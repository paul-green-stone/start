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

    /* ================================================================ */
    /* ======= Let's assume a `Texture_new` call is successful ======== */
    /* ==================== It is not safe, though ==================== */
    /* ================================================================ */

    /* Opening a font by standard library function */
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 22);;
    
    Particle* array_of_particles[20];
    
    for (size_t i = 0; i < 20; i++) {
        array_of_particles[i] = Particle_create(240, 240, rand_float(10, 25), rand_float(1, 5), &(SDL_Color) {rand_int(1, 255), rand_int(1, 255), rand_int(1, 255), 255});
    }
    
    /* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
    /* ================================================================ */
    
    for (size_t i = 0; i < 4; i++) { App_render(); }

    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:

                    App_stop();
                    break ;
            }
        }

        Input_update();
        
        for (size_t i = 0; i < 20; i++) {
            Particle_update(array_of_particles[i]);
        }

        /* Fill the screen with the given color */
        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderClear(ctx);
        
        for (size_t i = 0; i < 20; i++) {
            Particle_draw(array_of_particles[i]);
        }
        
        /* Render the current scene to the display */
        App_render();
    }
    
    for (size_t i = 0; i < 20; i++) {
            free(array_of_particles[i]);
    }

    TTF_CloseFont(font);

    /* Deinitializes the application and its core systems */
    App_quit();
    Stop();

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
