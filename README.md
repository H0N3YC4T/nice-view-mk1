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
`NVC_NEXT` / `NVC_PREV` / `NVC_SHUF`, see `include/zmk/behaviors/cycle_animation.h`) compiles whenever a
keymap declares its node — bind it like any behavior. **The DT node NAME must be 8 characters
or fewer** (e.g. `cycle_animation: nvcycle { ... }`): the behavior is GLOBAL-locality, and
ZMK's BLE split relay truncates device names to 8 chars + NUL — a longer node name is silently
cut and the peripheral-side lookup fails (theme keys then do nothing on the halves).

## Themes

Four frame sets ship in `boards/shields/nice_view_mk1/assets/animations/`: transmutation
(default), landscape, evangelion, omnissiah. By default peripherals show a
single static transmutation frame
(`NICE_VIEW_MK1_TRANSMUTATION_ONLY=y` compiles only that theme's bitmaps to save flash;
`NICE_VIEW_ANIMATION=n` compiles the animation engine out to save battery). With
`NICE_VIEW_ANIMATION=y` the NVC_PAUSE hotkey toggles play/stop at runtime;
`NICE_VIEW_ANIMATION_AUTOSTART=n` boots paused on a static frame (battery profile of the
static build until you press play). **Theme switching over the split works — wired and hardware-verified 2026-07-12** (root cause of it never working: the behavior node's 15-char
name was truncated by the BLE relay — see the node-name rule above; set
`NICE_VIEW_MK1_TRANSMUTATION_ONLY=n` on the halves so there is something to switch to). The
old reference attempt lives on the keyboard repo's `dev/periph-theme` branch.
