#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Application.h"
#include "../../include/Window.h"
#include "../../include/Clock.h"
#include "../../include/Text.h"
#include "../../include/Widget/Button/Button.h"
#include "../../include/Widget/Widget.h"
#include "../../include/Widget/Menu.h"
#include "../../include/Math/Vector2D.h"
#include "../../include/Input.h"
#include "../../include/State/State.h"

/* Contains information about user-defined states */
#include "User/States.h"

/* ================================================================ */

int main(int argc, char** argv) {

    Start();
    App_init();

    /* ================================ */

    SDL_Event event;
    SDL_Renderer* r = get_context();

    TTF_Font* font1 = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 48);
    Text* text = Text_new(r, font1, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");
    SDL_Rect text_pos = {32, 32, text->width, text->height};
    char fps_buf[32];

    App_setFPS(60);

    void* current_state = State_create(MainMenu_State, font);
    set_state(current_state);

    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

				case SDL_QUIT:
					App_stop();
					break ;
			}
        }

        Input_update();
        State_handle(get_state());

        /* ================ */

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

        Text_draw(text, &text_pos);

        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        State_update(get_state());

        sprintf(fps_buf, "FPS: %d", get_fps());
        Text_update(text, fps_buf);

        App_render();
    }

    /* ================================ */

    State_destroy(get_state());
    App_quit();

    TTF_CloseFont(font);
    TTF_CloseFont(font1);

    /* ======== */

    return 0;
}

/* ================================================================ */
