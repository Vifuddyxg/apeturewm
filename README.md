# apeturewm

A small, fast tiling window manager for X11.

Single-file C, BSP tiling tree, per-monitor bar, workspaces 1–9 (up to 500),
and an optional XComposite overview. Everything is set at compile time in
`config.h`, dwm-style — edit, `make`, restart. No runtime config file.

## Features

- **Fast & light.** One C file, built with `-Os`. The binary is ~75 KB and
  links only X11 plus a few standard extensions.
- **Runs on Xorg or XLibre.** Build against the normal X11 client libraries
  and run inside either server — no separate build needed.
- **Multi-monitor.** Xinerama-based layout with live RandR hotplug: plug or
  unplug an output and the screen reconfigures on the fly.
- **EWMH-aware.** Reports active window, client list, desktops and fullscreen
  state, so panels, pagers, and fullscreen apps behave correctly.
- **Plays well with others.** Reserves space for external bars/docks via strut
  hints (e.g. `polybar`), and an optional compositor (`picom`) works alongside
  the built-in overview thumbnails.
- **Tiling + floating + fullscreen.** BSP splits with adjustable ratios,
  per-window floating, normal and "real" (EWMH) fullscreen, and window rules.
- **dwm-style config.** Colors, sizes, keybinds, rules and autostart all live
  in `config.h`. Change it and recompile.

## Palette

The default theme is amber-on-black, set in `config.h`:

| Role                    | Hex        |
|-------------------------|------------|
| Background              | `#100A02`  |
| Secondary text / lines  | `#A66900`  |
| Primary text            | `#F1B00A`  |

The focused window border and the bar's primary text use the bright amber
(`#F1B00A`); the active-workspace box and muted text use `#A66900`; everything
sits on the near-black `#100A02`. Change all three in one place in `config.h`.

## Dependencies

Build needs a C compiler, `make`, and the X11 client headers/libraries:
`libX11`, `libXinerama`, `libXrandr`, `libXcomposite`, `libXrender`.

### Install the build dependencies

**Debian / Devuan / Ubuntu / Mint**

```sh
sudo apt install build-essential libx11-dev libxinerama-dev \
     libxrandr-dev libxcomposite-dev libxrender-dev
```

**Arch / Manjaro / EndeavourOS**

```sh
sudo pacman -S --needed base-devel libx11 libxinerama \
     libxrandr libxcomposite libxrender
```

**Fedora / RHEL / Rocky / Alma**

```sh
sudo dnf install gcc make libX11-devel libXinerama-devel \
     libXrandr-devel libXcomposite-devel libXrender-devel
```

**openSUSE**

```sh
sudo zypper install gcc make libX11-devel libXinerama-devel \
     libXrandr-devel libXcomposite-devel libXrender-devel
```

**Void Linux**

```sh
sudo xbps-install -S base-devel libX11-devel libXinerama-devel \
     libXrandr-devel libXcomposite-devel libXrender-devel
```

**Alpine**

```sh
sudo apk add build-base libx11-dev libxinerama-dev \
     libxrandr-dev libxcomposite-dev libxrender-dev
```

**Gentoo** (most are pulled in by a normal X install)

```sh
sudo emerge -an x11-libs/libX11 x11-libs/libXinerama \
     x11-libs/libXrandr x11-libs/libXcomposite x11-libs/libXrender
```

**NixOS** — a throwaway build shell:

```sh
nix-shell -p gcc gnumake xorg.libX11 xorg.libXinerama \
     xorg.libXrandr xorg.libXcomposite xorg.libXrender
```

### Optional at runtime

`rofi` (launcher), a terminal such as `alacritty`, `picom` (compositor),
`polybar` (external bar), `pipewire`/`wireplumber` (audio session).

## Build & install

```sh
make
sudo make install
```

`make install` places:

- `/usr/local/bin/apeturewm` — the window manager
- `/usr/local/bin/apeturewm-session` — the login session wrapper
- `/usr/share/xsessions/apeturewm.desktop` — the greeter session entry

## Running it

### With `startx`

Minimal `~/.xinitrc`:

```sh
exec apeturewm
```

Recommended `~/.xinitrc` for a full session (audio + session bus):

```sh
exec dbus-run-session sh -lc '
export XDG_CURRENT_DESKTOP=apeturewm
export XDG_SESSION_DESKTOP=apeturewm
export DESKTOP_SESSION=apeturewm
export XCURSOR_THEME=Adwaita
export XCURSOR_SIZE=24
command -v pipewire    >/dev/null 2>&1 && pipewire &
command -v wireplumber >/dev/null 2>&1 && wireplumber &
exec apeturewm
'
```

Then run `startx`.

## Greeter / XSession

If you want apeturewm in your graphical login, use a **session wrapper script**.
Do not point the greeter directly at the `apeturewm` binary, or you may end up
with a broken login session (no session bus, no audio).

`make install` already sets both files up for you. They look like this:

`/usr/share/xsessions/apeturewm.desktop`

