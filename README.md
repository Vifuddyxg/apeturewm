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
sudo make install      # installs /usr/local/bin/apeturewm
```

Run it from `~/.xinitrc`:

```sh
exec apeturewm
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
# apeturewm
