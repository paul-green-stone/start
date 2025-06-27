#ifndef _START_WIDGETS_COLLECTION_H
#define _START_WIDGETS_COLLECTION_H

/* ================================================================ */

/**
 * Widget base class
 */
extern const void* Widget;

/**
 * Usage: `Widget_create(Button, x, y, font, color, label, texture, src);`
 * 
 * @param Button pointer to the button widget descriptor
 * @param x x-coordinate of the button's position on the screen
 * @param y y-coordinate of the button's position on the screen
 * @param font pointer to an `SDL_ttf` font used to render the button's label text (`TTF_Font*`)
 * @param color pointer to an `SDL_Color` structure specifying the color of the label text (`SDL_Color*`)
 * @param label null-terminated string containing the text displayed on the button (`const char*`)
 * @param texture optional pointer to a custom texture object representing an image to be rendered as the button's background instead of the default label
 * @param src default portion of texture to render
 */
extern const void* Button;

/**
 * @param TextInput pointer to the text input widget descriptor
 * @param x x-coordinate of the button's position on the screen
 * @param y y-coordinate of the button's position on the screen
 * @param font pointer to an `SDL_ttf` font used to render the button's label text (`TTF_Font*`)
 * @param color pointer to an `SDL_Color` structure specifying the color of the label text (`SDL_Color*`)
 * @param label null-terminated string containing the text displayed on the button (`const char*`)
 */
extern const void* TextInput;

/**
 * @param SelectWidget pointer to the text input widget descriptor
 * @param x x-coordinate of the button's position on the screen
 * @param y y-coordinate of the button's position on the screen
 * @param font pointer to an `SDL_ttf` font used to render the button's label text (`TTF_Font*`)
 * @param color pointer to an `SDL_Color` structure specifying the color of the label text (`SDL_Color*`)
 * @param label null-terminated string containing the text displayed on the button (`const char*`)
 * @param num_options number of options
 * @param ... options
 */
extern const void* SelectWidget;

/* ================================================================ */

#endif /* _START_WIDGETS_COLLECTION_H */
