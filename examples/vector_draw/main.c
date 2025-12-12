#include "../../include/Start.h"

/* ================================================================ */

SDL_Renderer* ctx;

int width;
int height;

void draw(Vector2* v) {
	SDL_RenderDrawLine(ctx, width / 2, height / 2, width / 2 + v->x, height / 2 + v->y);
}

void update(Vector2* v, float d) {
	*v = Vector2_rotate(v, d);
}

/* ================================================================ */

int main(int argc, char** argv) {

	SDL_Event event;

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
	SDL_GetWindowSize(get_window(), &width, &height);

	Vector2 v1 = {125, 0};
	Vector2 v2 = {-125, 0};

	Clock* timer = Clock_new();
	Clock_setTimer(timer, 1);

	/* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
    /* ================================================================ */

	while (App_isRunning()) {

		Clock_update(timer);

		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case SDL_QUIT:

					App_stop();
					break ;
			}
		}

		if (Clock_isReady(timer)) {

			update(&v1, 1.f);
			update(&v2, -1.f);

			Clock_reset(timer);
		}

		if (eqf(Vector2_eAngle(&v1, &v2), 90.0)) {
			Clock_stop(timer);
		}

		SDL_SetRenderDrawColor(ctx, 255, 255, 255, 255);
		SDL_RenderClear(ctx);

		/* ======== */

		SDL_SetRenderDrawColor(ctx, 0, 255, 0, 255);
		draw(&v1);

		SDL_SetRenderDrawColor(ctx, 255, 0, 0, 255);
		draw(&v2);

		/* ======== */

		App_render();
	}

	Clock_destroy(&timer);

	App_stop();
	Stop();

	/* ======== */
	return EXIT_SUCCESS;
}
