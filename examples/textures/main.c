#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Window.h"
#include "../../include/Texture.h"

/* ================================================================ */

static TTF_Font* font;
static Window* w;
static SDL_Renderer* r;

SDL_Texture* foo(SDL_Texture* _t, const char* str, SDL_Color* color) {

	if (_t) SDL_DestroyTexture(_t);

	SDL_Surface* s = TTF_RenderText_Solid(font, str, *color);
	SDL_Texture* t = SDL_CreateTextureFromSurface(r, s);
	SDL_FreeSurface(s);

	return t;
}

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
	int width = 0, height = 0;
	
	/* Desired time for a frame */
	float frame_period = 1.0f / 60.f;

	Uint64 start;
	Uint64 end;
	double delta_time;

	int frames = 0;

	double counter = 0;

	char fps_string[32] = "FPS: 60";
	SDL_Texture* t = foo(NULL, fps_string, &(SDL_Color) {0, 0, 0, 255});

	Texture* bg = Texture_new(r, "../resources/images/asset.png");

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
		
		Texture_drawM(bg, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopy(r, t, NULL, &(SDL_Rect) {32, 32, width, height});
		SDL_RenderPresent(r);

		/* ================================ */
		/* ========== FRAME ENDS ========== */
		/* ================================ */

		end = SDL_GetPerformanceCounter();
		delta_time = (end - start) / (float) SDL_GetPerformanceFrequency();

		/* Delay time in milliseconds */
		double delay_time = (frame_period - delta_time) * 1000.0f;

		if ((counter += delta_time) >= 1.0) {
			sprintf(fps_string, "FPS: %d", frames);
			SDL_QueryTexture(t, NULL, NULL, &width, &height);
			t = foo(t, fps_string, &(SDL_Color) {0, 0, 0, 255});
			frames = 0;
			counter = 0;
		}

		if (delta_time < frame_period) { SDL_Delay(delay_time); counter += (frame_period - delta_time); }
	}	
	
	Texture_destroy(&bg);
	SDL_DestroyTexture(t);
	Window_destroy(&w);

	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();

	return 0;
}

/* ================================================================ */
