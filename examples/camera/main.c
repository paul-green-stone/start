#include "../../include/Start.h"

/* ================================================================ */

int main(int argc, char** argv) {

    SDL_Event event;
    SDL_Renderer* ctx;

    TTF_Font* font = NULL;

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

    /* Opening a font by standard library function */
    font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 24);

    /* ================================================================ */
    /* ============== Centering the player in the window ============== */
    /* ================================================================ */

    float speed = 48;

    int player_size = 16;
    Vector2 player_pos = {640 / 2 + player_size / 2, 480 / 2 - player_size / 2};
    SDL_Rect player = {player_pos.x, player_pos.y, player_size, player_size};
    
    char buffer[32];
    sprintf(buffer, "%.2f, %.2f", player_pos.x, player_pos.y);

    /* Coordinates displayed near the player */
    Text* player_coordinates = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, buffer);
    /* Well, this is a player's label :) */
    Text* p = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Player (You)");

    /* ================================================================ */
    /* ========== Creating `SDL_Rect`s representing buildings ========= */
    /* ================================================================ */

    SDL_Rect _b1 = {540, 100, 200, 200};
    Text* b1 = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Building 1");

    SDL_Rect _b2 = {300, -450, 150, 300};
    Text* b2 = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Building 2");

    /* ================================================================ */
    /* ============ Creating a humble citizen moving around =========== */
    /* ================================================================ */

    SDL_Rect _npc1 = {500, -75, 16, 16};
    Text* npc1 = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "Humble Citizen");
    Vector2 _npc_pos1 = {500.0, -75.0};
    float _npc1_speed = 16;

    /* ================================================================ */
    /* ===================== Ccreating a fast car ===================== */
    /* ================================================================ */

    SDL_Rect _car = {1000, -55, 64, 24};
    Text* car = Text_new(ctx, font, &(SDL_Color) {0, 0, 0, 255}, "A really fast car");
    float car_speed = 100;
    Vector2 car_pos = {1000.0, -55.0f};

    /* ================================================================ */
    /* ====================== Ccreating a camera ====================== */
    /* ================================================================ */

    Camera c;
    c.dmns = (SDL_Rect) {0, 0, 640, 480};
    /* Try to bind the camera to the car, citizen, or building to see the result */
    Camera_bind(&c, &player_pos);
    Camera_center(&c);

    /* Variables for storing transformed coordinates */
    SDL_Rect transformed;
    float fx, fy;

    /* ================================================================ */
    /* =============== A pretty standard main game loop =============== */
    /* ================================================================ */

    for (size_t i = 0; i < 2; i++) App_render();
    
    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:

                    App_stop();
                    break ;
            }
        }

        Input_update();

        /* ================================================================ */
        /* ========= Computing how far the entities have traveled ========= */
        /* ========================== S = VT ============================== */
        /* ================================================================ */
        {
            /* Citizen */
            float _ = _npc1_speed * get_delta();
            _npc_pos1.x += _;

            /* Car */
            _ = car_speed * get_delta();
            car_pos.x -= _;
        }

        /* ================================================================ */
        /* =================== Handling player movement =================== */
        /* ================================================================ */

        if (Input_isKey_pressed(SDL_SCANCODE_S)) {

            float _ = speed * get_delta();
            player_pos.y += _;

            player.y = player_pos.y;
        }

        if (Input_isKey_pressed(SDL_SCANCODE_W)) {

            float _ = speed * get_delta();
            player_pos.y -= _;

            player.y = player_pos.y;
        }

        if (Input_isKey_pressed(SDL_SCANCODE_D)) {

            float _ = speed * get_delta();
            player_pos.x += _;

            player.x = player_pos.x;
        }

        if (Input_isKey_pressed(SDL_SCANCODE_A)) {

            float _ = speed * get_delta();
            player_pos.x -= _;

            player.x = player_pos.x;
        }

        sprintf(buffer, "%.2f, %.2f", player_pos.x, player_pos.y);
        Text_update(player_coordinates, buffer);

        /* ================================================================ */

        /* Fill the screen with the given color */
        SDL_SetRenderDrawColor(ctx, 255, 255, 255, 255);
        SDL_RenderClear(ctx);

        /* Set the color of a player */
        SDL_SetRenderDrawColor(ctx, 255, 0, 0, 255);

        /* ================================================================ */
        /* ========= Adjusting coordinates relative to the camera ========= */
        /* ================================================================ */

        /* The Player */
        Camera_transform(&c, player_pos.x, player_pos.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.w = player_size;
        transformed.h = player_size;
        SDL_RenderFillRect(ctx, &transformed);

        /* Its textual coordinates representation */
        Camera_transform(&c, player_pos.x, player_pos.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.x += player.w + 4;
        transformed.y -= 4;

        transformed.w = player_coordinates->width;
        transformed.h = player_coordinates->height;

        Text_draw(player_coordinates, &transformed);

        /* And its label */
        transformed.y += transformed.h + 8;
        transformed.h = p->height;
        transformed.w = p->width;
        Text_draw(p, &transformed);
        
        /* ========================== Building 1 ========================== */

        Camera_transform(&c, _b1.x, _b1.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.w = 200,
        transformed.h = 200;

        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderFillRect(ctx, &transformed);

        Camera_transform(&c, _b1.x, _b1.y, &fx, &fy);
        transformed.w = b1->width;
        transformed.h = b1->height;
        transformed.x = fx + (_b1.w / 2) - (b1->width / 2);
        transformed.y = fy + (_b1.h / 2) - (b1->height / 2);
        Text_draw(b1, &transformed);

        /* ========================== Building 2 ========================== */

        Camera_transform(&c, _b2.x, _b2.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.h = _b2.h;
        transformed.w = _b2.w;

        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderFillRect(ctx, &transformed);

        Camera_transform(&c, _b2.x, _b2.y, &fx, &fy);
        transformed.w = b2->width;
        transformed.h = b2->height;
        transformed.x = fx + (_b2.w / 2) - (b2->width / 2);
        transformed.y = fy + (_b2.h / 2) - (b2->height / 2);
        Text_draw(b2, &transformed);

        /* ========================= The Citizen ========================== */

        Camera_transform(&c, _npc_pos1.x, _npc1.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.w = transformed.h = _npc1.w;

        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderFillRect(ctx, &transformed);

        transformed.w = npc1->width;
        transformed.h = npc1->height;
        transformed.x = transformed.x + _npc1.w;
        transformed.y = transformed.y - npc1->height;
        Text_draw(npc1, &transformed);

        /* =========================== The Car ============================ */

        Camera_transform(&c, car_pos.x, car_pos.y, &fx, &fy);
        transformed.x = fx;
        transformed.y = fy;
        transformed.w = _car.w;
        transformed.h = _car.h;

        SDL_SetRenderDrawColor(ctx, 255, 0, 0, 255);
        SDL_RenderFillRect(ctx, &transformed);

        transformed.x += _car.w;
        transformed.y += car->height;
        transformed.w = car->width;
        transformed.h = car->height;

        Text_draw(car, &transformed);
        
        /* Render the current scene to the display */
        App_render();

        Camera_center(&c);
    }

    TTF_CloseFont(font);
    Text_destroy(&player_coordinates);
    Text_destroy(&p);
    Text_destroy(&b1);
    Text_destroy(&npc1);
    Text_destroy(&car);

    App_quit();
    Stop();

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
