#ifndef _START_WIDGET_INTERFACE_H
#define _START_WIDGET_INTERFACE_H

#include <SDL2/SDL.h>
#include <stdarg.h>

#include "../Math/Vector2D.h"
#include "../Text.h"

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Creates a new widget instance.
 * 
 * @param widget pointer to a widget descriptor
 * @param ... constructor-specific arguments (type and quantity depend on widget implementation)
 * 
 * @return Returns a pointer to initialized widget instance on success, `NULL` on failure; call `Error_get()` for more information
 */
void* Widget_create(const void* widget, ...);

/**
 * Destroys a widget instance and releases associated resources.
 * 
 * @param widget pointer to widget instance created by `Widget_create()`
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information
 */
int Widget_destroy(void* widget);

/**
 * Generic drawing interface for widgets.
 * Delegates drawing operations to the widget's descriptor-defined draw function,
 * enabling polymorphic rendering behavior.
 * 
 * @param widget pointer to a valid widget instance
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Widget_draw(const void* widget, const SDL_Rect* src, const SDL_Rect* dst);

/**
 * Retrieves the dimensions (width and height) of a widget.
 * 
 * @param widget Pointer to the widget instance
 * @param w pointer to an integer where the width will be stored. Can be `NULL` if width is not needed
 * @param h pointer to an integer where the height will be stored. Can be `NULL` if height is not needed
 * 
 * @return @return Returns `SUCCESS` (0) on success, or a negative error code on failure; call `Error_get()` for more information.
 */
int Widget_get_dimensions(const void* widget, int* w, int* h);

/**
 * Sets the position of a widget.
 * 
 * @param widget pointer to the widget instance. Expected to be a pointer to a pointer to a widget struct
 * @param x the new x-coordinate of the widget
 * @param y the new y-coordinate of the widget
 * 
 * @return Returns `SUCCESS` (0) on success, or a negative error code on failure; call `Error_get()` for more information.
 */
int Widget_set_position(void* widget, int x, int y);

/**
 * Retrieves the position of a widget.
 * 
 * @param widget pointer to the widget instance. Expected to be a pointer to a pointer to a widget struct
 * @param x pointer to an integer where the widget's `x` coordinate will be stored. If `NULL`, the `x` coordinate will not be written
 * @param y pointer to an integer where the widget's `y` coordinate will be stored. If `NULL`, the `y` coordinate will not be written
 * 
 * @return Returns `SUCCESS` (0) on success, or a negative error code on failure; call `Error_get()` for more information.
 */
int Widget_get_position(const void* self, int* x, int* y);

/**
 * 
 */
int Widget_bind_callback(void* widget, int (callback)(const void* widget, va_list* args));

/**
 * 
 */
int Widget_click(const void* widget, ...);

/**
 * 
 */
int Widget_is_focused(const void* widget);

/* ================================================================ */

#endif /* _START_WIDGET_INTERFACE_H */
