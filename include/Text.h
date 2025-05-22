#ifndef START_TEXT_H
#define START_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "Texture.h"

#define TEXT_BUFFER 64

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct text {

    Texture* texture;           /* The underlying texture of the text */

    char content[TEXT_BUFFER];  /* The string content of the text */

    SDL_Color color;
    TTF_Font* font;

    int width;
    int height;
};

/* ======== */

typedef struct text Text;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * The function creates a new instance of `Text`, which relies on `Texture`. Therefore, specifying the rendering context is necessary.
 * 
 * @param r a rendering context used for texture rendering
 * @param font the font used in the text
 * @param color a color of the text
 * @param str a string of textual data to be rendered
 * 
 * @return Returns the `Text` or `NULL` on failure; call `Error_string()` for more information.
 */
Text* Text_new(SDL_Renderer* context, TTF_Font* font, SDL_Color* color, const char* str);

/**
 * Destroy a text object. The function deallocates the `Text` object, reclaiming all memory occupied by it.
 * 
 * @param text text to destroy
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int Text_destroy(Text** text);

/**
 * Update the textual content of a `Text` object.
 * 
 * @param text text to update (change its content)
 * @param str a string used to update the text
 * 
 * @return Returns a `Text` object containing the string `str`.
 */
Text* Text_update(Text* text, const char* str);

/**
 * Set a `Text` object color.
 * 
 * @param text text to update (set a new color)
 * @param color a new color of the text
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int Text_set_color(Text* text, const SDL_Color* color);

/**
 * Set a `Text` object font.
 * 
 * @param text text to update (set a new font)
 * @param font a font used to update the text
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int Text_set_font(Text* text, TTF_Font* font);

/**
 * Display text on the screen.
 * 
 * @param text text to be rendered on the screen
 * @param dst the region into which text should be rendered
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure.
 */
int Text_draw(const Text* text, const SDL_Rect* dst);

/**
 * Draw text on the screen with optional rotation and flipping.
 * 
 * @param src a region of the texture to be drawn. `NULL` for the whole texture
 * @param dst the destination area on the screen where the texture will be rendered. `NULL` for the entire screen
 * @param angle an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction
 * @param center a pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around `dst.w / 2`, `dst.h / 2`)
 * @param flip a `SDL_RendererFlip` value stating which flipping actions should be performed on the texture
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure.
 */
int Text_drawM(const Text *t, const SDL_Rect *src, const SDL_Rect *dst, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);

/* ================================================================ */

#endif /* START_TEXT_H */
