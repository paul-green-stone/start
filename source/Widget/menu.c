#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>

#include "../../include/Widget/Menu.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Widget/Widget.h"
#include "../../include/Math/Vector2D.h"
#include "../../include/Application.h"
#include "../../include/Input.h"
#include "../../include/Error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct menu {

    /* Number of widgets in a menu */
    int num_widgets;
    /* Maximum number of widgets the a can hold */
    size_t max_num_widgets; 

    /* The array of widgets */
    struct widget** widgets;

    /* A widget that is being focused on */
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

    /* Menu position on the screen */
    Vector2 position;
};

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Menu* Menu_new(int _num_widgets, Vector2* position) {

    Menu* menu = NULL;

    int num_widgets = (_num_widgets < 1) ? 1 : _num_widgets;
    /* ======== */

    /* ==== Menu Memory Allocation ==== */
    if ((menu = calloc(1, sizeof(struct menu))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL; 
    }

    /* ==== Array of Widgets Allocation ==== */
    if ((menu->widgets = calloc(num_widgets, sizeof(struct widget*))) == NULL) {

        free(menu);
        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    menu->active_widget = -1;
    menu->max_num_widgets = num_widgets;
    menu->padding.y = 16;
    menu->padding.x = 0;
    menu->position = *position;
    menu->active_widget_color = (SDL_Color) {255, 0, 0, 255};
    menu->widget_color.a = 255;

    /* ======== */
    return menu;
}

/* ================================================================ */

int Menu_destroy(Menu** menu) {

    size_t i;
    /* ======== */

    if ((menu == NULL) || (*menu == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
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
    return SSUCCESS;
}

/* ================================================================ */

int Menu_pack(Menu* menu, const void* widget) {

    Vector2 widget_dimensions;
    /* ======== */

    if ((menu == NULL) || (widget == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if ((size_t) menu->num_widgets >= menu->max_num_widgets) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    menu->widgets[menu->free_widget_slot++] = (struct widget*) widget;
    menu->num_widgets++;

    if (Widget_get_dimensions(widget, &widget_dimensions) == SSUCCESS) {

        if (menu->num_widgets == 1) {

            menu->width = widget_dimensions.x;
            menu->height = widget_dimensions.y;
        }
        else {

            menu->width = (menu->width >= widget_dimensions.x) ? menu->width + menu->padding.x : widget_dimensions.x;
            menu->height += widget_dimensions.y + menu->padding.y;
        }
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_get_size(const Menu* menu) {

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ======== */
    return menu->num_widgets;
}

/* ================================================================ */

int Menu_set_padding(Menu* menu, Vector2* padding) {

    if ((menu == NULL) || (padding = NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->padding = *padding;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_draw(const Menu* menu, Alignment a) {

    int i;
    int previous_Y_position;
    SDL_Rect rect;

    Text* label = NULL;
    /* ======== */

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
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

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_update(Menu* menu) {

    int i;
    /* ======== */

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (Input_wasKey_pressed(SDL_SCANCODE_UP)) {

        if ((menu->active_widget == -1) || (menu->active_widget == 0)) {
            menu->active_widget = menu->num_widgets - 1;
        }
        else {
            menu->active_widget -= 1;
        }
    }

    if (Input_wasKey_pressed(SDL_SCANCODE_DOWN)) {

        if ((menu->active_widget == -1) || (menu->active_widget == (int)(menu->num_widgets - 1))) {
            menu->active_widget = 0;
        } else {
            menu->active_widget += 1;
        }
    }
    
    if (Input_wasKey_pressed(SDL_SCANCODE_RETURN)) {

        for (i = 0; i < menu->num_widgets; i++) {

            if (menu->active_widget == i) {
                return Widget_handle_click(menu->widgets[i], get_state());
            }
        }
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_get_dimensions(const Menu* menu, Vector2* dimensions) {

    if ((menu == NULL) || (dimensions == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    dimensions->x = menu->width;
    dimensions->y = menu->height;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_set_position(Menu* menu, int x, int y) {

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->position.x = x;
    menu->position.y = y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
