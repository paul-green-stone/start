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

struct menu_data {

    /* Number of widgets in a menu */
    int num_widgets;
    /* Maximum number of widgets the a can hold */
    size_t max_num_widgets;
    
    int free_widget_slot;

    /* Menu's width */
    int width;
    /* Menu's height */
    int height;

    /* Distance between menu's widgets and its border */
    int px;
    int py;

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

    int w;
    int h;

    int x;
    int y;
    size_t i;
    /* ======== */

    if (((struct menu_data*)(menu->data))->num_widgets > 0) {

        for (i = 0; (int) i < ((struct menu_data*)(menu->data))->num_widgets; i++) {

            /* === Skip the empty widget === */
            if (menu->widgets[i] == NULL) { continue ; }

            Widget_get_dimensions(menu->widgets[i], &w, &h);

            x = (((struct menu_data*)(menu->data))->alignnment == CENTER) ? ((struct menu_data*)(menu->data))->position.x + (((struct menu_data*)(menu->data))->width / 2) - (w / 2) : 
                (((struct menu_data*)(menu->data))->alignnment == RIGHT) ? (((struct menu_data*)(menu->data))->position.x + ((struct menu_data*)(menu->data))->width) - w : ((struct menu_data*)(menu->data))->position.x;
            y = (i == 0) ? ((struct menu_data*)(menu->data))->position.y : y + h + ((struct menu_data*)(menu->data))->py;

            Widget_set_position(menu->widgets[i], x, y);
        }
    }
} 

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Menu* Menu_new(int _num_widgets, Vector2* position) {

    Menu* menu = NULL;
    struct menu_data* data = NULL;
    /* ======== */

    /* === Let the minimum number of widgets be one === */
    int num_widgets = (_num_widgets < 1) ? 1 : _num_widgets;

    /* === Allocating space for the menu's control structure === */
    if ((data = calloc(1, sizeof(struct menu_data))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* === Allocating space for the menu itself === */
    if ((menu = calloc(1, sizeof(struct menu))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* === Allocating array of widgets === */
    if ((menu->widgets = calloc(num_widgets, sizeof(struct widget*))) == NULL) {
        
        free(data);
        free(menu);

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* === Setting up the control structure === */
    menu->data = (void*) data;

    ((struct menu_data*)(menu->data))->max_num_widgets = num_widgets;
    ((struct menu_data*)(menu->data))->py = 16;
    ((struct menu_data*)(menu->data))->px = 0;
    ((struct menu_data*)(menu->data))->position = *position;
    ((struct menu_data*)(menu->data))->alignnment = CUSTOM;

    menu->active_widget = -1;
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

    /* == Destroying widgets if there are any === */
    if (((struct menu_data*)((*menu)->data))->num_widgets > 0) {
        for (i = 0; i < ((struct menu_data*)((*menu)->data))->max_num_widgets; i++) {

            if ((*menu)->widgets[i] == NULL) {
                continue ;
            }
            
            Widget_destroy((*menu)->widgets[i]);
        }
    }

    /* === Destroying the `menu_data` structure === */
    free((*menu)->data);
    /* === Destroying the menu itself === */
    free(*menu);

    *menu = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_pack(Menu* menu, const void* widget) {

    int w;
    int h;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Make sure there is room for a new widget === */
    if ((size_t) ((struct menu_data*)(menu->data))->num_widgets >= ((struct menu_data*)(menu))->max_num_widgets) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    /* ================================ */

    menu->widgets[((struct menu_data*)(menu->data))->free_widget_slot++] = (struct widget*) widget;
    ((struct menu_data*)(menu->data))->num_widgets++;

    Widget_get_dimensions(widget, &w, &h);

    if (((struct menu_data*)(menu))->num_widgets == 1) {

        ((struct menu_data*)(menu))->width = w;
        ((struct menu_data*)(menu))->height = h;
    }
    else {

        ((struct menu_data*)(menu->data))->width = ((struct menu_data*)(menu))->width >= w ? ((struct menu_data*)(menu))->width + ((struct menu_data*)(menu))->px : w;
        ((struct menu_data*)(menu->data))->height += h + ((struct menu_data*)(menu))->py;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_get_size(const Menu* menu) {

    /* === Do not dereference `NULL` === */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ======== */
    return ((struct menu_data*)(menu->data))->num_widgets;
}

/* ================================================================ */

int Menu_set_padding(Menu* menu, int x, int y) {

    size_t i;

    int w;
    int h;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    ((struct menu_data*)(menu->data))->px = x;
    ((struct menu_data*)(menu->data))->py = y;

    if (((struct menu_data*)(menu->data))->num_widgets > 0) {
        ((struct menu_data*)(menu->data))->height = 0;

        for (i = 0; i < ((struct menu_data*)(menu->data))->max_num_widgets; i++) {

            if (menu->widgets[i] == NULL) { continue ; }

            Widget_get_dimensions(menu->widgets[i], &w, &h);
            ((struct menu_data*)(menu->data))->height += h;

            if (i + 1 != ((struct menu_data*)(menu->data))->max_num_widgets) ((struct menu_data*)(menu->data))->height += ((struct menu_data*)(menu->data))->py;
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

    if (((struct menu_data*)(menu->data))->num_widgets > 0) {

        for (i = 0; i < ((struct menu_data*)(menu->data))->num_widgets; i++) {

            if (menu->widgets[i] == NULL) { continue ; }

            /* === Draw the widget === */
            Widget_draw(menu->widgets[i], NULL, NULL);
        }
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_get_dimensions(const Menu* menu, int* w, int* h) {

    /* === Do not dereference `NULL` === */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (w != NULL) *w = ((struct menu_data*)(menu->data))->width;
    if (h != NULL) *h = ((struct menu_data*)(menu->data))->height;

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

    ((struct menu_data*)(menu->data))->position.x = x;
    ((struct menu_data*)(menu->data))->position.y = y;

    if (((struct menu_data*)(menu->data))->alignnment != CUSTOM) { _Menu_align_(menu); }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Menu_set_alignment(Menu* menu, Alignment a) {

    /* === Do not dereference `NULL` === */
    if (menu == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    ((struct menu_data*)(menu->data))->alignnment = a;
    _Menu_align_(menu);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
