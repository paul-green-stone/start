#include "../../../include/Widget/Widgets.h"
#include "../../../include/Widget/_Class.h"
#include "../../../include/Widget/_Widget.h"
#include "../../../include/Widget/SelectWidget/_SelectWidget.h"
#include "../../../include/Widget/SelectWidget/SelectWidget.h"

#include "../../../include/Application.h"
#include "../../../include/Error.h"

/* ================================================================ */

int SelectWidget_next(void* _self) {

    /* Parent class widget. Provides information such as its position and size */
    struct widget* widget = _self;
    struct select_widget* self = _self;
    char buffer[64];
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Type mismatch === */
    if (((struct Class*) self->_._class) != SelectWidget) {
        
        Error_set(SERR_UNKNOWN_TYPE);
        /* ======== */
        return SERR_UNKNOWN_TYPE;
    }

    self->node_option = self->node_option->next;
    /* === Wrapping around === */
    if (self->node_option == NULL) {
        self->node_option = self->options.head;
    }

    memset(buffer, '\0', sizeof(buffer));

    strcat(buffer, "<");
    strcat(buffer, (const char*) self->node_option->data);
    strcat(buffer, ">\0");

    Text_update(self->text_option, buffer);
    self->option_dst = (SDL_Rect) {
        .x = widget->x + widget->label->width + 16,
        .y = widget->y,
        .w = self->text_option->width,
        .h = self->text_option->height
    };

    /* ======= */
    return SSUCCESS;
}

/* ================================================================ */

int SelectWidget_add(void* _self, const char* _option) {

    /* Base widget class. Provides information such as its position and size */
    struct widget* widget = _self;
    struct select_widget* self = _self;

    char buffer[64];
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((self == NULL) || (_option == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Type mismatch === */
    if (((struct Class*) self->_._class) != SelectWidget) {
        
        Error_set(SERR_UNKNOWN_TYPE);
        /* ======== */
        return SERR_UNKNOWN_TYPE;
    }
    
    List_insert_tail(&self->options, (void*) _option);

    /* === Add a default option === */
    if (self->options.size == 1) {

        self->node_option = self->options.head;

        strcat(buffer, "<");
        strcat(buffer, _option);
        strcat(buffer, ">\0");

        if ((self->text_option = Text_new(get_context(), widget->label->font, &widget->label->color, buffer)) == NULL) {
            /* Do not forget to do somethng here */
        }

        self->option_dst = (SDL_Rect) {
            .x = widget->x + widget->label->width + 16,
            .y = widget->y,
            .w = self->text_option->width,
            .h = self->text_option->height
        };
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int SelectWidget_prev(void* _self) {

    /* Parent class widget. Provides information such as its position and size */
    struct widget* widget = _self;
    struct select_widget* self = _self;
    char buffer[64];
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Type mismatch === */
    if (((struct Class*) self->_._class) != SelectWidget) {
        
        Error_set(SERR_UNKNOWN_TYPE);
        /* ======== */
        return SERR_UNKNOWN_TYPE;
    }

    self->node_option = self->node_option->prev;
    /* === Wrapping around === */
    if (self->node_option == NULL) {
        self->node_option = self->options.tail;
    }

    memset(buffer, '\0', sizeof(buffer));

    strcat(buffer, "<");
    strcat(buffer, (const char*) self->node_option->data);
    strcat(buffer, ">\0");

    Text_update(self->text_option, buffer);
    self->option_dst = (SDL_Rect) {
        .x = widget->x + widget->label->width + 16,
        .y = widget->y,
        .w = self->text_option->width,
        .h = self->text_option->height
    };

    /* ======= */
    return SSUCCESS;
}

/* ================================================================ */

const char* SelectWidget_get_value(const void* _self) {

    const struct select_widget* self = _self;
    /* ======== *
    
    /* === Do not dereference `NULL` === */
    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return NULL;
    }

    /* === Type mismatch === */
    if (((struct Class*) self->_._class) != SelectWidget) {
        
        Error_set(SERR_UNKNOWN_TYPE);
        /* ======== */
        return NULL;
    }

    /* ======== */
    return ((const char*) self->node_option->data);
}

/* ================================================================ */
