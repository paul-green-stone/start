#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

	SDL_Event event;
    SDL_Renderer* ctx;

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

	/* Opening a font by standard library function */
	TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);

	Clock* normal_clock = Clock_new();
	Clock_start(normal_clock);

	Text* normal = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Normal Clock (1x)");
	Text* normal_time_string = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Seconds passed:");

	float normal_time = 0;

	/* ================ */

	Clock* fast_clock = Clock_new();
	Clock_setSpeed(fast_clock, 2.0f);
	Clock_start(fast_clock);

	Text* fast = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Fast Clock (2x)");
	Text* fast_time_string = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Seconds passed:");;
	
	float fast_time = 0;

	/* ================ */

	Text* fps_string = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");

	/* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
    /* ================================================================ */

	int window_width, window_height;
	SDL_GetWindowSize(get_window(), &window_width, &window_height);

	while (App_isRunning()) {

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_QUIT:

					App_stop();
					break ;
			}
		}

		SDL_SetRenderDrawColor(ctx, 255, 255, 255, 255);
		SDL_RenderClear(ctx);

		SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
		SDL_RenderDrawLine(ctx, window_width / 2, 0, window_width / 2, window_height);

		/* ================================================================ */
		/* ================== Drawing text on the screen ================== */
		/* ================================================================ */
		
		Text_draw(fps_string, &(SDL_Rect) {16, 16, fps_string->width, fps_string->height});
		
		Text_draw(normal, &(SDL_Rect) {window_width / 4 - normal->width / 2, window_height / 2 + normal->height / 2, normal->width, normal->height});
		Text_draw(normal_time_string, &(SDL_Rect) {window_width / 4 - normal_time_string->width / 2, window_height / 2 + normal_time_string->height / 2 + normal->height + 8, normal_time_string->width, normal_time_string->height});

		SDL_RenderSetViewport(ctx, &(SDL_Rect) {window_width / 2, 0, window_width / 2, window_height});

		Text_draw(fast, &(SDL_Rect) {window_width / 4 - fast->width / 2 , window_height / 2 + fast->height / 2, fast->width, fast->height});
		Text_draw(fast_time_string, &(SDL_Rect) {window_width / 4 - fast_time_string->width / 2, window_height / 2 + fast_time_string->height / 2 + normal->height + 8, fast_time_string->width, fast_time_string->height});

		sprintf(normal_time_string->content, "Seconds passed: %.1f", normal_time);
		Text_update(normal_time_string, normal_time_string->content);

		sprintf(fast_time_string->content, "Seconds passed: %.1f", fast_time);
		Text_update(fast_time_string, fast_time_string->content);
        
        sprintf(fps_string->content, "FPS: %d", get_fps());
        Text_update(fps_string, fps_string->content);

		SDL_RenderSetViewport(ctx, NULL);

		App_render();

		/* ================================ */
		/* ========== FRAME ENDS ========== */
		/* ================================ */

        Clock_update(normal_clock);
        Clock_update(fast_clock);

		normal_time += Clock_getDelta(normal_clock);
		fast_time += Clock_getDelta(fast_clock);
	}

	/* ================================================================ */
    /* ===================== Freeing cloks & text ===================== */
    /* ================================================================ */
    
    Text_destroy(&fps_string);
    
    Clock_destroy(&normal_clock);
    Clock_destroy(&fast_clock);

	Text_destroy(&fast_time_string);
	Text_destroy(&normal_time_string);
	Text_destroy(&normal);
	Text_destroy(&fast);

	TTF_CloseFont(font);

	App_stop();
	Stop();

	/* ======== */
	return EXIT_SUCCESS;
}
