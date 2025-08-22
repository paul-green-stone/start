#include "../include/Window.h"
#include "../include/Error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct _window {

    SDL_Window*   w;    /* The Window itself */
    SDL_Renderer* r;    /* Rendering Context */
};

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Window* Window_new(const char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags) {

    Window* w = NULL;
    /* ======== */

    /* === Window Memory Allocation === */
    if ((w = calloc(1, sizeof(struct _window))) == NULL) {
        
        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* ===== Creating SDL_Window ====== */
    if ((w->w = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags)) == NULL) {

        /* Deallocating a `Window` container */
        free(w);
        Error_set(SERR_SDL);
        /* ======== */
        return NULL;
    }

    /* ==== Creating SDL_Renderer ===== */
    if ((w->r = SDL_CreateRenderer(w->w, -1, renderer_flags)) == NULL) {
        
        /* Destroying a `SDL_Renderer` object */    
        SDL_DestroyWindow(w->w);
        /* Deallocating a `Window` container */
        free(w);

        Error_set(SERR_SDL);
        /* ======== */
        return NULL;
    }

    /* ======== */
    return w;
}

/* ================================================================ */

int Window_destroy(Window** window) {
    
    /* ====== Do not dereference a NULL pointer ======= */
    if ((window == NULL) || (*window == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Destroying SDL_Renderer ==== */
    if ((*window)->r) {
        SDL_DestroyRenderer((*window)->r);
    }

    /* ==== Destroying SDL_Window ===== */
    if ((*window)->w) {
        SDL_DestroyWindow((*window)->w);
    }

    /* === Deallocating a Container === */
    free(*window);
    *window = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

SDL_Renderer* Window_get_context(const Window* window) {

    /* ====== Do not dereference a NULL pointer ======= */
    if (window != NULL) {
        return window->r;
    }

    Error_set(SERR_NULL_POINTER);

    /* ======== */
    return NULL;
}

/* ================================================================ */

SDL_Window* Window_get_window(const Window* window) {

    /* ====== Do not dereference a NULL pointer ======= */
    if (window != NULL) {
        return window->w;
    }

    Error_set(SERR_NULL_POINTER);

    /* ======== */
    return NULL;
}

/* ================================================================ */
