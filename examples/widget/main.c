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

int main(int argc, char** argv) {

    /* SDL Library Initialization */
	SDL_Init(SDL_INIT_TIMER);
	/* TTF Library Initialization */
	TTF_Init();

    App_init("Start Application", 640, 480);

    /* ================================ */

    SDL_Event event;
    SDL_Renderer* r = get_context();

    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);
    Text* text = Text_new(r, font, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");
    SDL_Rect text_pos = {32, 32, text->width, text->height};
    char fps_buf[32];

    Menu* menu = Menu_new(3, &(Vector2) {128, 128});
    Menu_set_padding(menu, &(Vector2) {0, 24});

    Vector2 bd;
    void* button = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Button 1", &(Vector2) {64.0f, 64.0f});
    void* button2 = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Button 2", &(Vector2) {64.0f, 64.0f});
    void* button3 = Widget_create(Button, font, &(SDL_Color){0, 0, 0, 255}, "Long Button", &(Vector2) {64.0f, 64.0f});
    
    Widget_get_dimensions(button, &bd);

    Menu_pack(menu, button);
    Menu_pack(menu, button2);
    Menu_pack(menu, button3);

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

        Menu_update(menu, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

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

    /* ======== */

    return 0;
}

/* ================================================================ */
