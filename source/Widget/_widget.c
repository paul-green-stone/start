#include "../../include/Widget/_Class.h"
#include "../../include/Widget/_Widget.h"

/* ================================================================ */

static void* Widget_ctor(void* _self, va_list* args) {

    struct widget* self = _self;
    /* ======== */

    self->x = va_arg(*args, int);
    self->y = va_arg(*args, int);

    /* ======== */
    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct Class _Widget = {

    .size = sizeof(struct widget),

    .ctor = Widget_ctor,
    .dtor = NULL,
};

const void* Widget = &_Widget;

/* ================================================================ */
