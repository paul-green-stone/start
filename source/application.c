#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <libconfig.h>

#include "../include/Start.h"
#include "../include/Application.h"
#include "../include/Window.h"
#include "../include/Clock.h"
#include "../include/File/conf.h"

/* Default configuration file */
#define DEFAULT_CONFIGURATION_FILE "application.conf"

#define combine(buffer) \
    (buffer)[0] = '\0'; \
    strcat((buffer), DEFAULT_CONFIGURATION_DIRECTORY); \
    strcat((buffer), "/"); \
    strcat((buffer), DEFAULT_CONFIGURATION_FILE); \
    (buffer)[strlen((buffer))] = '\0'; \

/* ================================================================ */
/* ========================= DEFINITIONS ========================== */
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

/* ================================================================ */

struct default_app {

    Uint64 wflags;
    Uint64 rflags;

    char* title;

    int width;
    int height;
};

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

static struct lookup_table_entry SDL_CreateWindow__flags[] = {
    {"SDL_WINDOW_FULLSCREEN", SDL_WINDOW_FULLSCREEN},
    {"SDL_WINDOW_OPENGL", SDL_WINDOW_OPENGL},
    {"SDL_WINDOW_SHOWN", SDL_WINDOW_SHOWN},
    {"SDL_WINDOW_HIDDEN", SDL_WINDOW_HIDDEN},
    {"SDL_WINDOW_BORDERLESS", SDL_WINDOW_BORDERLESS},
    {"SDL_WINDOW_RESIZABLE", SDL_WINDOW_RESIZABLE},
    {"SDL_WINDOW_MINIMIZED", SDL_WINDOW_MAXIMIZED},
    {"SDL_WINDOW_MOUSE_GRABBED", SDL_WINDOW_MOUSE_GRABBED},
    {"SDL_WINDOW_INPUT_FOCUS", SDL_WINDOW_INPUT_FOCUS},
    {"SDL_WINDOW_MOUSE_FOCUS", SDL_WINDOW_MOUSE_FOCUS},
    {"SDL_WINDOW_FULLSCREEN_DESKTOP", ( SDL_WINDOW_FULLSCREEN | 0x00001000 )},
    {"SDL_WINDOW_FOREIGN", SDL_WINDOW_FOREIGN},
    {"SDL_WINDOW_ALLOW_HIGHDPI", SDL_WINDOW_ALLOW_HIGHDPI},
    {"SDL_WINDOW_MOUSE_CAPTURE", SDL_WINDOW_MOUSE_CAPTURE},
    {"SDL_WINDOW_ALWAYS_ON_TOP", SDL_WINDOW_ALWAYS_ON_TOP},
    {"SDL_WINDOW_SKIP_TASKBAR", SDL_WINDOW_SKIP_TASKBAR},
    {"SDL_WINDOW_UTILITY", SDL_WINDOW_UTILITY},
    {"SDL_WINDOW_TOOLTIP", SDL_WINDOW_TOOLTIP},
    {"SDL_WINDOW_POPUP_MENU", SDL_WINDOW_POPUP_MENU},
    {"SDL_WINDOW_KEYBOARD_GRABBED", SDL_WINDOW_KEYBOARD_GRABBED},
    {"SDL_WINDOW_VULKAN", SDL_WINDOW_VULKAN},
    {"SDL_WINDOW_METAL", SDL_WINDOW_METAL},
    {"SDL_WINDOW_INPUT_GRABBED", SDL_WINDOW_MOUSE_GRABBED}
};

/* ======== */

static struct lookup_table_entry SDL_CreateRenderer__flags[] = {
    {"SDL_RENDERER_SOFTWARE", SDL_RENDERER_SOFTWARE},
    {"SDL_RENDERER_ACCELERATED", SDL_RENDERER_ACCELERATED},
    {"SDL_RENDERER_PRESENTVSYNC", SDL_RENDERER_PRESENTVSYNC},
    {"SDL_RENDERER_TARGETTEXTURE", SDL_RENDERER_TARGETTEXTURE}
};

/* ======== */

