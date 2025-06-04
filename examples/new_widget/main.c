#include "../../include/Start.h"

int click(const void* _self, va_list* args) {

    const char* string = va_arg(*args, const char*);

    printf("%s\n", string);
}

/* ================================================================ */

int main(int argc, char** argv) {

    SDL_Event event;
    SDL_Renderer* ctx;

    Start();
    App_init();

    ctx = get_context();
    TTF_Font* font = TTF_OpenFont("../resources/8bitOperatorPlus8-Regular.ttf", 22);
    Texture* btn_texture = Texture_new(ctx, "../resources/images/64x32.png");
    Texture* btn_texture_hover = Texture_new(ctx, "../resources/images/64x32_2.png");

    void* widget = Widget_create(Button, 10, 12, NULL, NULL, NULL, btn_texture);\

    Widget_bind_callback(widget, click);

    SDL_Rect d = {10, 12, 192, 96};

    Menu* menu = Menu_new(2, &(Vector2) {64, 64});

    void* btn1 = Widget_create(Button, 0, 0, font, &(SDL_Color) {255, 255, 255, 255}, "Button 1", NULL);
    void* btn2 = Widget_create(Button, 0, 0, font, &(SDL_Color) {255, 255, 255, 255}, "Button 2", NULL);

    Menu_pack(menu, btn1);
    Menu_pack(menu, btn2);

    menu->widget_color = (SDL_Color) {255, 255, 255, 255};

    Menu_set_alignment(menu, CENTER);

    printf("%ld\n", Menu_get_size(menu));

    int menu_w, menu_h;
    Menu_get_dimensions(menu, &menu_w, &menu_h);
    Menu_set_position(menu, 640 / 2 - menu_w / 2, 480 / 2 - menu_h / 2);
    Menu_set_alignment(menu, CUSTOM);
    
    while (App_isRunning()) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:

                    App_stop();
                    break ;
            }
        }

        Input_update();

        // Widget_click(widget, "Hello, World!");

        // if (Widget_is_focused(widget)) {
        //    Button_set_texture(widget, btn_texture_hover);
        // }
        // else {
        //    Button_set_texture(widget, btn_texture);
        // }

        // SDL_SetRenderDrawColor(ctx, 255, 255, 255, 255);
        // SDL_RenderClear(ctx);
        
        // Widget_draw(widget, NULL, &d);

        for (size_t i = 0; i < Menu_get_size(menu); i++) {

            if (Widget_is_focused(menu->widgets[i])) {
                Button_set_label_color(menu->widgets[i], &(SDL_Color) {255, 0, 0, 255});
            }
            else {
                Button_set_label_color(menu->widgets[i], &(SDL_Color) {255, 255, 255, 255});
            }
        }

        Menu_draw(menu);
        
        App_render();
    }

    Texture_destroy(&btn_texture);
    Texture_destroy(&btn_texture_hover);
    TTF_CloseFont(font);

    App_quit();
    Stop();

    Widget_destroy(widget);

    /* ======== */
    return EXIT_SUCCESS;    
}

/* ================================================================ */
