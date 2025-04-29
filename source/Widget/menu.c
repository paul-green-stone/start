#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>

#include "../../include/Widget/Menu.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Widget/Widget.h"
#include "../../include/Math/Vector2D.h"
#include "../../include/Application.h"
#include "../../include/Input.h"

/* ================================================================ */

struct menu {

    /* Number of widgets in a menu */
    int num_widgets;
    /* Maximum number of widgets the a can hold */
    size_t max_num_widgets; 

    /* The array of widgets */
    struct widget** widgets;

    int active_widget;
    int free_widget_slot;

    SDL_Color widget_color;
    SDL_Color active_widget_color;

    /* Menu's width */
    int width;
    /* Menu's height */
    int height;

    /* Distance between menu's widgets and its border */
    Vector2 padding;

    Vector2 position;
};

/* ================================================================ */

Menu* Menu_new(int _num_widgets, Vector2* position) {

    Menu* menu;
    int num_widgets;

    /* ======== */

    num_widgets = (_num_widgets < 1) ? 1 : _num_widgets;

    /* ================================ */
    /* ==== Menu Memory Allocation ==== */
    /* ================================ */

    if ((menu = calloc(1, sizeof(struct menu))) == NULL) {
        return NULL;
    }

    /* ================================ */
    /* ======= Array of Widgets ======= */
    /* ================================ */

    if ((menu->widgets = calloc(num_widgets, sizeof(struct widget*))) == NULL) {

        free(menu);

        /* ======== */

        return NULL;
    }

    menu->active_widget = -1;
    menu->max_num_widgets = num_widgets;
    menu->padding.y = 16;
    menu->padding.x = 0;
    menu->position = *position;

    /* Active color */
    menu->active_widget_color.r = 255;
    menu->active_widget_color.g = 0;
    menu->active_widget_color.b = 0;
    menu->active_widget_color.a = 255;

    /* Regular Color */
    menu->widget_color.a = 255;

    /* ======== */

    return menu;
}

/* ================================================================ */

int Menu_destroy(Menu** menu) {

    size_t i;

    if ((menu == NULL) || (*menu == NULL)) {
        return -1;
    }

    /* If there are widgets in the menu */
    if ((*menu)->num_widgets > 0) {

        for (i = 0; i < (*menu)->max_num_widgets; i++) {

            if ((*menu)->widgets[i] == NULL) {
                continue ;
            }

            Widget_destroy((*menu)->widgets[i]);
        }
    }

    free(*menu);
    *menu = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_pack(Menu* menu, const void* widget) {

    Vector2 widget_dimensions;

    if ((menu == NULL) || (widget == NULL)) {
        return -1;
    }

    if ((size_t) menu->num_widgets >= menu->max_num_widgets) {
        return -3;
    }

    menu->widgets[menu->free_widget_slot++] = (struct widget*) widget;
    menu->num_widgets++;

    Widget_get_dimensions(widget, &widget_dimensions);

    if (menu->num_widgets == 1) {
        menu->width = widget_dimensions.x;
        menu->height = widget_dimensions.y;
    }
    else {
        menu->width = (menu->width >= widget_dimensions.x) ? menu->width + menu->padding.x : widget_dimensions.x;
        menu->height += widget_dimensions.y + menu->padding.y;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_get_size(const Menu* menu) {

    if (menu == NULL) {
        return -1;
    }

    return menu->num_widgets;
}

/* ================================================================ */

int Menu_set_padding(Menu* menu, Vector2* padding) {

    if (menu == NULL) {
        return -1;
    }

    menu->padding = *padding;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_draw(const Menu* menu, Alignment a) {

    int i;
    int previous_Y_position;
    SDL_Rect rect;

    Text* label;

    /* ======== */

    if (menu == NULL) {
        return -1;
    }

    if (menu->num_widgets > 0) {

        previous_Y_position = menu->position.y;

        /* For every widget in the menu */
        for (i = 0; i < menu->num_widgets; i++) {

            if (menu->widgets[i] == NULL) {
                continue ;
            }

            /* Retrieving the widget's label */
            label = Widget_get_label(menu->widgets[i]);

            /* rect.x = menu->position.x + menu->padding.x; */
            rect.y = previous_Y_position;
            rect.w = label->width;
            rect.h = label->height;

            /* Align the widget across the X axis */
            rect.x = (a == CENTER) ? menu->position.x + menu->padding.x + ((menu->width / 2) - (label->width / 2)) : (a == RIGHT) ? menu->position.x + menu->padding.x : menu->position.x + menu->padding.x + menu->width - label->width;

            if (menu->active_widget == i) {
                Text_set_color(label, &menu->active_widget_color);
            }
            else {
                Text_set_color(label, &menu->widget_color);
            }

            /* Draw the widget */
            Widget_draw(menu->widgets[i], &rect);

            previous_Y_position += label->height + menu->padding.y;
        }
    }

    /* rect.x = menu->position.x;
    rect.y = menu->position.y;
    rect.w = menu->width + (menu->padding.x * 2);
    rect.h = menu->height;

    SDL_RenderDrawRect(get_context(), &rect); */

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_update(Menu* menu, SDL_Scancode up_key, SDL_Scancode down_key, SDL_Scancode trigger) {

    int i;

    if (menu == NULL) {
        return -1;
    }

    if (Input_wasKey_pressed(up_key)) {

        if ((menu->active_widget == -1) || (menu->active_widget == 0)) {
            menu->active_widget = menu->num_widgets - 1;
        }
        else {
            menu->active_widget -= 1;
        }
    }

    if (Input_wasKey_pressed(down_key)) {

        if ((menu->active_widget == -1) || (menu->active_widget == (int)(menu->num_widgets - 1))) {
            menu->active_widget = 0;
        } else {
            menu->active_widget += 1;
        }
    }
    
    if (Input_wasKey_pressed(trigger)) {

        for (i = 0; i < menu->num_widgets; i++) {

            if (menu->active_widget == i) {
                
                Widget_handle_click(menu->widgets[i], NULL);

                /* ======== */

                return 0;
            }
        }
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_get_dimensions(const Menu* menu, Vector2* dimensions) {

    if ((menu == NULL) || (dimensions == NULL)) {
        return -1;
    }

    dimensions->x = menu->width;
    dimensions->y = menu->height;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Menu_set_position(Menu* menu, int x, int y) {

    if (menu == NULL) {
        return -1;
    }

    menu->position.x = x;
    menu->position.y = y;

    /* ======== */

    return 0;
}

/* ================================================================ */