```ini
[Desktop Entry]
Name=apeturewm
Comment=Tiling window manager for X11
Exec=/usr/local/bin/apeturewm-session
TryExec=/usr/local/bin/apeturewm
Type=XSession
DesktopNames=apeturewm
Keywords=tiling;wm;
```

`/usr/local/bin/apeturewm-session`

```sh
#!/bin/sh
export XDG_CURRENT_DESKTOP=apeturewm
export XDG_SESSION_DESKTOP=apeturewm
export XDG_SESSION_TYPE=x11

exec dbus-run-session sh -lc '
  command -v pipewire    >/dev/null 2>&1 && pipewire &
  command -v wireplumber >/dev/null 2>&1 && wireplumber &
  exec apeturewm
'
```

If you set them up by hand, make the wrapper executable:

```sh
sudo chmod +x /usr/local/bin/apeturewm-session
```

Every X11 greeter reads `/usr/share/xsessions/*.desktop`, so once that entry is
in place **apeturewm** shows up in the session picker. Pick whichever greeter
you like.

### greetd + tuigreet

`greetd` is a tiny, init-agnostic greeter; `tuigreet` is its console UI. It
picks up `apeturewm` automatically from the `.desktop` above.

`/etc/greetd/config.toml`

```toml
[terminal]
vt = 1

[default_session]
command = "tuigreet --remember --sessions /usr/share/xsessions"
user = "greeter"
```

Enable it at boot (OpenRC / sysvinit, no systemd required):

```sh
sudo rc-update add greetd default          # OpenRC
sudo update-rc.d greetd defaults           # sysvinit
```

### LightDM

LightDM auto-detects the session from the `.desktop` — nothing extra is
required:

```sh
sudo apt install lightdm lightdm-gtk-greeter
```

To default new logins to apeturewm and theme the greeter, edit
`/etc/lightdm/lightdm.conf`:

```ini
[Seat:*]
user-session=apeturewm
greeter-session=lightdm-gtk-greeter

[greeter]
theme-name=Adwaita-dark
background=#100A02
```

```sh
sudo rc-update add lightdm default         # OpenRC
sudo update-rc.d lightdm defaults          # sysvinit
```

### SDDM

```sh
sudo apt install sddm
```

SDDM also reads `/usr/share/xsessions/`; select **apeturewm** from the session
menu at the bottom of the login screen.

Notes:

- apeturewm needs X11 **client** libraries at build time, not XLibre server
  headers. The same binary runs under Xorg or XLibre.
- Multi-monitor support depends on the Xinerama extension being available and
  active in the running X server.
- A compositor (`picom`) is optional and not required. For the lightest setup,
  don't install one — apeturewm works fine without it.

## Configure

Open `config.h`, change what you want, then:

```sh
make && sudo make install
```

and restart the WM with **Super+Shift+R** (re-execs the installed binary
without ending your X session).

What you can set in `config.h`:

- **Layout:** gap, border width, workspace count.
- **Palette:** the three colors and how they map to borders/bar.
- **Bar:** height, top/bottom, padding, font, and the comma-separated item
  lists (`workspaces`, `title`, `clock`, `battery`) for left/center/right.
- **Keybinds:** the `keybinds[]` table — `{ mod, keysym, action }`.
- **Autostart:** the `autostart[]` list of shell commands.
- **Window rules:** the `config_rules[]` table (float / send to workspace by
  class, instance or title).

### Keybind actions

`action` is either `"spawn:<shell command>"` or `"wm:<action>"`. Available wm
actions:

```
quit restart kill clear screenshot overview toggle_split
focus_left/right/up/down  focus_next/prev
swap_left/right/up/down   swap_next/prev
toggle_fullscreen toggle_real_fullscreen toggle_float toggle_float_centered
workspace:N  workspace_prev workspace_next
move_to_workspace:N  move_to_workspace_follow:N
move_to_workspace_prev move_to_workspace_next
ratio:+0.05  ratio:-0.05
```

## Default keys (Super = Mod4)

| Key | Action |
|-----|--------|
| `Super+Return` / `Super+Q` | terminal |
| `Super+Space` | rofi launcher |
| `Super+C` | close window |
| `Super+Shift+Q` | quit |
| `Super+Shift+R` | restart (reload config) |
| `Super+H/J/K/L` or arrows | move focus |
| `Super+Shift+H/J/K/L` or arrows | swap / move window |
| `Super+-` / `Super+=` | shrink / grow split |
| `Super+S` | toggle split direction |
| `Super+F` / `Super+Shift+F` | fullscreen / real fullscreen |
| `Super+V` | toggle centered float |
| `Super+Tab` | next window |
| `Super+1..9` | go to workspace |
| `Super+Shift+1..9` | send window to workspace |
| `Super+PageUp/PageDown` | previous / next workspace |
| `Super+Z` | workspace overview |
| `Print` | screenshot |

Mouse: `Super+Button1` move/swap, `Super+Button3` resize, `Super+scroll`
switch workspace.
# apeturewm
