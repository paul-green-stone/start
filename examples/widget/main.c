#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Application.h"
#include "../../include/Window.h"
#include "../../include/Clock.h"
#include "../../include/Text.h"
#include "../../include/Widget/Button.h"
#include "../../include/Widget/Widget.h"
#include "../../include/Widget/Menu.h"
#include "../../include/Math/Vector2D.h"
#include "../../include/Input.h"

/* ================================================================ */

void quit(void* data) {
    printf("Exiting the game...\n");
    App_stop();
}

void start_game(void* data) {
    printf("Starting a new game...\n");
}

void load_game(void* data) {
    printf("Loading the game...\n");
}

void open_settings_menu(void* data) {
    printf("Opening a settings window...\n");
}

/* ================================================================ */

int main(int argc, char** argv) {

    /* SDL Library Initialization */
	SDL_Init(SDL_INIT_TIMER);
	/* TTF Library Initialization */
	TTF_Init();

    App_init("Start Application", 640, 480);

    /* ================================ */

    SDL_Event event;
    SDL_Renderer* r = get_context();

    TTF_Font* font1 = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 48);
    Text* text = Text_new(r, font1, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");
    SDL_Rect text_pos = {32, 32, text->width, text->height};
    char fps_buf[32];

    Menu* menu = Menu_new(4, &(Vector2) {640 / 2, 480 / 2});
    Menu_set_padding(menu, &(Vector2) {0, 24});

    Vector2 menu_d;

    void* new_game = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "New Game", &(Vector2) {64.0f, 64.0f});
    void* load = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Load", &(Vector2) {64.0f, 64.0f});
    void* settings = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Settings", &(Vector2) {64.0f, 64.0f});
    void* exit = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Exit", &(Vector2) {64.0f, 64.0f});

    Widget_bind_callback(new_game, start_game);
    Widget_bind_callback(load, load_game);
    Widget_bind_callback(settings, open_settings_menu);
    Widget_bind_callback(exit, quit);

    Menu_pack(menu, new_game);
    Menu_pack(menu, load);
    Menu_pack(menu, settings);
    Menu_pack(menu, exit);

    Menu_get_dimensions(menu, &menu_d);
    Menu_set_position(menu, 640 / 2 - menu_d.x / 2, 480 / 2 - menu_d.y / 2);

    App_setFPS(60);

    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

				case SDL_QUIT:
					App_stop();
					break ;
			}
        }

        Input_update();

        Menu_update(menu, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_SPACE);

        /* ================ */

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

        Text_draw(text, &text_pos);

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        Menu_draw(menu, CENTER);

        sprintf(fps_buf, "FPS: %d", get_fps());
        Text_update(text, fps_buf);

        App_render();
    }

    /* ================================ */

    Menu_destroy(&menu);
    App_quit();

    TTF_CloseFont(font);
    TTF_CloseFont(font1);

    /* ======== */

    return 0;
}

/* ================================================================ */
