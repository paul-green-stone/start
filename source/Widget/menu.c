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

    Alignment alignnment;
};

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * 
 */
static void _Menu_align_(const Menu* menu) {

    Vector2 widget_size;

    int x;
    int y;
    size_t i;
    /* ======== */

    if (menu->num_widgets > 0) {

        for (i = 0; (int) i < menu->num_widgets; i++) {

            /* Skip the empty widget */
            if (menu->widgets[i] == NULL) { continue ; }

            Widget_get_dimensions(menu->widgets[i], &widget_size);

            x = (menu->alignnment == CENTER) ? menu->position.x + (menu->width / 2) - (widget_size.x / 2) : 
                (menu->alignnment == RIGHT) ? (menu->position.x + menu->width) - widget_size.x : menu->position.x;
            y = (i == 0) ? menu->position.y : y + widget_size.y + menu->padding.y;

            Widget_set_position(menu->widgets[i], &(Vector2) {x, y});
        }
    }
} 

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
    menu->alignnment = CUSTOM;

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

    /* Do not dereference `NULL` */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* Make sure there is room for a new widget */
    if ((size_t) menu->num_widgets >= menu->max_num_widgets) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    /* ================================ */

    menu->widgets[menu->free_widget_slot++] = (struct widget*) widget;
    menu->num_widgets++;

    Widget_get_dimensions(widget, &widget_dimensions);

    if (menu->num_widgets == 1) {

        menu->width = widget_dimensions.x;
        menu->height = widget_dimensions.y;
    }
    else {

        menu->width = (menu->width >= widget_dimensions.x) ? menu->width + menu->padding.x : widget_dimensions.x;
        menu->height += widget_dimensions.y + (menu->padding.y);
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

    size_t i;

    Vector2 widget_size;
    /* ======== */

    if ((menu == NULL) || (padding == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->padding = *padding;

    if (menu->num_widgets > 0) {
        menu->height = 0;

        for (i = 0; i < menu->max_num_widgets; i++) {

            if (menu->widgets[i] == NULL) { continue ; }

            Widget_get_dimensions(menu->widgets[i], &widget_size);
            menu->height += widget_size.y;

            if (i + 1 != menu->max_num_widgets) menu->height += menu->padding.y;
        }
    }
    
    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_draw(const Menu* menu) {

    int i;

    Text* label = NULL;
    /* ======== */

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (menu->num_widgets > 0) {

        for (i = 0; i < menu->num_widgets; i++) {

            if (menu->widgets[i] == NULL) { continue ; }

            /* Retrieving the widget's label */
            label = Widget_get_label(menu->widgets[i]);

            if (menu->active_widget == i) {
                Text_set_color(label, &menu->active_widget_color);
            }
            else {
                Text_set_color(label, &menu->widget_color);
            }

            /* Draw the widget */
            Widget_draw(menu->widgets[i], NULL);
        }
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_update(Menu* menu) {

    int i;
    int x, y;
    int t;

    SDL_Rect widget_d;
    
    Vector2 pos;
    Vector2 size;
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

    Input_get_cursorPos(&x, &y);

    for (i = 0; i < menu->num_widgets; i++) {

        Widget_get_dimensions(menu->widgets[i], &size);
        Widget_get_position(menu->widgets[i], &pos);

        widget_d = (SDL_Rect) {pos.x, pos.y, size.x, size.y};

        t = PinR(x, y, &widget_d);

        if (t) {
            menu->active_widget = i;
        }

        if (t && Input_wasBtn_pressed(LMB)) {
            return Widget_handle_click(menu->widgets[i], get_state());
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

    if (menu->alignnment != CUSTOM) { _Menu_align_(menu); }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_set_color(Menu* menu, SDL_Color* color) {

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->widget_color = *color;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_set_activeColor(Menu* menu, SDL_Color* color) {

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->active_widget_color = *color;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_set_alignment(Menu* menu, Alignment a) {

    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    menu->alignnment = a;
    _Menu_align_(menu);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
