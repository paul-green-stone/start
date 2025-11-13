#include "../../include/Start.h"
#include <time.h>

#define SIZE 20

/* ================================================================ */

int main(int argc, char** argv) {

    srand(time(NULL));

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
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 18);

    int num_em = 0;
    int free_slot = 0;
    //ParticalEmmiter* emmiters[SIZE] = {NULL};

    int width, height;
    SDL_GetWindowSize(get_window(), &width, &height);

    //ParticalEmmiter* super = ParticalEmmiter_create(0, width / 2, height / 2, rand_float(10, 30), rand_int(2, 5), NULL, 50);

    // Text* text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Particels: ");
    // char buffer[64];

    void* particles[SIZE];
    int alive = SIZE;

    for (size_t i = 0; i < SIZE; i++) {

        particles[i] = Particle_create(BaseParticle, (float) width / 2, (float) height / 2, rand_float(-1.0f, 1.0f), rand_float(-1.0f, 1.0f), rand_float(15, 25), rand_int(2, 5), rand_int(1, 4294967295), 255);
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

        for (size_t i = 0; i < alive; i++) {

            if (particles[i] == NULL) { continue ; }

            Particle_move(particles[i]);
            Particle_update(particles[i]);
        }


        /* Fill the screen with the given color */
        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderClear(ctx);

       

        for (size_t i = 0; i < alive; i++) {
            Particle_draw(particles[i]);
        }
        
        /* Render the current scene to the display */
        App_render();
        
        for (size_t i = 0; i < alive; i++) {

            if (!Particle_isAlive(particles[i])) {

                Particle_destroy(particles[i]);
                particles[i] = particles[alive -= 1];
                i--;
            }
        }
    }
    
    // for (size_t i = 0; i < SIZE; i++) {
    //     ParticalEmmiter_destroy(&emmiters[i]);
    // }

    // ParticalEmmiter_destroy(&super);
    //Text_destroy(&text);

    TTF_CloseFont(font);

    for (size_t i = 0; i < alive; i++) {
        Particle_destroy(particles[i]);
    }

    /* Deinitializes the application and its core systems */
    App_quit();
    Stop();

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
