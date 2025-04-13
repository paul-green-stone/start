#include "../include/Text.h"

/* ================================================================ */

Text* Text_new(SDL_Renderer* r, TTF_Font* font, SDL_Color* color, const char* str) {

    Text* text;
    text = NULL;

    /* ================================ */
    /* ==== Text Memory Allocation ==== */
    /* ================================ */

    if ((text = calloc(1, sizeof(Text))) == NULL) {
        return NULL;
    }

    /* ================================ */
    /* == Texture Memory Allocation === */
    /* ================================ */

    if ((text->texture = calloc(1, sizeof(Texture))) == NULL) {

        free(text);
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

    if ((text == NULL) || (*text == NULL)) {
        return -1;
    }

    /* ================================ */
    /* === Deallocating a Container === */
    /* ================================ */

    Texture_destroy(&(*text)->texture);
    free(*text);

    *text = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */

Text* Text_update(Text* text, const char* str) {

    SDL_Surface* s;

    /* Copying the text */
    strncpy(text->content, str, TEXT_BUFFER - 2);
    text->content[TEXT_BUFFER - 1] = '\0';

    /* Destroy the underlying `SDL_Texture` */
    if (text->texture->t != NULL) {
        SDL_DestroyTexture(text->texture->t);
    }

    if ((s = TTF_RenderText_Solid(text->font, text->content, text->color)) == NULL) {

        /* If something bad happens here, the original text is returned */
        /* Need to think of some kind of error handling mechanism */

        return text;
    }

    if ((text->texture->t = SDL_CreateTextureFromSurface(text->texture->r, s)) == NULL) {
        return text;
    }

    SDL_FreeSurface(s);

    Texture_get_dimensions(text->texture, &text->width, &text->height);

    /* ======== */

    return text;
}

/* ================================================================ */

int Text_set_color(Text* text, const SDL_Color* color) {

    if (text == NULL) {
        return -1;
    }

    text->color = *color;

    /* Update the text with a new color */
    text = Text_update(text, text->content);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Text_set_font(Text* text, TTF_Font* font) {

    if (text == NULL) {
        return -1;
    }

    text->font = font;

    /* Update the text with a new font */
    text = Text_update(text, text->content);

    /* ======== */

    return 0;
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
