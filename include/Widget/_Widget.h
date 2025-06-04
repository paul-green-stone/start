#ifndef _START_WIDGET_CLASS_H
#define _START_WIDGET_CLASS_H

#include "_Class.h"

/* ================================================================ */

struct widget {

    const void* _class; /* This is a function pointers table */

    /* === Widget position on the screen === */
    int x;
    int y;

    int is_focused;

    /* === Widget dimensions === */
    int width;
    int height;

    /* === Actions associated with the widget === */
    int (*on_click)(const void* self, va_list* args);
};

/* ================================================================ */

#endif /* _START_WIDGET_CLASS_H */
