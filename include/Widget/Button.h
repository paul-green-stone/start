#ifndef _START_BUTTON_WIDGET_H
#define _START_BUTTON_WIDGET_H

/* ================================================================ */

/**
 * Usage: `Widget_create(Button, font, color, label, position);`
 * 
 * @param Button pointer to the button widget descriptor
 * @param font pointer to an `SDL_ttf` font used to render the button's label text (`TTF_Font*`)
 * @param color pointer to an `SDL_Color` structure specifying the color of the label text (`SDL_Color*`)
 * @param label null-terminated string containing the text displayed on the button (`const char*`)
 * @param position pointer to a `Vector2` struct specifying the button's position coordinates (`Vector2*`)
 */
extern const void* Button;

/* ================================================================ */

#endif /* _START_BUTTON_WIDGET_H */
