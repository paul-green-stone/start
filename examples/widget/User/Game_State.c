#include "../../../include/Start.h"
#include "../../../include/State/_State.h"
#include "../../../include/Widget/Menu.h"
#include "../../../include/State/State.h"
#include "../../../include/Widget/Widget.h"
#include "../../../include/Widget/Button.h"
#include "States.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* ================================================================ */

struct game_state {

    const void* state;

    Text* game_text;
    TTF_Font* font;
};

/* ================================================================ */

void* Game_ctor(void* _self, va_list* app) {

    struct game_state* self = _self;
    TTF_Font* font = va_arg(*app, TTF_Font*);
    self->font = font;

    self->game_text = Text_new(get_context(), font, &(SDL_Color) {0, 0, 0, 255}, "Game's Running");

    /* ======== */

    return _self;
}

/* ================================================================ */

void* Game_dtor(void* _self) {

    struct game_state* self = _self;

    Text_destroy(&self->game_text);

    /* ======== */

    return _self;
}

/* ================================================================ */

void Game_handle(void* _self, va_list* app) {

    struct game_state* self = _self;

    if (Input_wasKey_pressed(SDL_SCANCODE_BACKSPACE)) {

        State_destroy(get_state());
        set_state(State_create(MainMenu_State, self->font));
    }
}

/* ================================================================ */

void Game_update(void* _self, va_list* app) {

    struct game_state* self = _self;
    SDL_Rect dest = {.x = 640 / 2 - self->game_text->width / 2, .y = 480 / 2 - self->game_text->height / 2, .w = self->game_text->width, .h = self->game_text->height};

    Text_draw(self->game_text, &dest);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state _Game_State = {

    .size = sizeof(struct game_state),

    .ctor = Game_ctor,
    .dtor = Game_dtor,
    
    .handle = Game_handle,
    .update = Game_update,
};

const void* Game_State = &_Game_State;  

/* ================================================================ */
