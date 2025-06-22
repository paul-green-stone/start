#include "../../include/Widget/_Class.h"
#include "../../include/Widget/_Widget.h"

#include "../../include/Text.h"
#include "../../include/Application.h"

/* ================================================================ */

static void* Widget_ctor(void* _self, va_list* args) {

    struct widget* self = _self;
    /* ======== */

    self->x = va_arg(*args, int);
    self->y = va_arg(*args, int);
    TTF_Font* font = va_arg(*args, TTF_Font*);
    SDL_Color* color = va_arg(*args, SDL_Color*);
    const char* str = va_arg(*args, const char*);
    
    /* === Creating the widget's label === */
    if ((self->label = Text_new(get_context(), font, color == NULL ? &(SDL_Color) {0, 0, 0, 255} : color, str)) == NULL) {
        return NULL;
    }

    /* === Updating the widget's dimensions === */
    self->width = self->label->width;
    self->height = self->label->height;

    /* ======== */
    return self;
}

/* ================================================================ */

static void* Widget_dtor(void* _self) {

    struct widget* self = _self;
    /* ======== */

    Text_destroy(&self->label);

    /* ======= */
    return self;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct Class _Widget = {

    .size = sizeof(struct widget),

    .ctor = Widget_ctor,
    .dtor = Widget_dtor,
};

const void* Widget = &_Widget;

/* ================================================================ */
