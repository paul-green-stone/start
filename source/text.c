#include "../include/Text.h"
#include "../include/Error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Text* Text_new(SDL_Renderer* r, TTF_Font* font, SDL_Color* color, const char* str) {

    Text* text = NULL;
    /* ======== */

    /* ==== Text Memory Allocation ==== */
    if ((text = calloc(1, sizeof(Text))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* == Texture Memory Allocation === */
    if ((text->texture = calloc(1, sizeof(Texture))) == NULL) {

        free(text);
        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    text->texture->r = r;
    text->color = *color;
    text->font = font;

    text = Text_update(text, str);

    /* ======== */
    return text;
}

/* ================================================================ */

int Text_destroy(Text** text) {

    /* ====== Do not dereference a NULL pointer ======= */
    if ((text == NULL) || (*text == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Deallocating a Container === */
    Texture_destroy(&(*text)->texture);
    free(*text);

    *text = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

Text* Text_update(Text* text, const char* str) {

    SDL_Surface* s = NULL;
    /* ======== */

    /* Copying the text */
    strncpy(text->content, str, TEXT_BUFFER - 2);
    text->content[TEXT_BUFFER - 1] = '\0';

    /* Destroy the underlying `SDL_Texture` */
    if (text->texture->t != NULL) {
        SDL_DestroyTexture(text->texture->t);
    }

    if ((s = TTF_RenderText_Solid(text->font, text->content, text->color)) == NULL) {

        /* If something bad happens here, the original text is returned */

        Error_set(SERR_SDL);
        /* ======== */
        return text;
    }

    if ((text->texture->t = SDL_CreateTextureFromSurface(text->texture->r, s)) == NULL) {
       
        Error_set(SERR_SDL);
        /* ======== */
        return text;
    }

    SDL_FreeSurface(s);
    Texture_get_dimensions(text->texture, &text->width, &text->height);

    /* ======== */
    return text;
}

/* ================================================================ */

int Text_set_color(Text* text, const SDL_Color* color) {

    /* ====== Do not dereference a NULL pointer ======= */
    if (text == NULL) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    text->color = *color;
    /* Update the text with a new color */
    text = Text_update(text, text->content);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Text_set_font(Text* text, TTF_Font* font) {

    /* ====== Do not dereference a NULL pointer ======= */
    if (text == NULL) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    text->font = font;
    /* Update the text with a new font */
    text = Text_update(text, text->content);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Text_draw(const Text* text, const SDL_Rect* dst) {
    return SDL_RenderCopy(text->texture->r, text->texture->t, NULL, dst);
}

/* ================================================================ */

int Text_drawM(const Text *t, const SDL_Rect *src, const SDL_Rect *dst, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
    return SDL_RenderCopyEx(t->texture->r, t->texture->t, src, dst, angle, center, flip);
}

/* ================================================================ */
