#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <libconfig.h>

#include "../include/Application.h"
#include "../include/Window.h"
#include "../include/Clock.h"
#include "../include/File/conf.h"

/* Default configuration file path */
#define DEFAULT_CONFIG_FILE "./configs/system.conf"

#define DEFAUL_CONFIG_DIR "./configs"

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * 
 */
static int _create_default_configuration_file_(void) {

    config_t config;
    config_setting_t* setting;
    config_setting_t* array;
    config_setting_t* elm;

    size_t i;

    /* ======== */

    /* Structure holding default application properties */
    struct {
        char* wflags[1];
        char* rflags[1];
        
        char* title;
        int width;
        int height;
    } default_window = {{"SDL_WINDOW_SHOWN"}, {"SDL_RENDERER_ACCELERATED"}, "Start", 640, 480};

    config_init(&config);

    /* Create a new setting for the application configuration */
    setting = config_setting_add(config_root_setting(&config), "application", CONFIG_TYPE_GROUP);

    /* ================================ */
    /* ============ TITLE ============= */
    /* ================================ */

    elm = config_setting_add(setting, "title", CONFIG_TYPE_STRING);
    config_setting_set_string(elm, default_window.title);

    /* ================================ */
    /* ========= WIDTH&HEIGHT ========= */
    /* ================================ */

    elm = config_setting_add(setting, "width", CONFIG_TYPE_INT);
    config_setting_set_int(elm, default_window.width);

    elm = config_setting_add(setting, "height", CONFIG_TYPE_INT);
    config_setting_set_int(elm, default_window.height);

    /* ================================ */
    /* ======== WFLAGS&RFLAGS ========= */
    /* ================================ */

    array = config_setting_add(setting, "Window", CONFIG_TYPE_ARRAY);

    /* Set window flags */
    for (i = 0; i < sizeof(default_window.wflags) / sizeof(default_window.wflags[0]); i++) {

        elm = config_setting_add(array, NULL, CONFIG_TYPE_STRING);
        config_setting_set_string(elm, default_window.wflags[i]);
    }

    array = config_setting_add(setting, "Renderer", CONFIG_TYPE_ARRAY);

    /* Set renderer flags */
    for (i = 0; i < sizeof(default_window.rflags) / sizeof(default_window.rflags[0]); i++) {

        elm = config_setting_add(array, NULL, CONFIG_TYPE_STRING);
        config_setting_set_string(elm, default_window.rflags[i]);
    }

    /* ================================ */

    /* Write the configuration to a file */
    if (!config_write_file(&config, DEFAULT_CONFIG_FILE)) {
        return -2;
    }

    config_destroy(&config);
    
    /* ======== */

    return 0;
}

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

    /* Application's current state */
    void* state;
};

static struct application app;

/* ================================ */

int App_init(const char* title, int width, int height) {

    /* ================================================ */
    /* ============== CREATING A WINDOW =============== */
    /* ================================================ */

    if ((app.window = Window_new(title, width, height, 0, SDL_RENDERER_ACCELERATED)) == NULL) {
        return -1;
    }

    /* ================================================ */
    /* ============= CREATING A DIRECTORY ============= */
    /* ================================================ */
    
    if (!directory_exist(DEFAUL_CONFIG_DIR)) {
        directory_new(DEFAUL_CONFIG_DIR);
    }

    _create_default_configuration_file_();

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

SDL_Window* get_window(void) {
    return Window_get_window(app.window);
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

int take_screenshot(const char* filename) {

    SDL_Surface* surface;
    int width;
    int height;
    struct stat st;
    char filepath[64];

    /* ================================================ */
    /* === Creating a directory if it doesn't exist === */
    /* ================================================ */

    memset(&st, 0, sizeof(st));

    if (stat("screenshots", &st) == -1) {
        mkdir("screenshots", 0755);
    }

    strcat(filepath, "screenshots/");

    /* ================================================ */

    /* Do not use `NULL` */
    if (filename == NULL) {
        return -1;
    }

    /* Getting window dimensions */
    SDL_GetWindowSize(Window_get_window(app.window), &width, &height);

    if ((surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32)) == NULL) {
        return -1;
    }

    if (SDL_RenderReadPixels(get_context(), NULL, SDL_PIXELFORMAT_RGBA32, surface->pixels, surface->pitch) != 0) {

        SDL_FreeSurface(surface);

        /* ======== */

        return -2;
    }

    /* ================================================ */
    /* ============ Updating the filename ============= */
    /* ================================================ */

    strcat(filepath, filename);
    filepath[strlen(filepath)] = '\0';

    /* ================================================ */

    if (IMG_SavePNG(surface, filepath) != 0) {

        SDL_FreeSurface(surface);

        /* ======== */

        return -3;  
    }

    SDL_FreeSurface(surface);

    /* ======== */

    return 0;
}

/* ================================================================ */

void set_state(const void* state) {
    app.state = (void*) state;
}

/* ================================================================ */

void* get_state(void) {
    return app.state;
}

/* ================================================================ */
