#ifndef _START_WIDGET_INTERFACE_H
#define _START_WIDGET_INTERFACE_H

#include <SDL2/SDL.h>

#include "../Math/Vector2D.h"
#include "../Text.h"

/* ================================================================ */

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

/* ================================================================ */

#endif /* _START_WIDGET_INTERFACE_H */
