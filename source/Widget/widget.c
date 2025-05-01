#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../../include/Widget/Widget.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Text.h"

/* ================================================================ */

void* Widget_create(const void* _widget_descriptor, ...) {

    /* Table of pointers to functions */
    const struct widget* widget_descriptor;
    void* new_widget;
    va_list ap;

    /* ======== */

    widget_descriptor = _widget_descriptor;
    new_widget = NULL;

    if ((new_widget = calloc(1, widget_descriptor->size)) == NULL) {
        return NULL;
    }

    *(const struct widget**) new_widget = widget_descriptor;

    if (widget_descriptor->ctor) {

        va_start(ap, _widget_descriptor);
        new_widget = widget_descriptor->ctor(new_widget, &ap);
        va_end(ap);
    }

    /* ======== */

    return new_widget;
}

/* ================================================================ */

int Widget_destroy(void* widget) {

    const struct widget** widget_descriptor_p;
    widget_descriptor_p = widget;

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->dtor != NULL)) {
        widget = (*widget_descriptor_p)->dtor(widget);
    }
    else {
        return -1;
    }

    free(widget);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Widget_draw(const void* widget, const SDL_Rect* dst) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->draw != NULL)) {
        return (*widget_descriptor_p)->draw(widget, dst);
    }

    return -1;
}

/* ================================================================ */

int Widget_get_dimensions(const void* widget, Vector2* dimensions) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->get_dimensions != NULL) && (dimensions != NULL)) {
        *dimensions = (*widget_descriptor_p)->get_dimensions(widget);

        /* ======== */

        return 0;
    }

    /* ======== */

    return -1;
}

/* ================================================================ */

Text* Widget_get_label(const void* widget) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->get_dimensions != NULL)) {
        return (*widget_descriptor_p)->get_label(widget);
    }

    /* ======== */

    return NULL;
}

/* ================================================================ */

int Widget_bind_callback(void* widget, action callback) {

    const struct widget* const* widget_p;
    widget_p = widget;

    if ((widget != NULL) && (*widget_p != NULL) && ((*widget_p)->bind != NULL)) {

        (*widget_p)->bind(widget, callback);

        /* ======== */

        return 0;
    }

    return -1;
}

/* ================================================================ */

int Widget_handle_click(const void* widget, ...) {

    const struct widget* const* widget_p;
    va_list ap;

    /* ======== */
    
    widget_p = widget;

    if ((widget != NULL) && (*widget_p != NULL) && ((*widget_p)->handle_click != NULL)) {

        va_start(ap, widget);
        (*widget_p)->handle_click(widget, &ap);
        va_end(ap);

        /* ======== */

        return 0;
    }

    return -1;
}

/* ================================================================ */
