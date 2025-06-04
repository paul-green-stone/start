#ifndef _START_BUTTON_INTERFACE_H
#define _START_BUTTON_INTERFACE_H

#include "../../Texture.h"

/* ================================================================ */

/**
 * 
 */
int Button_set_texture(void* button, Texture* texture);

/**
 * 
 */
int Button_set_label_color(void* button, const SDL_Color* color);

/* ================================================================ */

#endif /* _START_BUTTON_INTERFACE_H */
