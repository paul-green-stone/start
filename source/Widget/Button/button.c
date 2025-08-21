#include "../../../include/Widget/Button/_Button.h"
#include "../../../include/Widget/Button/Button.h"

#include "../../../include/Error.h"

/* ================================================================ */

int Button_set_texture(void* _self, Texture* texture) {

    struct button* self = _self;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (_self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    /* === Assigning `NULL` will remove the texture from the button === */
    self->texture = texture;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Button_set_label_color(void* _self, const SDL_Color* color) {

    struct button* self = _self;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (_self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    /* === Setting a new color === */
    return Text_set_color(self->label, color);
}

/* ================================================================ */
