#include "../../../include/Widget/Widgets.h"
#include "../../../include/Widget/_Class.h"
#include "../../../include/Widget/_Widget.h"
#include "../../../include/Widget/TextInput/_TextInput.h"
#include "../../../include/Widget/TextInput/TextInput.h"

#include "../../../include/Application.h"
#include "../../../include/Error.h"

/* ================================================================ */

int TextInput_update(void* _self, SDL_Event* e) {

    struct text_input* self = _self;
    struct widget* widget = _self;
    int length;
    /* ======== */

    /* === Do not dereference `NULL === */
    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Writing a character === */
    if (e->type == SDL_TEXTINPUT) {
        self->input->content[self->curr_pos++] = *(e->text.text);

        self->input->content[strlen(self->input->content)] = '>';
    }
    /* === Deleting a character === */
    else if ((e->type == SDL_KEYDOWN) && (e->key.keysym.sym == SDLK_BACKSPACE)) {

        /* === Getting the number of characters in the field === */
        length = strlen(self->input->content);

        if (length != 2) {
            
            /* === "Shifting" === */
            self->input->content[--self->curr_pos] = '>';
            self->input->content[length - 1] = '\0';
        }
    }

    /* === Updating the text and the size of the field === */
    Text_update(self->input, self->input->content);
    self->ifd.w = self->input->width;
    self->ifd.h = self->input->height;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int TextInput_get_input(const void* _self, char* buffer) {

    const struct text_input* self = _self;

    size_t j = 0;
    size_t size;
    /* ======== */

    /* === Do not dereference `NULL === */
    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === The maximum number of characters to copy (this includes both opening '<' and closing '>') === */
    size = sizeof(self->input->content);

    /* === We are omiting '<' and '>' (does not include '<' and '>') === */
    for (size_t i = 1; i < size;) {
        buffer[j++] = self->input->content[i++];
    }

    /* === Marking the end of the string === */
    buffer[strlen(buffer) - 1] = '\0';

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
