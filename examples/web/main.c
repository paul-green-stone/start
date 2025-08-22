#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "../../include/Application.h"
#include "../../include/Clock.h"
#include "../../include/Text.h"
#include "../../include/Window.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef struct AppCtx {
    SDL_Event event;
    SDL_Renderer *r;

    TTF_Font *font;
    Text *text;
    SDL_Rect text_pos;
    char fps_buf[32];
} AppCtx;

/* ================================================================ */

/**
 * Main game loop code
 */
void game_loop(void *app_ctx) {
    AppCtx *ctx = (AppCtx *)app_ctx;

    while (SDL_PollEvent(&(ctx->event))) {

        switch (ctx->event.type) {

        case SDL_QUIT:
            App_stop();
            break;
        }
    }

    /* ================ */

    SDL_SetRenderDrawColor(ctx->r, 255, 0, 0, 255);
    SDL_RenderClear(ctx->r);

    Text_draw(ctx->text, &ctx->text_pos);

    sprintf(ctx->fps_buf, "FPS: %d", get_fps());
    Text_update(ctx->text, ctx->fps_buf);

    App_render();

    printf("Delta time: %f\n", get_delta());
}

int main(int argc, char **argv) {
    /* ================================ */

    AppCtx ctx;

    ApplicationConfig app_config = {.title = "Web test",
                                    .width = 640,
                                    .height = 480,
                                    .window_flags = SDL_WINDOW_SHOWN,
                                    .renderer_flags = SDL_RENDERER_ACCELERATED};

    Start();
    App_init(&app_config);

    ctx.r = get_context();

    ctx.font = TTF_OpenFont("res/font.ttf", 24);
    ctx.text = Text_new(ctx.r, ctx.font, &(SDL_Color){0, 0, 0, 255}, "FPS: 60");
    ctx.text_pos = (SDL_Rect){32, 32, ctx.text->width, ctx.text->height};

    App_setFPS(45);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, &ctx, 0, true);
#else
    while (App_isRunning())
        game_loop(&ctx);
#endif

    /* ================================ */

    App_quit();
    Stop();

    /* ======== */
    return 0;
}

/* ================================================================ */
