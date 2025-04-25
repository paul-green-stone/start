#include <SDL2/SDL.h>

#include "../include/Application.h"
#include "../include/Window.h"
#include "../include/Clock.h"
/* ================================================================ */

struct application {

    /* A structure that contains information about both the `SDL_Window` and its associated `SDL_Renderer` */
    Window* window;

    /* The main game loop controlling variable */
    int is_running;

    int desired_fps;
    int actual_fps;

    /* How much time a frame takes */
    float frame_period;
    /* How much time has passed since the last frame */
    float delta_time;
    
    /* Frame start time */
    Uint64 fst;
    Uint64 running_time;
};

static struct application app;

/* ================================ */

int App_init(const char* title) {

    /* ================================================ */
    /* ============== CREATING A WINDOW =============== */
    /* ================================================ */

    if ((app.window = Window_new(title, 640, 480, 0, SDL_RENDERER_ACCELERATED)) == NULL) {
        return -1;
    }

    /* ================================================ */

    app.is_running = 1;

    app.desired_fps = 60;
    app.frame_period = 1.0f / app.desired_fps;

    /* ======== */

    return 0;
}

/* ================================================================ */

void App_quit(void) {
    
    /* Destroying the window */
    Window_destroy(&app.window);
}

/* ================================================================ */

int App_isRunning(void) {
    return app.is_running;
}

/* ================================================================ */

void App_render(void) {

    /* A variable that controls how long the program pauses its execution */
    double delay_time;
    /* Frame end time */
    double end;

    static double sec_timer = 0;

    /* A variable that accumulates the number of frames within each second */
    static int fps_accumulator = 0;

    /* ======== */

    /* Mark the end of a frame */
    end = SDL_GetPerformanceCounter();
    /* and compute delta time (the amount of time between two frames in seconds )*/
    app.delta_time = (end - app.fst) / (float) SDL_GetPerformanceFrequency();

    /* Delay time in milliseconds */
    delay_time = (app.frame_period - app.delta_time) * 1000.0f;

    SDL_RenderPresent(Window_get_context(app.window));

    if ((sec_timer += app.delta_time) >= 1.0f) {

        app.actual_fps = fps_accumulator;
        fps_accumulator = 0;
        sec_timer = 0;
    }

    if (app.delta_time < app.frame_period) {

        SDL_Delay(delay_time);
        sec_timer += (app.frame_period - app.delta_time);
        app.delta_time += (app.frame_period - app.delta_time);
    }

    /* New frame starts */
    app.fst = SDL_GetPerformanceCounter();
    fps_accumulator++;
}

/* ================================================================ */

void App_setFPS(int fps) {

    app.desired_fps = (fps < 1) ? 1 : (fps > 60) ? 60 : fps;
    app.frame_period = 1.0f / app.desired_fps;
}

/* ================================================================ */

void App_stop(void) {
    app.is_running = !app.is_running;
}

/* ================================================================ */

SDL_Renderer* get_context(void) {
    return Window_get_context(app.window);
}

/* ================================================================ */

double get_delta(void) {
    return app.delta_time;
}

/* ================================================================ */

int get_fps(void) {
    return app.actual_fps;
}

/* ================================================================ */
