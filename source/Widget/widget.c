#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../../include/Widget/Widget.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Text.h"
#include "../../include/Error.h"
#include "../../include/_error.h"

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

        /* Constructing and updating the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

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

    if ((widget != NULL) && (*widget_descriptor_p != NULL)) {
        return SERR_NULL_POINTER;
    }

    if ((*widget_descriptor_p)->draw != NULL) {
        return (*widget_descriptor_p)->draw(widget, dst);
    }

    /* ======== */
    return SERR_NIMPLMNT;
}

/* ================================================================ */

int Widget_get_dimensions(const void* widget, Vector2* dimensions) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ========= */

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && (dimensions != NULL)) {
        return SERR_NULL_POINTER;
    }

    if ((*widget_descriptor_p)->get_dimensions != NULL) {

        *dimensions = (*widget_descriptor_p)->get_dimensions(widget);
        /* ======== */
        return SSUCCESS;
    }

    /* ======== */
    return SERR_NIMPLMNT;    /* Method is not implemented */
}

/* ================================================================ */

Text* Widget_get_label(const void* widget) {

    const struct widget* const* widget_descriptor_p;
    widget_descriptor_p = widget;
    /* ======== */

    if ((widget != NULL) && (*widget_descriptor_p != NULL) && ((*widget_descriptor_p)->get_dimensions != NULL)) {
        return (*widget_descriptor_p)->get_label(widget);
    }

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

    /* ======== */
    return SERR_NIMPLMNT;    /* Method is not implemented */
}

/* ================================================================ */

int Widget_handle_click(const void* widget, ...) {

    const struct widget* const* widget_p = widget;
    va_list ap;
    /* ======== */

    if ((widget != NULL) && (*widget_p != NULL)) {
        return SERR_NULL_POINTER;
    }
    
    if ((*widget_p)->handle_click != NULL) {

        va_start(ap, widget);
        (*widget_p)->handle_click(widget, &ap);
        va_end(ap);

        /* ======== */
        return SSUCCESS;
    }

    /* ========= */
    return SERR_NIMPLMNT;      /* Method is not implemented */
}

/* ================================================================ */
