/* config.h — apeturewm compile-time configuration (dwm-style: edit & recompile)
 *
 * Everything that used to live in config.conf now lives here. Change a value,
 * run `make`, restart the WM (mod+shift+r). No runtime config file is read.
 */
#ifndef APETURE_CONFIG_H
#define APETURE_CONFIG_H

/* ----- layout ----- */
#define CFG_GAP            6     /* gap between tiles, px            */
#define CFG_BORDER         2     /* window border width, px         */
#define CFG_WORKSPACES     9     /* number of workspaces (1..500)   */

/* ----- Aperture palette ----- */
#define COL_BG     0x100A02      /* background                      */
#define COL_LINE   0xA66900      /* secondary text / lines          */
#define COL_TEXT   0xF1B00A      /* primary text                    */

#define CFG_BORDER_FOCUS   COL_LINE    /* focused window border     */
#define CFG_BORDER_NORMAL  COL_BG    /* unfocused window border   */

#define CFG_ROOT_BG        0x2d1e13    /* empty desktop / root background */

/* ----- bar (minimal, single line, top) ----- */
#define CFG_BAR_ENABLED    1
#define CFG_BAR_HEIGHT     22
#define CFG_BAR_POSITION   BAR_TOP     /* BAR_TOP or BAR_BOTTOM     */
#define CFG_BAR_PADDING_X  8
#define CFG_BAR_ITEM_GAP   8
#define CFG_BAR_TEXT_PAD   6
#define CFG_BAR_WS_MIN_W   0           /* 0 = size tags to content  */
#define CFG_BAR_FONT       "9x15"
/* bar layout: comma list of items. items: workspaces,title,clock,battery */
#define CFG_BAR_LEFT       "workspaces"
#define CFG_BAR_CENTER     ""
#define CFG_BAR_RIGHT      "battery,clock"

#define CFG_BAR_BG         CFG_ROOT_BG  /* bar background (matches desktop) */
#define CFG_BAR_FG         COL_TEXT     /* normal bar text          */
#define CFG_BAR_ACCENT_BG  COL_LINE     /* active workspace box bg  */
#define CFG_BAR_ACCENT_FG  COL_BG       /* active workspace box text*/
#define CFG_BAR_MUTED_FG   COL_LINE     /* inactive / muted text    */

/* ----- misc ----- */
#define CFG_TERMINAL          "st"
#define CFG_SCREEN_OFF_MIN    0     /* dpms blank after N idle min (0=off) */
#define CFG_AUTO_MONITORS     1     /* auto-enable hotplugged outputs      */
#define CFG_MONITOR_HOOK      ""    /* command run after a layout change   */
#define CFG_COMPOSITOR_MODE   0     /* 0=auto 1=on 2=off                   */

/* ----- keybinds (dwm-style table) -----
 * mod: MOD (Super), ShiftMask, ControlMask, Mod1Mask (Alt) — OR them together.
 * action: "spawn:<shell cmd>"  or  "wm:<action>"
 *   wm actions: quit restart kill clear screenshot overview toggle_split
 *               focus_left/right/up/down focus_next/prev
 *               swap_left/right/up/down  swap_next/prev
 *               toggle_fullscreen toggle_real_fullscreen
 *               toggle_float toggle_float_centered
 *               workspace:N  workspace_prev workspace_next
 *               move_to_workspace:N move_to_workspace_follow:N
 *               move_to_workspace_prev move_to_workspace_next
 *               ratio:+0.05 / ratio:-0.05
 */
