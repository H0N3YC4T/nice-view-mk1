# nice-view-mk1

Custom nice!view display shield for the Prototype_Mk1 split keyboard: the central half gets a
status screen (layers / battery / output / WPM), the peripheral halves show themed pixel-art
frames. Extracted 2026-07-11 from the Keyboard-Prototype_Mk1 repo into its own ZMK module.

Derived from [M165437/nice-view-gem](https://github.com/M165437/nice-view-gem) (MIT — see
LICENSE), re-based onto LVGL 9 / Zephyr 4.1 and carrying a custom theme system on top.

## Usage

west.yml:

```yaml
- name: nice-view-mk1
  remote: honeycat
  revision: main
```

build.yaml (per half):

```yaml
- board: nice_nano//zmk
  shield: prototype_mk1_periph_left nice_view_adapter nice_view_mk1
```

The `cycle_animation` behavior (`zmk,behavior-cycle-animation`, params `NVC_PAUSE` /
`NVC_NEXT` / `NVC_PREV`, see `include/zmk/behaviors/cycle_animation.h`) compiles whenever a
keymap declares its node — bind it like any behavior.

## Themes

Six frame sets ship in `boards/shields/nice_view_mk1/assets/animations/`: transmutation
(default), crystal, landscape, evangelion, omnissiah, ultramar. **Theme switching is currently
paused**: peripherals show a single static transmutation frame
(`NICE_VIEW_MK1_TRANSMUTATION_ONLY=y` compiles only that theme's bitmaps to save flash;
`NICE_VIEW_ANIMATION=n` keeps it static to save battery). The full multi-theme switching
system is preserved for reference on the keyboard repo's `dev/periph-theme` branch.
