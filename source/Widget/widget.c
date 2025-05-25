#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../../include/Widget/Widget.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Text.h"
#include "../../include/Error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

void* Widget_create(const void* _widget_descriptor, ...) {

    const struct widget* widget_descriptor = _widget_descriptor; /* Table of pointers to functions */ 
    void* new_widget = NULL;
    va_list ap;
    int status = SSUCCESS;
    /* ======== */

    if (_widget_descriptor == NULL) {

        status = SERR_NULL_POINTER;
        /* ======== */
        goto ERROR;
    }

    if ((new_widget = calloc(1, widget_descriptor->size)) == NULL) {

        status = SERR_SYSTEM;
        /* ======== */
        goto ERROR;
    }

    *(const struct widget**) new_widget = widget_descriptor;

    if (widget_descriptor->ctor) {

        va_start(ap, _widget_descriptor);
        new_widget = widget_descriptor->ctor(new_widget, &ap);
        va_end(ap);
    }

    /* ======== */
    return new_widget;

    /* ================ */
    ERROR: {

        Error_set(status);
        /* ======== */
        return new_widget;
    };
}

/* ================================================================ */

int Widget_destroy(void* widget) {

    const struct widget** widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ======== */

    if ((widget != NULL) && (*widget_descriptor_p != NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if ((*widget_descriptor_p)->dtor != NULL) {
        widget = (*widget_descriptor_p)->dtor(widget);
    }

    free(widget);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_draw(const void* widget, const SDL_Rect* dst) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ======== */

    if ((widget == NULL) && (*widget_descriptor_p == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if ((*widget_descriptor_p)->draw != NULL) {
        return (*widget_descriptor_p)->draw(widget, dst);
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ======== */
    return SERR_NOT_IMPLEMENTED;
}

/* ================================================================ */

int Widget_get_dimensions(const void* widget, Vector2* dimensions) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ========= */

    if ((widget == NULL) && (*widget_descriptor_p == NULL) && (dimensions == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if ((*widget_descriptor_p)->get_dimensions != NULL) {

        *dimensions = (*widget_descriptor_p)->get_dimensions(widget);
        /* ======== */
        return SSUCCESS;
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ======== */
    return SERR_NOT_IMPLEMENTED;    /* Method is not implemented */
}

/* ================================================================ */

Text* Widget_get_label(const void* widget) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ======== */

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->get_label != NULL)) {
        return (*widget_descriptor_p)->get_label(widget);
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ======== */
    return NULL;    /* Method is not implemented */
}

/* ================================================================ */

int Widget_bind_callback(void* widget, action callback) {

    const struct widget* const* widget_p;
    widget_p = widget;
    /* ======== */

    if ((widget != NULL) && (*widget_p != NULL) && ((*widget_p)->bind != NULL)) {

        (*widget_p)->bind(widget, callback);
        /* ======== */
        return SSUCCESS;
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ======== */
    return SERR_NOT_IMPLEMENTED;    /* Method is not implemented */
}

/* ================================================================ */

int Widget_handle_click(const void* widget, ...) {

    const struct widget* const* widget_p = widget;
    va_list ap;
    /* ======== */

    if ((widget == NULL) && (*widget_p == NULL)) {
        return SERR_NULL_POINTER;
    }
    
    if ((*widget_p)->handle_click != NULL) {

        va_start(ap, widget);
        (*widget_p)->handle_click(widget, &ap);
        va_end(ap);

        /* ======== */
        return SSUCCESS;
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ========= */
    return SERR_NOT_IMPLEMENTED;      /* Method is not implemented */
}

/* ================================================================ */

int Widget_set_position(void* _widget, const Vector2* position) {

    const struct widget* const* widget_p = _widget;
    /* ======== */

    if ((_widget == NULL) || (widget_p == NULL) || (position == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if ((*widget_p)->set_position != NULL) {

        (*widget_p)->set_position(_widget, position);
        /* ======== */
        return SSUCCESS;
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ========= */
    return SERR_NOT_IMPLEMENTED;      /* Method is not implemented */
}

/* ================================================================ */
