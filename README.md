# apeturewm

A tiny, fast X11 tiling window manager — the WM for **Aperture Linux**.

Single-file C, BSP tiling tree, per-monitor bar, workspaces 1–9 (up to 500),
Xinerama + RandR hotplug, and an optional XComposite overview. No modes, no
runtime config file: everything is set at compile time in `config.h`,
dwm-style — edit, `make`, restart.

## Design

- **Super-light & minimal.** One C file, `-Os`, links only X11 + a few
  extensions. The binary is ~75 KB.
- **No vim modes, no command line.** Every key is a direct global binding
  (Super + key). There is no INSERT/NORMAL/COMMAND state to think about.
- **dwm-style config.** All settings — colors, sizes, keybinds, rules,
  autostart — live in `config.h`. Change it and recompile.
- **Minimal top bar.** A single line at the top showing workspaces on the
  left and the clock on the right. That's it.

## Aperture palette

Set in `config.h`:

| Role                    | Hex        |
|-------------------------|------------|
| Background              | `#100A02`  |
| Secondary text / lines  | `#A66900`  |
| Primary text            | `#F1B00A`  |

The focused window border and the bar's primary text use the bright amber
(`#F1B00A`); the active-workspace box and muted text use `#A66900`; everything
sits on the near-black `#100A02`.

## Build

Needs X11 dev headers: `libX11`, `libXinerama`, `libXrandr`, `libXcomposite`,
`libXrender`.

```sh
make
sudo make install      # installs the binary + the greeter session entry
```

`make install` places:

- `/usr/local/bin/apeturewm` — the window manager
- `/usr/share/xsessions/apeturewm.desktop` — the login session entry

## Running it

### Without a greeter (`startx`)

Run it straight from `~/.xinitrc`:

```sh
#!/bin/sh
# ~/.xinitrc
# optional: wallpaper / compositor / etc. go here, before exec
# feh --bg-fill ~/wall.png &
exec apeturewm
```

then `startx`.

### With a greeter (graphical login)

`make install` drops `/usr/share/xsessions/apeturewm.desktop`:

```ini
[Desktop Entry]
Name=Aperture WM
Comment=Minimal tiling window manager for Aperture Linux
Exec=apeturewm
TryExec=apeturewm
Type=XSession
DesktopNames=apeturewm
Keywords=tiling;wm;aperture;
```

Every X11 greeter reads `/usr/share/xsessions/*.desktop`, so once that file is
in place **"Aperture WM"** shows up in the session picker at login. Pick one of
the setups below.

#### LightDM (works on Devuan, no systemd)

```sh
# Devuan / Debian
sudo apt install lightdm lightdm-gtk-greeter
```

LightDM auto-detects the session from the `.desktop` above — nothing else is
required. To theme the greeter to match Aperture and default new logins to
apeturewm, edit `/etc/lightdm/lightdm.conf`:

```ini
[Seat:*]
# default session shown selected in the picker
user-session=apeturewm
greeter-session=lightdm-gtk-greeter

[greeter]
# amber-on-black to match the WM
theme-name=Adwaita-dark
background=#100A02
```

Enable it (Devuan uses sysvinit/OpenRC, not systemd):

```sh
sudo rc-update add lightdm default     # OpenRC
# or, on sysvinit:
sudo update-rc.d lightdm defaults
```

#### greetd (minimal, no systemd — fits the lightweight theme)

`greetd` is a tiny, init-agnostic greeter. Pair it with the text greeter
`agreety` (console) or `gtkgreet` (graphical). Complete console example:

```sh
sudo apt install greetd
```

`/etc/greetd/config.toml`:

```toml
[terminal]
# the VT greetd runs on
vt = 1

[default_session]
# agreety draws the login prompt, then launches the command below
command = "agreety --cmd apeturewm"
user = "greeter"
```

For a graphical greetd login with `gtkgreet`, point it at a session wrapper
instead:

`/etc/greetd/config.toml`:

```toml
[terminal]
vt = 1

[default_session]
command = "cage -s -- gtkgreet"
user = "greeter"
```

…and let it launch X with apeturewm via a small `~/.xsession` (or a wrapper
script) that ends in `exec apeturewm`.

Start greetd at boot (OpenRC):

```sh
sudo rc-update add greetd default
```

## Configure

Open `config.h`, change what you want, then:

```sh
make && sudo make install
```

and restart the WM with **Super+Shift+R** (re-execs the installed binary
without ending your X session).

What you can set in `config.h`:

- **Layout:** gap, border width, workspace count.
- **Palette:** the three Aperture colors and how they map to borders/bar.
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
