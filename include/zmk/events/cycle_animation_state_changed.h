// SPDX-License-Identifier: MIT
#pragma once

#include <zephyr/kernel.h>
#include <zmk/event_manager.h>

#define NVC_PAUSE 0   // play/stop toggle
#define NVC_NEXT  1   // next theme (keeps play state)
#define NVC_PREV  2   // previous theme (keeps play state)
#define NVC_SHUF  3   // new random static frame of the current theme (pauses)

struct cycle_animation_state_changed {
    int type;
};

ZMK_EVENT_DECLARE(cycle_animation_state_changed);