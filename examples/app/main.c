#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Application.h"
#include "../../include/Window.h"
#include "../../include/Clock.h"
#include "../../include/Text.h"

/* ================================================================ */

int main(int argc, char** argv) {

    
    Start();
    App_init(NULL);

    /* ================================ */

    SDL_Event event;
    SDL_Renderer* r = get_context();

    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);
    Text* text = Text_new(r, font, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");
    SDL_Rect text_pos = {32, 32, text->width, text->height};
    char fps_buf[32];

    double counter = 0.0f;

    App_setFPS(45);

    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

				case SDL_QUIT:
					App_stop();
					break ;
			}
        }

        /* ================ */

        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

        Text_draw(text, &text_pos);

        sprintf(fps_buf, "FPS: %d", get_fps());
        Text_update(text, fps_buf);

        App_render();

        printf("Delta time: %f\n", get_delta());
    }

    /* ================================ */

    App_quit();
    Stop();

    /* ======== */
    return 0;
}

/* ================================================================ */
