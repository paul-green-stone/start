#ifndef _START_WIDGET_CLASS_H
#define _START_WIDGET_CLASS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "_Class.h"
#include "../Text.h"

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

    /* === Widget's label === */
    Text* label;

    /* === Actions associated with the widget === */
    int (*on_click)(const void* self, va_list* args);
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_WIDGET_CLASS_H */
