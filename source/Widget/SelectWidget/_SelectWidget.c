#include "../../../include/Widget/Widgets.h"
#include "../../../include/Widget/_Class.h"
#include "../../../include/Widget/_Widget.h"
#include "../../../include/Widget/Widget.h"
#include "../../../include/Widget/SelectWidget/_SelectWidget.h"

#include "../../../include/Application.h"
#include "../../../include/Error.h"

/* ================================================================ */

/**
 * 
 */
static void* SelectWidget_ctor(void* _self, va_list* args) {

    /* === Calling a parent class constructor === */
    struct select_widget* self = ((const struct Class*) Widget)->ctor(_self, args);
    /* Parent class widget. Provides information such as its position and size */
    struct widget* widget = _self;
    /* ======== */

    List_init(&self->options, NULL);

    /* ======== */
    return self;
}

/* ================================================================ */

static void* SelectWidget_dtor(void* _self) {

    struct select_widget* self = _self;
    /* ======== */

    List_destroy(&self->options);
    Text_destroy(&self->text_option);
    
    /* ======== */
    return self;
}

/* ================================================================ */

/**
 * 
 */
static int SelectWidget_draw(const void* _self, const SDL_Rect* src, const SDL_Rect* dst) {

    /* Base widget class. Provides information such as its position and size */
    const struct widget* widget = _self;
    const struct select_widget* self = _self;

    /* ======== */

    /* If `dst` is not specified, use the one specified in the constructor */
    Text_draw(widget->label, (dst == NULL) ? &(SDL_Rect) {widget->x, widget->y, widget->width, widget->height} : dst);

    if (self->options.size > 0) {
        Text_draw(self->text_option, &self->option_dst);
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct Class _SelectWidget = {

    .size = sizeof(struct select_widget),

    .ctor = SelectWidget_ctor,
    .dtor = SelectWidget_dtor,

    .draw = SelectWidget_draw,
};

const void* SelectWidget = &_SelectWidget;

/* ================================================================ */