static struct application app;

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * Reads a configuration file containing application settings and SDL flags,
 * then populates a default_app structure with the parsed values.
 * 
 * @param _app output parameter. Pointer to a structure that will store parsed configuration values
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
static int _read_default_configuration_file(struct default_app* _app) {

    config_t config;
    config_setting_t* array;

    int length, i;
    int temp;
    int flag;

    char filepath[64];

    /* ======== */

    combine(filepath);

    config_init(&config);

    /* ================================ */
    /* = Parsing a file that contains = */
    /* == initial information about === */
    /* ======= the application ======== */
    /* ================================ */

    if (Conf_parse_file(&config, filepath) != 0) {

        config_destroy(&config);

        /* ======== */

        return -2;
    }

    /* ================================ */

    Conf_extract(&config, "application.width", INT, &_app->width);
    Conf_extract(&config, "application.height", INT, &_app->height);

    Conf_extract(&config, "application.title", STRING, &_app->title);

    /* ================================ */

    /* Extracting an array of `SDL_Window` flags */
    Conf_lookup(&config, "application.Window", &array);
    /* and getting the number of elements it contains */
    length = config_setting_length(array);

    for (i = 0; i < length; i++) {

        /* Map a string to its integral counterpart */
        temp = lookup_table_find(SDL_CreateWindow__flags, sizeof(SDL_CreateWindow__flags) / sizeof(SDL_CreateWindow__flags[0]), config_setting_get_string_elem(array, i), &flag);

        /* Combining flags */
        _app->wflags |= (temp == 0) ? flag : 0;
    }

    /* ================================ */

    /* Extracting an array of `SDL_Renderer` flags */
    Conf_lookup(&config, "application.Renderer", &array);
    /* and getting the number of elements it contains */
    length = config_setting_length(array);

    for (i = 0; i < length; i++) {

        /* Map a string to its integral counterpart */
        temp = lookup_table_find(SDL_CreateRenderer__flags, sizeof(SDL_CreateRenderer__flags) / sizeof(SDL_CreateRenderer__flags[0]), config_setting_get_string_elem(array, i), &flag);

        /* Combining flags */
        _app->rflags |= (temp == 0) ? flag : 0;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

/**
 * Creates a default configuration file with predefined window and renderer settings using the libconfig library.
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
static int _write_default_configuration_file_(void) {

    config_t config;
    config_setting_t* setting;
    config_setting_t* array;
    config_setting_t* elm;

    size_t i;

    char filepath[64];

    /* Structure holding default application properties */
    struct {
        char* wflags[1];
        char* rflags[1];
        
        char* title;
        int width;
        int height;
    } default_app;

    /* ======== */

    combine(filepath);

    default_app.wflags[0] = "SDL_WINDOW_SHOWN";
    default_app.rflags[0] = "SDL_RENDERER_ACCELERATED";
    default_app.width = 640;
    default_app.height = 480;
    default_app.title = "Start";

    config_init(&config);

    /* Create a new setting for the application configuration */
    setting = config_setting_add(config_root_setting(&config), "application", CONFIG_TYPE_GROUP);

    /* ================================ */
    /* ============ TITLE ============= */
    /* ================================ */

    elm = config_setting_add(setting, "title", CONFIG_TYPE_STRING);
    config_setting_set_string(elm, default_app.title);

    /* ================================ */
    /* ========= WIDTH&HEIGHT ========= */
    /* ================================ */

    elm = config_setting_add(setting, "width", CONFIG_TYPE_INT);
    config_setting_set_int(elm, default_app.width);

    elm = config_setting_add(setting, "height", CONFIG_TYPE_INT);
    config_setting_set_int(elm, default_app.height);

    /* ================================ */
    /* ======== WFLAGS&RFLAGS ========= */
    /* ================================ */

    array = config_setting_add(setting, "Window", CONFIG_TYPE_ARRAY);

    /* Set window flags */
    for (i = 0; i < sizeof(default_app.wflags) / sizeof(default_app.wflags[0]); i++) {

        elm = config_setting_add(array, NULL, CONFIG_TYPE_STRING);
        config_setting_set_string(elm, default_app.wflags[i]);
    }

    array = config_setting_add(setting, "Renderer", CONFIG_TYPE_ARRAY);

    /* Set renderer flags */
    for (i = 0; i < sizeof(default_app.rflags) / sizeof(default_app.rflags[0]); i++) {

        elm = config_setting_add(array, NULL, CONFIG_TYPE_STRING);
        config_setting_set_string(elm, default_app.rflags[i]);
    }

    /* ================================ */

    /* Write the configuration to a file */
    if (!config_write_file(&config, filepath)) {
        return -2;
    }

    config_destroy(&config);
    
    /* ======== */

    return 0;
}

/* ================================================================ */

int App_init(void) {

    struct default_app _app;
    char filepath[64];

    /* ======== */

    combine(filepath);

    /* Clearing the struct */
    memset(&_app, 0, sizeof(struct default_app));

    if (!file_exists(filepath)) {
        _write_default_configuration_file_();
    }

    _read_default_configuration_file(&_app);

    /* ================================================ */
    /* ============== CREATING A WINDOW =============== */
    /* ================================================ */

    if ((app.window = Window_new(_app.title, _app.width, _app.height, _app.wflags, _app.rflags)) == NULL) {
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
