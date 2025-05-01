#ifndef _START_WIDGET_INTERFACE_H
#define _START_WIDGET_INTERFACE_H

#include <SDL2/SDL.h>
#include <stdarg.h>

#include "../Math/Vector2D.h"
#include "../Text.h"

/* ================================================================ */

/**
 * Defines a function pointer type named action for callback functions that take a single `void*` argument and return no value.
 */
typedef void (*action)(va_list* app);

/* ================================ */

/**
 * Creates a new widget instance.
 * 
 * @param widget pointer to a widget descriptor
 * @param ... constructor-specific arguments (type and quantity depend on widget implementation)
 * 
 * @return Returns a pointer to initialized widget instance or NULL if memory allocation fails.
 */
void* Widget_create(const void* widget, ...);

/**
 * Destroys a widget instance and releases associated resources.
 * 
 * @param widget pointer to widget instance created by `Widget_create`
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Widget_destroy(void* widget);

/**
 * Generic drawing interface for widgets.
 * Delegates drawing operations to the widget's descriptor-defined draw function,
 * enabling polymorphic rendering behavior.
 * 
 * @param widget pointer to a valid widget instance
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
int Widget_draw(const void* widget, const SDL_Rect* dst);

/**
 * Retrieves the dimensions (width and height) of a widget.
 * 
 * @param widget Pointer to the widget instance
 * @param dimensions pointer to a `Vector2` struct where dimensions will be stored
 * 
 * @return Returns 0 and writes the widget dimensions to `*dimensions` or -1 on failure.
 */
int  Widget_get_dimensions(const void* widget, Vector2* dimensions);

/**
 * Retrieves the label text object associated with a widget.
 * 
 * @param widget pointer to the widget instance
 * 
 * @return Returns a pointer to the `Text` object representing the widget's label on success, NULL on failure.
 */
Text* Widget_get_label(const void* widget);

/**
 * Binds a callback function to a widget.
 * 
 * @param widget pointer to the widget instance
 * @param callbakc function pointer to the callback to bind to the widget
 * 
 * @return Returns 0 if the widget's bind method is called successfully, -1 otherwise.
 */
int Widget_bind_callback(void* widget, action callback);

/**
 * Triggers the widget's `on_click` callback function if it exists.
 * 
 * @param widget pointer to the widget instance to activate
 * @param data optional user-defined data to pass to the callback
 * 
 * @return Returns 0 if the widget's callback function is successfully called, -1 otherwise.
 */
int Widget_handle_click(const void* widget, ...);

/* ================================================================ */

#endif /* _START_WIDGET_INTERFACE_H */
