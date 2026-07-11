// widgets/animation.h
#pragma once

#include <lvgl.h>

// Theme selection
enum nice_view_theme {
    NICE_VIEW_THEME_CRYSTAL = 0,
    NICE_VIEW_THEME_LANDSCAPE,
    NICE_VIEW_THEME_EVANGELION,
    NICE_VIEW_THEME_TRANSMUTATION,
    NICE_VIEW_THEME_OMNISSIAH,
    NICE_VIEW_THEME_ULTRAMAR,
    NICE_VIEW_THEME_COUNT,
};


/**
 * @brief Return whether animation mode is enabled (true) or static-image mode (false).
 */
bool nice_view_animation_is_enabled(void);

/**
 * @brief Recompute the art offset and redraw on the bound screen (no-op if unbound).
 */
void nice_view_theme_redraw(void);

/**
 * @brief Bind the LVGL screen/container that the animation should draw into.
 *
 * Usually this is the same object you create in zmk_widget_screen_init()
 * (e.g. widget->obj).
 */
void nice_view_bind_screen(lv_obj_t *screen);

/**
 * @brief (Re)create the art object as a child of `parent` (the screen widget obj).
 */
void draw_animation(lv_obj_t *parent);

/**
 * @brief Set the current theme and redraw (if a screen is bound).
 */
void nice_view_theme_set(enum nice_view_theme theme);

/**
 * @brief Get the current theme.
 */
enum nice_view_theme nice_view_theme_get(void);

