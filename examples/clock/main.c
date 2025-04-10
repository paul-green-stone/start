#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Window.h"
#include "../../include/Clock.h"

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

	/* Window width */
	int W = 680;
	/* Window height */
	int H = 400;

	/* Creating a new window */
	w = Window_new("Start Clock Example", W, H, 0, SDL_RENDERER_ACCELERATED);
	/* and getting its rendering context */
	r = Window_get_context(w);

	/* Opening a TTF font */
	font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);

	SDL_Event e;
	int quit = 0;

	int width = 0, height = 0;

	SDL_Texture* t1 = foo(NULL, "Normal Clock (1x)", &(SDL_Color) {0, 0, 0, 255});
	SDL_Texture* t2 = foo(NULL, "Fast Clock (2x)", &(SDL_Color) {0, 0, 0, 255});

	int t1_w, t1_h;
	char t1_str[32];
	int t1_str_w, t1_str_h;
	double t1_d = 0;
	SDL_Texture* t1_str_t = NULL;

	int t2_w, t2_h;
	char t2_str[32];
	int t2_str_w, t2_str_h;
	double t2_d = 0;
	SDL_Texture* t2_str_t = NULL;

	SDL_QueryTexture(t1, NULL, NULL, &t1_w, &t1_h);
	SDL_QueryTexture(t2, NULL, NULL, &t2_w, &t2_h);
	
	/*  Desired time for a frame */
	float frame_period = 1.0f / 60.f;

	Uint64 start;
	Uint64 end;
	double delta_time;

	int frames = 0;
	double counter = 0;

	char fps_string[32] = "FPS: ";
	SDL_Texture* t = foo(NULL, fps_string, &(SDL_Color) {0, 0, 0, 255});

    Clock* clock = Clock_new();
    Clock_start(clock);

    Clock* fast_clock = Clock_new();
    Clock_setSpeed(fast_clock, 2.0f);
    Clock_start(fast_clock);

	/* ================================================================ */
	/* =========================== GAME LOOP ========================== */
	/* ================================================================ */

	while (!quit) {
		
		/* ================================ */
		/* ========= FRAME STARTS ========= */
		/* ================================ */

		frames++;
		/* `start` has milliseconds */
		// start = SDL_GetTicks64();

		start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&e)) {

			switch (e.type) {

				case SDL_QUIT:
					quit = !quit;
					break ;
			}
		}

		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);

		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderDrawLine(r, W / 2, 0, W / 2, H);
		
		SDL_RenderCopy(r, t, NULL, &(SDL_Rect) {16, 16, width, height});

		SDL_RenderCopy(r, t1, NULL, &(SDL_Rect) {(W / 2) / 2 - t1_w / 2, H / 2 - t1_h / 2, t1_w, t1_h});

		t1_d += Clock_getDelta(clock);
		sprintf(t1_str, "Seconds passed: %.2f", t1_d);
		t1_str_t = foo(t1_str_t, t1_str, &(SDL_Color) {0, 0, 0, 255});
		SDL_QueryTexture(t1_str_t, NULL, NULL, &t1_str_w, &t1_str_h);
		SDL_RenderCopy(r, t1_str_t, NULL, &(SDL_Rect) {(W / 2) / 2 - t1_str_w / 2, H / 2 + t1_str_h, t1_str_w, t1_str_h});

		SDL_RenderSetViewport(r, &(SDL_Rect) {W / 2, 0, W / 2, H});

		SDL_RenderCopy(r, t2, NULL, &(SDL_Rect) {(W / 2) / 2 - t2_w / 2, H / 2 - t2_h / 2, t2_w, t2_h});

		t2_d += Clock_getDelta(fast_clock);
		sprintf(t2_str, "Seconds passed: %.2f", t2_d);
		t2_str_t = foo(t2_str_t, t2_str, &(SDL_Color) {0, 0, 0, 255});
		SDL_QueryTexture(t2_str_t, NULL, NULL, &t2_str_w, &t2_str_h);
		SDL_RenderCopy(r, t2_str_t, NULL, &(SDL_Rect) {(W / 2) / 2 - t2_str_w / 2, H / 2 + t2_str_h, t2_str_w, t2_str_h});

		SDL_RenderSetViewport(r, NULL);

		SDL_RenderPresent(r);

		/* ================================ */
		/* ========== FRAME ENDS ========== */
		/* ================================ */

		// end = SDL_GetTicks64();
		end = SDL_GetPerformanceCounter();
		// delta_time = (end - start) / 1000.f;
		/* `delta_time` now in seconds */
		delta_time = (end - start) / (float) SDL_GetPerformanceFrequency();

        /* Make delta time available for game systems */

		/* Delay time in milliseconds */
		double delay_time = (frame_period - delta_time) * 1000.0f;

		if ((counter += delta_time) >= 1.0) {
			sprintf(fps_string, "FPS: %d", frames);
			SDL_QueryTexture(t, NULL, NULL, &width, &height);
			t = foo(t, fps_string, &(SDL_Color) {0, 0, 0, 255});
			frames = 0;
			counter = 0;
		}

		if (delta_time < frame_period) {
            SDL_Delay(delay_time);
            counter += (frame_period - delta_time);
        }

        Clock_update(clock);
        Clock_update(fast_clock);
	}
    
    Clock_destroy(&clock);
    Clock_destroy(&fast_clock);

	SDL_DestroyTexture(t);
	SDL_DestroyTexture(t1);
	SDL_DestroyTexture(t2);
	SDL_DestroyTexture(t2_str_t);
	SDL_DestroyTexture(t1_str_t);

	Window_destroy(&w);

	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();

	return 0;
}