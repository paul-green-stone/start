#ifndef _START_CLASS_H
#define _START_CLASS_H

#include <stdarg.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/* ================================================================ */

struct Class {

    size_t size;

    /* The widget constructor */
    void *(*ctor)(void *self, va_list *args);
    /* The widget destructor */
    void *(*dtor)(void *self);

    /* ================ */

    int (*draw)(const void *self, const SDL_Rect *src, const SDL_Rect *dst);
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_CLASS_H */
