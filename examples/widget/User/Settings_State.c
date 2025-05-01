#include "States.h"
#include "../../../include/Start.h"
#include "../../../include/State/_State.h"
#include "../../../include/Widget/Menu.h"
#include "../../../include/State/State.h"
#include "../../../include/Widget/Widget.h"
#include "../../../include/Widget/Button.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* ================================================================ */

struct settings_state {

    const void* state;
    
    Text* text;
    TTF_Font* font;
};

/* ================================================================ */

void* Settings_ctor(void* _self, va_list* app) {

    struct settings_state* self = _self;
    TTF_Font* font = va_arg(*app, TTF_Font*);

    self->font = font;

    self->text = Text_new(get_context(), font, &(SDL_Color) {0, 0, 0, 255}, "Controls");

    /* ======== */

    return _self;
}

/* ================================================================ */

void* Settings_dtor(void* _self) {
    
    struct settings_state* self = _self;

    Text_destroy(&self->text);

    /* ======== */

    return _self;
}

/* ================================================================ */

void Settings_handle(void* _self, va_list* ap) {

    struct settings_state* self = _self;

    if (Input_wasKey_pressed(SDL_SCANCODE_BACKSPACE)) {

        State_destroy(get_state());
        set_state(State_create(MainMenu_State, self->font));
    }
}

/* ================================================================ */

void Settings_update(void* _self, va_list* app) {

    struct settings_state* self = _self;
    SDL_Rect dest = {.x = 640 / 2 - self->text->width / 2, .y = 480 / 2 - self->text->height / 2, .w = self->text->width, .h = self->text->height};

    Text_draw(self->text, &dest);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state _Setting_State = {

    .size = sizeof(struct settings_state),

    .ctor = Settings_ctor,
    .dtor = Settings_dtor,
    
    .handle = Settings_handle,
    .update = Settings_update,
};

const void* Setting_State = &_Setting_State;

/* ================================================================ */