#ifndef _START_CLASS_H
#define _START_CLASS_H

#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

/* ================================================================ */

struct Class {

    size_t size;

    /* The widget constructor */
    void* (*ctor)(void* self, va_list* args);
    /* The widget destructor */
    void* (*dtor)(void* self);

    /* ================ */

    int (*draw)(const void* self, const SDL_Rect* src, const SDL_Rect* dst);
};

/* ================================================================ */

#endif /* _START_CLASS_H */
