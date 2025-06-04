#include "../../../include/Widget/Widgets.h"
#include "../../../include/Widget/_Class.h"
#include "../../../include/Widget/_Widget.h"
#include "../../../include/Widget/Button/_Button.h"

#include "../../../include/Application.h"

/* ================================================================ */

static void* Button_ctor(void* _self, va_list* args) {

    /* === Calling a parent class constructor === */
    struct button* self = ((const struct Class*) Widget)->ctor(_self, args);
    struct widget* widget = _self;

    TTF_Font* font = va_arg(*args, TTF_Font*);
    SDL_Color* label_color = va_arg(*args, SDL_Color*);
    const char* label = va_arg(*args, const char*);
    Texture* btn_texture = va_arg(*args, Texture*);
    /* ======== */

    /* === Check if the label has been provided === */
    if ((font != NULL) && (label != NULL)) {

        /* === Creating a button's label === */
        if ((self->label = Text_new(get_context(), font, (label_color == NULL) ? &(SDL_Color) {0, 0, 0, 255} : label_color, label)) == NULL) {
            return NULL;
        }

        /* === Updating the widget's dimensions === */
        widget->width = self->label->width;
        widget->height = self->label->height;
    }

    self->texture = btn_texture;

    /* === Updating the widget's dimensions === */
    if (self->texture != NULL) {
        Texture_get_dimensions(self->texture, &widget->width, &widget->height);
    }

    /* ======== */
    return self;
}

/* ================================================================ */

static void* Button_dtor(void* _self) {

    struct button* self = _self;
    /* ======== */

    /* === Destroying the button's label (`Text`) === */
    Text_destroy(&self->label);

    /* === `Texture` is typically an atlas of images that might contain not only the button's texture but also other images === */
    /* === this is why we don't destroy the texture here; make sure to delete it elsewhere when it is no longer needed === */

    /* ======== */
    return self;
}

/* ================================================================ */

/**
 * @param dst If no `dst` rectangle is provided, the button is rendered at the widget's position (x, y) with the widget's width and height
 */
static int Button_draw(const void* _self, const SDL_Rect* src, const SDL_Rect* dst) {

    const struct button* self = _self;
    const struct widget* widget = _self;

    /* === This is where we are going to render the button === */
    SDL_Rect dest = {widget->x, widget->y, widget->width, widget->height};
    /* ======== */

    /* === Render the button's label if it has one === */
    if (self->label != NULL) {
        return Text_draw(self->label, &dest);
    }

    /* === Render the button's texture if it has one and does not have a label === */
    return Texture_draw(self->texture, src, (dst == NULL) ? &dest : dst);
} 

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct Class _Button = {

    .size = sizeof(struct button),

    .ctor = Button_ctor,
    .dtor = Button_dtor,

    .draw = Button_draw,
};

const void* Button = &_Button;

/* ================================================================ */