static const Keybind keybinds[] = {
    /* launchers */
    { MOD,             XK_Return, "spawn:" CFG_TERMINAL },
    { MOD,             XK_q,      "spawn:" CFG_TERMINAL },
    { MOD,             XK_space,  "spawn:rofi -show drun" },
    { 0,               XK_Print,  "wm:screenshot" },

    /* window / session */
    { MOD,             XK_c,      "wm:kill" },
    { MOD|ShiftMask,   XK_q,      "wm:quit" },
    { MOD|ShiftMask,   XK_r,      "wm:restart" },
    { MOD,             XK_f,      "wm:toggle_fullscreen" },
    { MOD|ShiftMask,   XK_f,      "wm:toggle_real_fullscreen" },
    { MOD,             XK_v,      "wm:toggle_float_centered" },
    { MOD,             XK_s,      "wm:toggle_split" },
    { MOD,             XK_z,      "wm:overview" },
    { MOD,             XK_Tab,    "wm:focus_next" },

    /* focus (hjkl + arrows) */
    { MOD,             XK_h,      "wm:focus_left" },
    { MOD,             XK_l,      "wm:focus_right" },
    { MOD,             XK_k,      "wm:focus_up" },
    { MOD,             XK_j,      "wm:focus_down" },
    { MOD,             XK_Left,   "wm:focus_left" },
    { MOD,             XK_Right,  "wm:focus_right" },
    { MOD,             XK_Up,     "wm:focus_up" },
    { MOD,             XK_Down,   "wm:focus_down" },

    /* swap / move window (hjkl + arrows) */
    { MOD|ShiftMask,   XK_h,      "wm:swap_left" },
    { MOD|ShiftMask,   XK_l,      "wm:swap_right" },
    { MOD|ShiftMask,   XK_k,      "wm:swap_up" },
    { MOD|ShiftMask,   XK_j,      "wm:swap_down" },
    { MOD|ShiftMask,   XK_Left,   "wm:swap_left" },
    { MOD|ShiftMask,   XK_Right,  "wm:swap_right" },
    { MOD|ShiftMask,   XK_Up,     "wm:swap_up" },
    { MOD|ShiftMask,   XK_Down,   "wm:swap_down" },

    /* split ratio */
    { MOD,             XK_minus,  "wm:ratio:-0.05" },
    { MOD,             XK_equal,  "wm:ratio:+0.05" },

    /* workspaces */
    { MOD,             XK_1,      "wm:workspace:1" },
    { MOD,             XK_2,      "wm:workspace:2" },
    { MOD,             XK_3,      "wm:workspace:3" },
    { MOD,             XK_4,      "wm:workspace:4" },
    { MOD,             XK_5,      "wm:workspace:5" },
    { MOD,             XK_6,      "wm:workspace:6" },
    { MOD,             XK_7,      "wm:workspace:7" },
    { MOD,             XK_8,      "wm:workspace:8" },
    { MOD,             XK_9,      "wm:workspace:9" },
    { MOD,             XK_Prior,  "wm:workspace_prev" },
    { MOD,             XK_Next,   "wm:workspace_next" },

    /* move focused window to workspace (and follow) */
    { MOD|ShiftMask,   XK_1,      "wm:move_to_workspace_follow:1" },
    { MOD|ShiftMask,   XK_2,      "wm:move_to_workspace_follow:2" },
    { MOD|ShiftMask,   XK_3,      "wm:move_to_workspace_follow:3" },
    { MOD|ShiftMask,   XK_4,      "wm:move_to_workspace_follow:4" },
    { MOD|ShiftMask,   XK_5,      "wm:move_to_workspace_follow:5" },
    { MOD|ShiftMask,   XK_6,      "wm:move_to_workspace_follow:6" },
    { MOD|ShiftMask,   XK_7,      "wm:move_to_workspace_follow:7" },
    { MOD|ShiftMask,   XK_8,      "wm:move_to_workspace_follow:8" },
    { MOD|ShiftMask,   XK_9,      "wm:move_to_workspace_follow:9" },
};

/* autostart: shell commands run once at startup. NULL-terminated. */
static const char *autostart[] = {
    /* "picom", */
    /* "feh --bg-fill /path/to/wallpaper.png", */
    NULL,
};

/* window rules: match by class/instance/title, set floating and/or workspace.
 * workspace -1 means "leave on current". A rule with all match fields empty is
 * ignored, so the trailing entry below just terminates the table harmlessly. */
static const Rule config_rules[] = {
    /* { .class_name = "Pavucontrol", .set_floating = 1, .floating = 1, .workspace = -1 }, */
    /* { .class_name = "Librewolf",   .workspace = 1 }, */
    { .workspace = -1 },
};

#endif /* APETURE_CONFIG_H */
