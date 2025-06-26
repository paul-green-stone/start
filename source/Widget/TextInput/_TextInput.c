#include "../../../include/Widget/Widgets.h"
#include "../../../include/Widget/_Class.h"
#include "../../../include/Widget/_Widget.h"
#include "../../../include/Widget/TextInput/_TextInput.h"

#include "../../../include/Application.h"

/* ================================================================ */

static void* TextInput_ctor(void* _self, va_list* args) {

    /* === Calling a parent class constructor === */
    struct text_input* self = ((const struct Class*) Widget)->ctor(_self, args);
    struct widget* widget = _self;
    /* ======== */
    
    /* === Check if the label has been provided === */
    if ((self->input = Text_new(get_context(), widget->label->font, &widget->label->color, "<>")) == NULL) {
        return NULL;
    }

    self->curr_pos = 1;

    /* === Updating the widget's dimensions === */
    self->ifd = (SDL_Rect) {.x = widget->x + widget->label->width + 16, .y = widget->y, .w = self->input->width, .h = self->input->height};

    /* ======== */
    return self;
}

/* ================================================================ */

static void* TextInput_dtor(void* _self) {

    struct text_input* self = _self;
    /* ======== */

    /* === Destroying the widget's label (`Text`) === */
    Text_destroy(&self->input);

    /* ======== */
    return self;
}

/* ================================================================ */

static int TextInput_draw(const void* _self, const SDL_Rect* src, const SDL_Rect* dst) {

    const struct text_input* self = _self;
    const struct widget* widget = _self;

    /* === This is where we are going to render the widget === */
    SDL_Rect dest = {widget->x, widget->y, widget->width, widget->height};
    /* ======== */

    /* === Render the widget's label if it has one === */
    Text_draw(widget->label, &dest);
    Text_draw(self->input, &self->ifd);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct Class _TextInput = {

    .size = sizeof(struct text_input),

    .ctor = TextInput_ctor,
    .dtor = TextInput_dtor,

    .draw = TextInput_draw,
};

const void* TextInput = &_TextInput;

/* ================================================================ */
