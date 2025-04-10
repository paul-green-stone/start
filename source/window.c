#include "../include/Window.h"

/* ================================================================ */

struct _window {

    SDL_Window*   w;    /* The Window itself */
    SDL_Renderer* r;    /* Rendering Context */
};

/* ================================ */

Window* Window_new(const char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags) {

    Window* w;
    w = NULL;

    /* ================================ */
    /* === Window Memory Allocation === */
    /* ================================ */

    if ((w = calloc(1, sizeof(struct _window))) == NULL) {
        return NULL;
    }

    /* ================================ */
    /* ===== Creating SDL_Window ====== */
    /* ================================ */

    /* The window is always centered */
    if ((w->w = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags)) == NULL) {

        /* Deallocating a `Window` container */
        free(w);

        return NULL;
    }

    /* ================================ */
    /* ==== Creating SDL_Renderer ===== */
    /* ================================ */

    if ((w->r = SDL_CreateRenderer(w->w, -1, renderer_flags)) == NULL) {
        
        /* Destroying a `SDL_Renderer` object */    
        SDL_DestroyWindow(w->w);
        /* Deallocating a `Window` container */
        free(w);

        return NULL;
    }

    /* ======== */

    return w;
}

/* ================================ */

int Window_destroy(Window** window) {
    
    if ((window == NULL) || (*window == NULL)) {
        return -1;
    }

    /* ================================ */
    /* === Destroying SDL_Renderer ==== */
    /* ================================ */
    
    if ((*window)->r) {
        SDL_DestroyRenderer((*window)->r);
    }

    /* ================================ */
    /* ==== Destroying SDL_Window ===== */
    /* ================================ */

    if ((*window)->w) {
        SDL_DestroyWindow((*window)->w);
    }

    /* ================================ */
    /* === Deallocating a Container === */
    /* ================================ */

    free(*window);
    *window = NULL;

    /* ======== */

    return 0;
}

/* ================================ */

SDL_Renderer* Window_get_context(const Window* window) {

    if (window != NULL) {
        return window->r;
    }

    /* ======== */

    return NULL;
}

/* ================================================================ */
