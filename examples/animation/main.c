#include "../../include/Start.h"

int click(const void* _self, va_list* args) {

    const char* string = va_arg(*args, const char*);

    printf("%s\n", string);
}

/* ================================================================ */

int main(int argc, char** argv) {

    SDL_Event event;
    SDL_Renderer* ctx;

    char buffer[64];

    Start();
    App_init(NULL);

    ctx = get_context();

    Texture* attack_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Attack.png");
    Texture* death_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Death.png");
    Texture* fall_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Fall.png");
    Texture* get_hit_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/GetHit.png");
    Texture* idle_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Idle.png");
    Texture* jump_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Jump.png");
    Texture* run_t = Texture_new(ctx, "../resources/Huntress2/Sprites/Character/Run.png");

    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 22);

    Animation* attack_animation = Animation_new(attack_t, 0, 0, 6, 100, 100, X);
    Animation_setSpeed(attack_animation, 1.0f / 6);
    Text* attack_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Attack");

    Animation* death_animation = Animation_new(death_t, 0, 0, 10, 100, 100, X);
    Animation_setSpeed(death_animation, 1.0f / 10);
    Text* death_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Death");

    Animation* fall_animation = Animation_new(fall_t, 0, 0, 2, 100, 100, X);
    Animation_setSpeed(fall_animation, 1.0f / 4);
    Text* fall_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Falling");

    Animation* get_hit_animation = Animation_new(get_hit_t, 0, 0, 3, 100, 100, X);
    Animation_setSpeed(get_hit_animation, 1.0f / 3);
    Text* get_hit_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Get Hit");

    Animation* idle_animation = Animation_new(idle_t, 0, 0, 10, 100, 100, X);
    Animation_setSpeed(idle_animation, 1.0f / 10);
    Text* idle_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Idle");

    Animation* run_animation = Animation_new(run_t, 0, 0, 8, 100, 100, X);
    Animation_setSpeed(run_animation, 1.0f / 8);
    Text* run_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Run");

    Animation* jump_animation = Animation_new(jump_t, 0, 0, 2, 100, 100, X);
    Animation_setSpeed(jump_animation, 1.0f / 4);
    Text* jump_text = Text_new(ctx, font, &(SDL_Color) {255, 255, 255, 255}, "Jump");
    
    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:

                    App_stop();
                    break ;
            }
        }

        Input_update();

        Animation_update(attack_animation, get_delta());
        Animation_update(death_animation, get_delta());
        Animation_update(fall_animation, get_delta());
        Animation_update(get_hit_animation, get_delta());
        Animation_update(idle_animation, get_delta());
        Animation_update(jump_animation, get_delta());
        Animation_update(run_animation, get_delta());

        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderClear(ctx);

        Texture_draw(attack_animation->texture, &attack_animation->frame, &(SDL_Rect) {0, 0, 100, 100});
        Text_draw(attack_text, &(SDL_Rect) {100, 50 - attack_text->height / 2, attack_text->width, attack_text->height});

        Texture_draw(death_animation->texture, &death_animation->frame, &(SDL_Rect) {0, 100, 100, 100});
        Text_draw(death_text, &(SDL_Rect) {100, 150 - death_text->height / 2, death_text->width, death_text->height});

        Texture_draw(fall_animation->texture, &fall_animation->frame, &(SDL_Rect) {0, 200, 100, 100});
        Text_draw(fall_text, &(SDL_Rect) {100, 250 - fall_text->height / 2, fall_text->width, fall_text->height});

        Texture_draw(get_hit_animation->texture, &get_hit_animation->frame, &(SDL_Rect) {0, 300, 100, 100});
        Text_draw(get_hit_text, &(SDL_Rect) {100, 350 - get_hit_text->height / 2, get_hit_text->width, get_hit_text->height});

        Texture_draw(idle_animation->texture, &idle_animation->frame, &(SDL_Rect) {0, 400, 100, 100});
        Text_draw(idle_text, &(SDL_Rect) {100, 450 - idle_text->height / 2, idle_text->width, idle_text->height});

        Texture_draw(jump_animation->texture, &jump_animation->frame, &(SDL_Rect) {320, 0, 100, 100});
        Text_draw(jump_text, &(SDL_Rect) {420, 50 - jump_text->height / 2, jump_text->width, jump_text->height});
        
        Texture_draw(run_animation->texture, &run_animation->frame, &(SDL_Rect) {320, 100, 100, 100});
        Text_draw(run_text, &(SDL_Rect) {420, 150 - run_text->height / 2, run_text->width, run_text->height});
        
        App_render();
    }

    TTF_CloseFont(font);

    Animation_destroy(&attack_animation);
    Texture_destroy(&attack_t);
    Animation_destroy(&death_animation);
    Texture_destroy(&death_t);
    Animation_destroy(&fall_animation);
    Texture_destroy(&fall_t);
    Animation_destroy(&get_hit_animation);
    Texture_destroy(&get_hit_t);
    Animation_destroy(&idle_animation);
    Texture_destroy(&idle_t);
    Animation_destroy(&jump_animation);
    Texture_destroy(&jump_t);
    Animation_destroy(&run_animation);
    Texture_destroy(&run_t);

    Text_destroy(&attack_text);
    Text_destroy(&death_text);
    Text_destroy(&fall_text);
    Text_destroy(&get_hit_text);
    Text_destroy(&idle_text);
    Text_destroy(&jump_text);
    Text_destroy(&run_text);

    App_quit();
    Stop();

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
