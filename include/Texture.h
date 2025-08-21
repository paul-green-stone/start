#ifndef _START_TEXTURE_H
#define _START_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct texture {

    SDL_Renderer* r;
    SDL_Texture* t;
};

/* ======== */

typedef struct texture Texture;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Create (load) a new texture for the specified renderer.
 * 
 * @param context the `SDL_Renderer*` a texture will be associated with
 * @param filename path to the texture
 * 
 * @return Returns the `Texture` that was created or `NULL` on failure; call `Error_string()` for more information.
 */
Texture* Texture_new(SDL_Renderer* context, const char* filename);

/**
 * Destroy a texture.
 * 
 * @param texture to destroy (&texture)
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int Texture_destroy(Texture** texture);

/**
 * Draw a texture on the screen.
 * 
 * @param src a region of the texture to be drawn. `NULL` for the whole texture
 * @param dst the destination area on the screen where the texture will be rendered. `NULL` for the entire screen
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure.
 */
int Texture_draw(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst);

/**
 * Draw a texture on the screen with optional rotation and flipping.
 * 
 * @param src a region of the texture to be drawn. `NULL` for the whole texture
 * @param dst the destination area on the screen where the texture will be rendered. `NULL` for the entire screen
 * @param angle an angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction
 * @param center a pointer to a point indicating the point around which dstrect will be rotated (if `NULL`, rotation will be done around `dst.w / 2`, `dst.h / 2`)
 * @param flip a `SDL_RendererFlip` value stating which flipping actions should be performed on the texture
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure.
 */
int Texture_drawM(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);

/**
 * Get the dimensions of a texture.
 * 
 * @param w a pointer filled in with the width of the texture in pixels. This argument can be `NULL` if you don't need this information
 * @param h a pointer filled in with the height of the texture in pixels. This argument can be `NULL` if you don't need this information
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure.
 */
int Texture_get_dimensions(const Texture* texture, int* w, int* h);

/* ================================================================ */

#endif /* _START_TEXTURE_H */
