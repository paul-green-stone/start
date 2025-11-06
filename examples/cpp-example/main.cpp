#include "../../include/Start.h"

#define set_color(ctx, color_in_hex) \
    SDL_SetRenderDrawColor((ctx), (static_cast<int>(color_in_hex) >> 16) & 0xFF, (static_cast<int>(color_in_hex) >> 8) & 0xFF, static_cast<int>(color_in_hex) & 0xFF, 0xFF);

/* ================================================================ */

int main(int argc, char** argv) {

    SDL_Renderer* ctx = NULL;
    SDL_Event event;

    TTF_Font* font = NULL;

    Text* text = NULL;
    SDL_Rect text_pos;
    char fps_buf[32];

    enum class Color {

        red = 0xFF0000,
        green = 0x00FF00,
        blue = 0x0000FF,
    };

    /* ======== */
    
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
    
    /* ================================ */

    ctx = get_context();

    font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);

    SDL_Color text_color = {255, 255, 255, 255};
    text = Text_new(ctx, font, &text_color, "FPS: 60");
    text_pos = (SDL_Rect) {32, 32, text->width, text->height};

    App_setFPS(45);

    /* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
    /* ================================================================ */

    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

				case SDL_QUIT:

					App_stop();
                    /* ========= */
					break ;
			}
        }

        /* ================ */

        set_color(ctx, Color::red);
		SDL_RenderClear(ctx);

        Text_draw(text, &text_pos);

        sprintf(fps_buf, "FPS: %d", get_fps());
        Text_update(text, fps_buf);

        App_render();
    }

    /* ================================ */

    /* Deinitializes the application and its core systems */
    App_quit();
    Stop();

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
