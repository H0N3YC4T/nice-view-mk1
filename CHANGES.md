# Change ledger — nice-view-mk1

Everything this module changes on top of M165437/nice-view-gem, in one place. Companion docs
live in the keyboard repo (Keyboard-Prototype_Mk1: docs/information.md + docs/issues.md).
Consumed by the keyboard repo via `revision: main` in `config/west.yml`.

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
  `dev/periph-theme` branch; switching never worked end-to-end on hardware -- treat as a
  design reference, not a working feature.
- WPM gauge fixed-range option (`NICE_VIEW_MK1_WPM_FIXED_RANGE`, max default 100).
