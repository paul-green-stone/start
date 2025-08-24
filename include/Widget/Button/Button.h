#ifndef _START_BUTTON_INTERFACE_H
#define _START_BUTTON_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Texture.h"

/* ================================================================ */

/**
 * Sets or removes the texture for a button widget.
 * 
 * @param button pointer to the `Button` object (must not be `NULL`)
 * @param texture pointer to the `Texture` to assign, or `NULL` to remove the texture
 * 
 * @return Returns `SSUCCESS` (0) on success, or a negative error code on failure. call `Error_get()` for more information.
 */
int Button_set_texture(void* button, Texture* texture);

/**
 * Sets the color of the button's label text.
 * 
 * @param button pointer to the `Button` object (must not be `NULL`)
 * @param color pointer to an `SDL_Color` struct specifying the new color
 * 
 * @return Returns `SSUCCESS` (0) on success, or a negative error code on failure. call `Error_get()` for more information.
 */
int Button_set_label_color(void* button, const SDL_Color* color);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_BUTTON_INTERFACE_H */
