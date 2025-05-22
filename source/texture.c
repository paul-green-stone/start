#include "../include/Texture.h"
#include "../include/Error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Texture* Texture_new(SDL_Renderer* context, const char* filename) {

    Texture* texture = NULL;
    /* ======== */

    /* == Texture Memory Allocation === */
    if ((texture = calloc(1, sizeof(Texture))) == NULL) {
        return NULL;
    }

    /* ====== Loading a Texture ======= */
    if ((texture->t = IMG_LoadTexture(context, filename)) == NULL) {

        free(texture);
        Error_set(SERR_SDL);
        /* ======== */
        return NULL;
    }

    texture->r = context;

    /* ======== */
    return texture;
}

/* ================================ */

int Texture_destroy(Texture** texture) {

    /* ====== Do not dereference a NULL pointer ======= */
    if ((texture == NULL) || (*texture == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* Destroying the `SDL_Texture` */
    SDL_DestroyTexture((*texture)->t);

    /* === Deallocating a Container === */
    free(*texture);
    *texture = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================ */

int Texture_draw(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst) {
    return SDL_RenderCopy(t->r, t->t, src, dst);
}

/* ================================ */

int Texture_drawM(const Texture *t, const SDL_Rect *src, const SDL_Rect *dst, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
    return SDL_RenderCopyEx(t->r, t->t, src, dst, angle, center, flip);
}

/* ================================ */

int Texture_get_dimensions(const Texture* texture, int* w, int* h) {
    return SDL_QueryTexture(texture->t, NULL, NULL, w, h);
}

/* ================================================================ */
