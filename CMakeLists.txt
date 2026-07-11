zephyr_include_directories(include)
zephyr_library()

# cycle_animation behavior + event: compiled whenever a keymap declares a
# zmk,behavior-cycle-animation node, independent of which shield is building
# (the keymap is shared across every target of a split).
if(CONFIG_DT_HAS_ZMK_BEHAVIOR_CYCLE_ANIMATION_ENABLED)
  zephyr_library_sources(src/events/cycle_animation_state_changed.c)
  zephyr_library_sources(src/behaviors/behavior_cycle_animation.c)
endif()
