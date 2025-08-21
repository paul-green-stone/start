#ifndef _START_STATE_CLASS_H
#define _START_STATE_CLASS_H

#include <stdio.h>
#include <stdarg.h>

/* ================================================================ */

struct state {

    size_t size;                                    /* How much memory to allocate */

    void* (*ctor)(void* self, va_list* app);        /* How to initialize the memory area */
    void* (*dtor)(void* self);                      /* How to deinitialize the memory area */

    void (*handle)(void* self, va_list* app);       /* How to switch to another states within the current one */
    void (*update)(void* self, va_list* app);       /* How to update a state */         
};

/* ================================================================ */

#endif /* _START_STATE_CLASS_H */
