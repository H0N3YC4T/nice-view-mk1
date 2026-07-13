# Change ledger — nice-view-mk1

Everything this module changes on top of M165437/nice-view-gem, in one place. Companion docs
live in the keyboard repo (prototype-mk1: docs/information.md; the old issues.md is retired, see its git history).
Consumed by the keyboard repo via `revision: main` in `config/west.yml`.

## Theme switching wired + peripheral battery tick (2026-07-12, HARDWARE-VERIFIED same day)

**Why switching never worked:** the `cycle_animation` behavior already had
`BEHAVIOR_LOCALITY_GLOBAL` (central invokes it locally AND relays it to every peripheral),
but ZMK's BLE split relay carries the behavior's DEVICE NAME in a 9-byte field
(`ZMK_SPLIT_RUN_BEHAVIOR_DEV_LEN`) -- `cycle_animation` (15 chars) was truncated to
`cycle_an` on the wire, the peripheral's behavior lookup failed, and the only symptom was a
LOG_ERR nobody had enabled. Same constraint upstream documents on its own reset behaviors
("name must be <= 8 characters": `sysreset`, `bootload`).

**Fix (keyboard-repo side):** rename the keymap NODE to `nvcycle` (7 chars) -- the C label
`cycle_animation:` and every `&cycle_animation NVC_*` binding stay unchanged. Also set
`NICE_VIEW_MK1_TRANSMUTATION_ONLY=n` on the halves so all themes are compiled to switch
between. On the module side nothing was needed: the peripheral listener, redraw path and
locality were already correct. In static mode (`NICE_VIEW_ANIMATION=n`) NVC_NEXT/PREV pick a
random frame of the next/prev theme; NVC_PAUSE reshuffles the current theme's frame.

**Theme trim (2026-07-13):** crystal and ultramar dropped from the rotation on request --
removed from the enum, asset tables, Kconfig choice and CMake; the frame sources stay on
disk (recoverable by reverting this commit). Rotation is now transmutation / landscape /
evangelion / omnissiah; fallback theme is transmutation.

**Play/stop toggle (2026-07-13):** NVC_PAUSE now toggles the animation instead of only
reshuffling the frame. `NICE_VIEW_ANIMATION=y` compiles the animation engine;
new `NICE_VIEW_ANIMATION_AUTOSTART` (default y) picks the boot state -- the halves run
`AUTOSTART=n` so they boot paused on a random static frame and NVC_PAUSE starts/stops the
show. NVC_NEXT/PREV keep the current play state across theme changes; stopping lands on a
fresh random frame (the animimg frame index isn't exposed to freeze in place). In a
static-only build (`ANIMATION=n`) NVC_PAUSE still just reshuffles. New `NVC_SHUF` param:
a new random static frame of the current theme (pauses if playing) -- the old PAUSE
semantics under a new code.

**Battery:** `ZMK_DISPLAY_TICK_PERIOD_MS` defaults to 100ms for this shield (ZMK default is
10ms -- 100 display-thread wakeups/second driving lv_task_handler for a screen that only
changes on events). 33ms only when `NICE_VIEW_ANIMATION_AUTOSTART=y` (always-animating
builds); toggle builds keep the 100ms battery tick, so a playing animation updates at ~10fps
-- the paused battery profile is unchanged from the static build.

## Extraction + rename (2026-07-11)

Moved out of Keyboard-Prototype_Mk1 (where it lived vendored at `boards/shields/nice_view_gem`
since the LVGL 9 re-vendor) into this standalone module, renamed nice_view_gem ->
nice_view_mk1 (shield dir, file names, `SHIELD_NICE_VIEW_MK1`, `NICE_VIEW_MK1_*` Kconfig
symbols; the neutral `NICE_VIEW_ANIMATION*` / `NICE_VIEW_WIDGET_*` symbols kept their names).
The `cycle_animation` behavior, its event, headers and DT binding moved in from the keyboard
repo's `app/` + `include/` trees -- their only consumer is this module's animation widget.
No functional changes in the move.

## Inherited state (pre-extraction history lives in the keyboard repo)

- LVGL 9 / Zephyr 4.1 port of the whole widget set; re-vendored from upstream @ 0a50fe2.
- Custom theme system: 6 frame-set themes + `cycle_animation` behavior (NVC_NEXT/PREV/PAUSE)
  driving theme changes on the peripherals via the split.
- Theme switching PAUSED: peripherals show one static transmutation frame
  (`NICE_VIEW_ANIMATION=n`, `NICE_VIEW_MK1_TRANSMUTATION_ONLY=y` gates the other five themes'
  bitmaps out of the build). Full switching system backed up on the keyboard repo's
  `dev/periph-theme` branch; switching WORKS since 2026-07-12 (see entry above) -- the old branch is just a
  design reference, not a working feature.
- WPM gauge fixed-range option (`NICE_VIEW_MK1_WPM_FIXED_RANGE`, max default 100).
