#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    Start();
    App_init(NULL);

    /* ================ */

    SDL_Event event;
    SDL_Renderer* context = get_context();

    while(App_isRunning()) {

        while(SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:
                    App_stop();
                    break ;
            }
        }

        /* ================================ */

        SDL_SetRenderDrawColor(context, 255, 255, 255, 255);
        SDL_RenderClear(context);

        App_render();
    }

    /* ================ */

    App_quit();
    Stop();

    /* ========= */

    return 0;
}

/* ================================================================ */
