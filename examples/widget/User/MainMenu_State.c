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

struct main_menu_state {

    const void* state;

    /* Menu to display while being in the state of `MainMenu`*/
    Menu* menu;

    TTF_Font* font;
};

/* ================================================================ */
/* ====================== CALLBACK FUNCTIONS ====================== */
/* ================================================================ */

static void quit_game(va_list* app) {

    struct main_menu_state* self = va_arg(*app, void*);

    State_destroy(self);

    printf("See you!\n");
    
    App_stop();
}

/* ================================================ */

static void start_game(va_list* app) {

    struct main_menu_state* self = va_arg(*app, void*);

    State_destroy(get_state());
    set_state(State_create(Game_State, self->font));
}

/* ================================================ */

static void open_settings(va_list* app) {

    struct main_menu_state* self = va_arg(*app, void*);

    State_destroy(get_state());
    set_state(State_create(Setting_State, self->font));
}

/* ================================================ */

static void load_game(va_list* app) {

    struct main_menu_state* self = va_arg(*app, void*);

    State_destroy(get_state());
    set_state(State_create(LoadGame_State, self->font));
}

/* ================================================================ */

static void* MainMenu_ctor(void* _self, va_list* app) {
    
    struct main_menu_state* self = _self;
    TTF_Font* font = va_arg(*app, TTF_Font*);
    Vector2 menu_d;
    self->font = font;

    /* Just create a menu */
    self->menu = Menu_new(4, &(Vector2) {0, 0});

    void* quit_btn = Widget_create(Button, font, &(SDL_Color) {0, 0, 0, 255}, "Exit", &(Vector2) {0, 0});
    Widget_bind_callback(quit_btn, quit_game);

    void* start_btn = Widget_create(Button, font, &(SDL_Color) {0, 0, 0, 255}, "New Game", &(Vector2) {0, 0});
    Widget_bind_callback(start_btn, start_game);
    
    void* settings_btn = Widget_create(Button, font, &(SDL_Color) {0, 0, 0, 255}, "Settings", &(Vector2) {0, 0});
    Widget_bind_callback(settings_btn, open_settings);

    void* load_btn = Widget_create(Button, font, &(SDL_Color) {0, 0, 0, 255}, "Load", &(Vector2) {0, 0});
    Widget_bind_callback(load_btn, load_game);

    Menu_pack(self->menu, start_btn);
    Menu_pack(self->menu, load_btn);
    Menu_pack(self->menu, settings_btn);
    Menu_pack(self->menu, quit_btn);

    /* Position a menu at the center of the window */
    Menu_get_dimensions(self->menu, &menu_d);
    Menu_set_position(self->menu, 640 / 2 - menu_d.x / 2, 480 / 2 - menu_d.y / 2);

    /* ======== */

    return self; 
}

/* ================================================================ */

static void* MainMenu_dtor(void* _self) {

    struct main_menu_state* self = _self;

    Menu_destroy(&self->menu);

    /* ======== */

    return _self;
}

/* ================================================================ */

static void MainMenu_handle(void* _self, va_list* app) {

    struct main_menu_state* self = _self;

    Menu_update(self->menu);
}

/* ================================================================ */

static void MainMenu_update(void* _self, va_list* app) {

    struct main_menu_state* self = _self;

    Menu_draw(self->menu, CENTER);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct state _MainMenu_State = {

    .size = sizeof(struct main_menu_state),

    .ctor = MainMenu_ctor,
    .dtor = MainMenu_dtor,
    
    .handle = MainMenu_handle,
    .update = MainMenu_update,
};

const void* MainMenu_State = &_MainMenu_State;

/* ================================================================ */
