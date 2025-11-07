#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Start.h"

/* ================================================================ */

void bar(Text* t) {

	static int width;
	static int height;

	SDL_GetWindowSize(get_window(), &width, &height);

    SDL_Rect rect = {width / 2 - t->width / 2, height / 2 - t->height / 2, t->width, t->height};

    if (Input_isKey_pressed(SDL_SCANCODE_A)) {
        Text_update(t, "\"A\" is pressed");
    }
    else if (Input_isKey_pressed(SDL_SCANCODE_B)) {
        Text_update(t, "\"B\" is pressed");
    }
    else if (Input_isKey_pressed(SDL_SCANCODE_C)) {
        Text_update(t, "\"C\" is pressed");
    }
    else if (Input_isKey_pressed(SDL_SCANCODE_D)) {
        Text_update(t, "\"D\" is pressed");
    }

    Text_draw(t, &rect);
}

/* ================================ */

int main(int argc, char** argv) {

	SDL_Event event;
	SDL_Renderer* ctx;
	TTF_Font* font;
	Text* _t = NULL;
	Text* fps = NULL;

    /* Initialize the framework: set up the initial configurations and initialize SDL2 library */
    if (Start() != SSUCCESS) {

        error(stderr, "%s\n", Error_string());
        Stop();

        /* ======== */
        return EXIT_FAILURE;
    }

    /* Create a basic application. You can modify it by manually configuring a file `configs/application.conf` and `configs.system` */
    if (App_init() != SSUCCESS) {

        error(stderr, "%s\n", Error_string());
        Stop();

        /* ======== */
        return EXIT_FAILURE;
    }

	ctx = get_context();

    /* Opening a TTF font */
	font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 32);

	char fps_buf[32] = "FPS: 60";

    _t = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "What key did you just press?");
	fps = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "What key did you just press?");

	App_setFPS(55);

	/* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
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

        Input_update();

		/* The bar function renderes the text */
        bar(_t);
		Text_draw(fps, &(SDL_Rect) {16, 16, fps->width, fps->height});

		App_render();

		sprintf(fps_buf, "FPS: %d", get_fps());
		Text_update(fps, fps_buf);
	}	

	Text_destroy(&fps);
	Text_destroy(&_t);

	TTF_CloseFont(font);
	
	/* Deinitializes the application and its core systems */
	App_quit();
	Stop();

	/* ======== */
	return EXIT_SUCCESS;
}

/* ================================================================ */
