#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Start.h"

/* ================================================================ */

/* ================================ */

int main(int argc, char** argv) {

	SDL_Event event;
    SDL_Renderer* ctx;

	TTF_Font* font = NULL;
	Text* fps = NULL;
	Texture* bg = NULL;

    /* Initialize the framework: set up the initial configurations and initialize SDL2 library */
    if (Start() != SSUCCESS) {

        error(stderr, "%s\n", Error_string());
        Stop();

        /* ======== */
        return EXIT_FAILURE;
    }

    /* Create a basic application. You can modify it by manually configuring a file at `configs/application.conf` and `configs.system` */
    if (App_init() != SSUCCESS) {

        error(stderr, "%s\n", Error_string());
        Stop();

        /* ======== */
        return EXIT_FAILURE;
    }

	ctx = get_context();

    /* Opening a TTF font */
	font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 32);

	fps = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "FPS: ");
	bg = Texture_new(ctx, "../resources/images/asset.png");

	App_setFPS(60);

	/* ================================================================ */
	/* =========================== GAME LOOP ========================== */
	/* ================================================================ */

	while (App_isRunning()) {

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_QUIT: 
					{ App_stop(); }
					/* ======== */
					break ;
			}
		}

		SDL_SetRenderDrawColor(ctx, 255, 255, 255, 255);
		SDL_RenderClear(ctx);

		Texture_drawM(bg, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
		Text_draw(fps, &(SDL_Rect) {16, 16, fps->width, fps->height});

		App_render();

		sprintf(fps->content, "FPS: %d", get_fps());
		Text_update(fps, fps->content);		
	}	
	
	Text_destroy(&fps);
	Texture_destroy(&bg);
	TTF_CloseFont(font);

	App_stop();
	Stop();

	/* ======== */
	return EXIT_SUCCESS;
}

/* ================================================================ */
