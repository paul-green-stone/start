#include <stdlib.h>

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../../include/Widget/Widgets.h"
#include "../../include/Widget/_Class.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Widget/TextInput/_TextInput.h"

#include "../../include/Error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

void* Widget_create(const void* _class, ...) {

    /* === Table of pointers to functions. Each class of widgets has its own constructor === */
    const struct Class* class = _class;
    /* === The widget we are creating === */
    void* widget = NULL;

    int status = SSUCCESS;

    va_list ap;
    /* ======== */

    /* === Do not dereference `NULL` ===*/
    if (_class == NULL) {

        status = SERR_NULL_POINTER;
        /* ======== */
        goto ERROR;
    }

    /* === Allocating enough bytes of memory as specified by the widget's class description === */
    if ((widget = calloc(1, class->size)) == NULL) {

        status = SERR_SYSTEM;
        /* ======== */
        goto ERROR;
    }

    *(const struct Class**) widget = class;

    /* === Calling the widget's contructor if it has one === */
    if (class->ctor) {

        va_start(ap, _class);
        
        /* === Make sure the constructor runs successfully === */
        if ((widget = class->ctor(widget, &ap)) == NULL) {

            /* === `Widget_destroy()` will deallocate memory allocated by the previous `calloc` call === */
            Widget_destroy(widget);
            widget = NULL;
        }

        va_end(ap);
    }

    /* ======== */
    return widget;

    ERROR: {

        Error_set(status);
        /* ======== */
        return widget;
    };
}

/* ================================================================ */

int Widget_destroy(void* _widget) {

    const struct Class** class_p = _widget;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_widget == NULL) || (class_p == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Calling the widget's destructor if it has one === */
    if ((*class_p)->dtor != NULL) {
        _widget = (*class_p)->dtor(_widget);
    }

    /* === Freeing the space occupied by the `Widget` widget === */
    free(_widget);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_draw(const void* _widget, const SDL_Rect* src, const SDL_Rect* dst) {

    const struct Class* const* class_p = _widget;
    struct widget* widget = (struct widget*) _widget;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_widget == NULL) && (*class_p == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Update the widget's dimensions to properly handle its callbacks === */
    if (dst != NULL) {
        widget->width = dst->w;
        widget->height = dst->h;
    }

    /* === Let the widget's descriptor decide how to draw itself === */
    if ((*class_p)->draw != NULL) {
        return (*class_p)->draw(_widget, src, dst);
    }

    Error_set(SERR_NOT_IMPLEMENTED);

    /* ======== */
    return SERR_NOT_IMPLEMENTED;
}

/* ================================================================ */

int Widget_set_position(void* _self, int x, int y) {

    struct widget* self = _self;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    self->x = x;
    self->y = y;

    if (((void**) self->_class) == TextInput) {
        
        struct text_input* s = _self;
        /* ======== */

        s->ifd.x = self->x + self->label->width + 16;
        s->ifd.y = self->y;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_get_position(const void* _self, int* x, int* y) {

    const struct widget* self = _self;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */
    
    if (x != NULL) { *x = self->x; }
    if (y != NULL) { *y = self->y; }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_get_dimensions(const void* _self, int* w, int* h) {

    const struct widget* self = _self;

    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    if (w != NULL) { *w = self->width; }
    if (h != NULL) { *h = self->height; }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_bind_callback(void* _self, int (callback)(const void* widget, va_list* args)) {

    struct widget* self = _self;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    /* === Binding `NULL` will simply remove a callback function from a widget === */
    self->on_click = callback;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_click(const void* _self, ...) {

    const struct widget* self = _self;

    int x;
    int y;

    SDL_Rect widget_rect;

    va_list ap;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */

    /* === Get the current mouse cursor position === */
    Input_get_cursorPos(&x, &y);

    /* === Updating the widget's area === */
    widget_rect = (SDL_Rect) {.x = self->x, .y = self->y, .w = self->width, .h = self->height};
    
    if ((self->on_click != NULL) && Input_wasBtn_pressed(LMB) && (PinR(x, y, &widget_rect))) {

        va_start(ap, _self);

        self->on_click(_self, &ap);

        va_end(ap);
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Widget_is_hovered(const void* _self) {

    const struct widget* self = _self;

    int x;
    int y;

    SDL_Rect widget_area;
    /* ======== */

    /* === Do not dereference `NULL` === */
    if ((_self == NULL) || (self == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    widget_area = (SDL_Rect) {.x = self->x, .y = self->y, .w = self->width, .h = self->height};
    Input_get_cursorPos(&x, &y);

    /* ======== */
    return PinR(x, y, &widget_area);
}

/* ================================================================ */

void Widget_focus(void* _self) {

    struct widget* self = _self;
    /* ======== */

    self->is_focused = 1;
}

/* ================================================================ */

void Widget_unfocus(void* _self) {

    struct widget* self = _self;
    /* ======== */

    self->is_focused = 0;
}

/* ================================================================ */

int Widget_set_label_color(void* _self, const SDL_Color* color) {

    struct widget* self = _self;
    /* ======== */

    if (self == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ======== */
    return Text_set_color(self->label, color);
}

/* ================================================================ */

int Widget_is_focused(const void* _self) {
    return ((struct widget*) _self)->is_focused;
}

/* ================================================================ */
