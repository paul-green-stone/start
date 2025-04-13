#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Window.h"
#include "../../include/Text.h"

/* ================================================================ */

static TTF_Font* font;
static Window* w;
static SDL_Renderer* r;

/* ================================ */

int main(int argc, char** argv) {

    /* SDL Library Initialization */
	SDL_Init(SDL_INIT_TIMER);
    /* TTF Library Initialization */
	TTF_Init();

    /* Creating a new window */
	w = Window_new("Start", 680, 400, 0, SDL_RENDERER_ACCELERATED);
    /* and getting its rendering context */
	r = Window_get_context(w);

    /* Opening a TTF font */
	font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 32);

	SDL_Event e;

	int quit = 0;
	
	/* Desired time for a frame */
	float frame_period = 1.0f / 60.f;

	Uint64 start;
	Uint64 end;
	double delta_time;

	int frames = 0;

	double counter = 0;

	Text* text = Text_new(r, font, &(SDL_Color) {0, 0, 0, 255}, "FPS: 60");
	char buffer[32];
	SDL_Rect dst = {16, 16, text->width, text->height};

	/* ================================================================ */
	/* =========================== GAME LOOP ========================== */
	/* ================================================================ */

	while (!quit) {
		
		/* ================================ */
		/* ========= FRAME STARTS ========= */
		/* ================================ */

		frames++;
		start = SDL_GetPerformanceCounter();

		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

		while (SDL_PollEvent(&e)) {

			switch (e.type) {

				case SDL_QUIT:
					quit = !quit;
					break ;
			}
		}
		
		Text_drawM(text, NULL, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
		Text_draw(text, &(SDL_Rect) {dst.x, dst.y + text->height+ 16, text->width, text->height});
		SDL_RenderPresent(r);

		/* ================================ */
		/* ========== FRAME ENDS ========== */
		/* ================================ */

		end = SDL_GetPerformanceCounter();
		delta_time = (end - start) / (float) SDL_GetPerformanceFrequency();

		/* Delay time in milliseconds */
		double delay_time = (frame_period - delta_time) * 1000.0f;

		if ((counter += delta_time) >= 1.0) {
			sprintf(buffer, "FPS: %d", frames);
			text = Text_update(text, buffer);
			frames = 0;
			counter = 0;
		}

		if (delta_time < frame_period) { SDL_Delay(delay_time); counter += (frame_period - delta_time); }
	}	
	
	Text_destroy(&text);
	Window_destroy(&w);

	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();

	return 0;
}

/* ================================================================ */
