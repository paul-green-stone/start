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
    App_init();

    ctx = get_context();
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 22);
    Texture* btn_texture = Texture_new(ctx, "../resources/images/64x32.png");
    Texture* btn_texture_hover = Texture_new(ctx, "../resources/images/64x32_2.png");

    SDL_Rect d = {10, 12, 192, 96};

    Menu* menu = Menu_new(2, &(Vector2) {64, 64});

    void* btn1 = Widget_create(Button, 64, 64, font, &(SDL_Color) {255, 255, 255, 255}, "Button 1", NULL, NULL);
    void* btn2 = Widget_create(Button, 128, 90, font, &(SDL_Color) {255, 255, 255, 255}, "Button 2", NULL, NULL);

    void* input = Widget_create(TextInput, 0, 0, font, &(SDL_Color) {255, 255, 255, 255}, "Input");
    Widget_set_position(input, 0, 350);

    void* select = Widget_create(SelectWidget, 240, 240, font, &(SDL_Color) {255, 255, 255, 255}, "Race");
    SelectWidget_add(select, "Argonian");
    SelectWidget_add(select, "Khajiit");
    SelectWidget_add(select, "Redguard");
    SelectWidget_add(select, "Nord");
    SelectWidget_add(select, "Breton");
    SelectWidget_add(select, "Imperial");
    SelectWidget_add(select, "Orsimer");
    SelectWidget_add(select, "Bosmer");
    SelectWidget_add(select, "Altmer");
    SelectWidget_add(select, "Dunmer");

    Menu_pack(menu, btn1);
    Menu_pack(menu, btn2);

    menu->widget_color = (SDL_Color) {255, 255, 255, 255};

    int menu_w, menu_h;
    Menu_get_dimensions(menu, &menu_w, &menu_h);
    Menu_set_position(menu, 640 / 2 - menu_w / 2, 480 / 2 - menu_h / 2);
    //Menu_set_alignment(menu, CUSTOM);
    
    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:

                    App_stop();
                    break ;
            }

            if (Widget_is_focused(input)) {

                SDL_StartTextInput();
                TextInput_update(input, &event);
            }
            else {
                SDL_StopTextInput();
            }
        }

        Input_update();

        if (Widget_is_focused(input) && Input_wasKey_pressed(SDL_SCANCODE_RETURN)) {
            TextInput_get_input(input, buffer);

            printf("Input: %s\n", buffer);
        }

        SDL_SetRenderDrawColor(ctx, 0, 0, 0, 255);
        SDL_RenderClear(ctx);

        for (size_t i = 0; i < Menu_get_size(menu); i++) {

            if (Widget_is_hovered(menu->widgets[i])) {
                Widget_set_label_color(menu->widgets[i], &(SDL_Color) {255, 0, 0, 255});
            }
            else {
                Widget_set_label_color(menu->widgets[i], &(SDL_Color) {255, 255, 255, 255});
            }
        }

        /* === Handling the input widget; might decide to integrate states === */
        if (Widget_is_hovered(input) && Input_isBtn_pressed(LMB)) {
            Widget_focus(input);
            Widget_set_label_color(input, &(SDL_Color) {0, 255, 0, 255});
        }
        else if (!Widget_is_hovered(input) && Input_isBtn_pressed(LMB)) {
            TextInput_clear(input);
            Widget_unfocus(input);
            Widget_set_label_color(input, &(SDL_Color) {255, 255, 255, 255});
        }
        else if (!Widget_is_focused(input) && Widget_is_hovered(input)) {
            Widget_set_label_color(input, &(SDL_Color) {0, 255, 0, 122});
        }
        else if (!Widget_is_focused(input) && !Widget_is_hovered(input)) {
            Widget_set_label_color(input, &(SDL_Color) {255, 255, 255, 255});
        }
        
        if (Widget_is_hovered(select) && Input_isBtn_pressed(LMB)) {

            Widget_focus(select);
            Widget_set_label_color(select, &(SDL_Color) {0, 255, 0, 255});
        }
        else if (!Widget_is_hovered(select) && Input_isBtn_pressed(LMB)) {
            
            Widget_unfocus(select);
            Widget_set_label_color(select, &(SDL_Color) {255, 255, 255, 255});
        }
        else if (!Widget_is_focused(select) && Widget_is_hovered(select)) {
            Widget_set_label_color(select, &(SDL_Color) {0, 255, 0, 122});
        }
        else if (!Widget_is_focused(select) && !Widget_is_hovered(select)) {
            Widget_set_label_color(select, &(SDL_Color) {255, 255, 255, 255});
        }
        else if (Widget_is_focused(select) && Input_wasKey_pressed(SDL_SCANCODE_RIGHT)) {
            SelectWidget_next(select);
        }
        else if (Widget_is_focused(select) && Input_wasKey_pressed(SDL_SCANCODE_LEFT)) {
            SelectWidget_prev(select);
        }

        Widget_draw(input, NULL, NULL);
        Widget_draw(select, NULL, NULL);

        Menu_draw(menu);
        
        App_render();
    }

    Menu_destroy(&menu);

    Texture_destroy(&btn_texture);
    Texture_destroy(&btn_texture_hover);
    Widget_destroy(input);
    Widget_destroy(select);
    TTF_CloseFont(font);

    App_quit();
    Stop();

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
