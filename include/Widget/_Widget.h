#ifndef _START_WIDGET_CLASS_H
#define _START_WIDGET_CLASS_H

#include <stdio.h>
#include <stdarg.h>
#include <SDL2/SDL.h>

#include "../Math/Vector2D.h"
#include "../Text.h"
#include "../Application.h"

/* ================================================================ */

struct widget {
    
    /* The amount of memory to allocate (in bytes) */
    size_t size;

    /* Widget's constructor */
    void* (*ctor)(void* self, va_list* app);
    /* Widget's destructor */
    void* (*dtor)(void* self);

    /* How to draw a widget on the screen*/
    int (*draw)(const void* self, const SDL_Rect* dst);
    /* What are the widget's dimensions and how to retrieve them */
    Vector2 (*get_dimensions)(const void* self);
    /* How to retrieve the widget's label */
    Text* (*get_label)(const void* self);

    void (*bind)(void* self, void (*callback)(va_list* app));
    void (*handle_click)(const void* self, va_list* app);
    void (*on_hover)(const void* self, void (*callback)(va_list* app));
};

/* ================================================================ */

#endif /* _START_WIDGET_CLASS_H */
