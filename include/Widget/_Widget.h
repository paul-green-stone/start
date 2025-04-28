#ifndef _START_WIDGET_CLASS_H
#define _START_WIDGET_CLASS_H

#include <stdio.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

#include "../Math/Vector2D.h"
#include "../Text.h"

/* ================================================================ */

struct widget {
    
    /* The amount of memory to allocate (in bytes) */
    size_t size;

    /* Widget's constructor */
    void* (*ctor)(void* self, va_list* app);
    /* Widget's destructor */
    void* (*dtor)(void* self);

    int (*draw)(const void* self, const SDL_Rect* dst);
    Vector2 (*get_dimensions)(const void* self);
    Text* (*get_label)(const void* self);
};

/* ================================================================ */

#endif /* _START_WIDGET_CLASS_H */
