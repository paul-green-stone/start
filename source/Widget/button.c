#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

#include "../../include/Widget/Widget.h"
#include "../../include/Widget/_Widget.h"
#include "../../include/Widget/Button.h"
#include "../../include/Math/Vector2D.h"
#include "../../include/Text.h"
#include "../../include/Application.h"

/* ================================================================ */

struct button {

    /* The type descriptor. Always goes first */
    const void* descriptor;

    /* Button's top left corner coordinates */
    Vector2 position;
    Text* label;
    action on_click;            /* What to do on a mouse click or key press */
};

/* ================================ */

/**
 * Constructor function for a `Button` widget.
 * It initializes a button instance by extracting constructor arguments
 * from a variable argument list and setting up its internal state,
 * including creating a text label.
 * 
 * @param _self pointer to pre-allocated memory for the button instance
 * @param app pointer to a variable argument list containing constructor parameters
 * 
 * @return Returns a pointer to initialized button instance or NULL if initialization fails.
 */
static void* Button_ctor(void* _self, va_list* app) {

    struct button* self;
    SDL_Renderer* context;
    
    TTF_Font* font;
    SDL_Color* color;
    const char* label;
    Vector2* position;

    /* ======== */

    self = _self;
    context = get_context();

    /* ================================================ */
    /* ====== Extracting arguments from the list ====== */
    /* ================================================ */

    font = va_arg(*app, TTF_Font*);
    color = va_arg(*app, SDL_Color*);
    label = va_arg(*app, const char*);
    position = va_arg(*app, Vector2*);

    /* ================================================ */

    if ((self->label = Text_new(context, font, color, label)) == NULL) {
        return NULL;
    }

    self->position = *position;

    /* ======== */

    return self;
}

/* ================================================================ */

/**
 * Destructor function for a `Button` widget.
 * 
 * It performs cleanup of resources allocated during the button's lifetime,
 * specifically destroying the button's label text.
 * 
 * @param _self pointer to the button instance to be destroyed
 * 
 * @return Returns the pointer to the button instance after cleanup.
 */
static void* Button_dtor(void* _self) {
    
    struct button* self;
    self = _self;

    Text_destroy(&(self->label));

    /* ======== */

    return self;
}

/* ================================================================ */

/**
 * Renders a button by drawing its label text at the button's position.
 * 
 * @param _self a pointer to the button instance to be drawn
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
static int Button_draw(const void* _self, const SDL_Rect* dst) {

    const struct button* self;
    SDL_Rect rect;

    /* ======== */

    self = _self;

    if (dst == NULL) {

        rect.x = self->position.x;
        rect.y = self->position.y;
        rect.w = self->label->width;
        rect.h = self->label->height;
    }
    else {
        rect = *dst;
    }

    /* ======== */

    return Text_draw(self->label, &rect);
}

/* ================================================================ */

/**
 * Calculates and returns the total dimensions (width and height) of a button widget.
 * 
 * @param _self pointer to the button instance
 * 
 * @return Returns a `Vector2` struct containing: `x` - total width of the button; `y` - total height of the button.
 */
Vector2 Button_get_dimensions(const void* _self) {

    const struct button* self;
    Vector2 dimensions;

    /* ======== */

    self = _self;

    dimensions.x = self->label->width;
    dimensions.y = self->label->height;

    /* ======== */

    return dimensions;
}

/* ================================================================ */

/**
 * Returns a pointer to the label text object associated with the button.
 * 
 * @param _self pointer to the button instance
 * 
 * @return Returns a pointer to the `Text` object representing the button's label.
 */
Text* Button_get_label(const void* _self) {

    const struct button* self;
    self = _self;

    /* ======== */

    return self->label;
}

/* ================================================================ */

/**
 * Assigns a callback function to a button's click event.
 * 
 * @param _self pointer to the button instance
 * @param callback function pointer to the callback
 * 
 * @return None.
 */
void Button_bind_callback(void* _self, action callback) {

    struct button* self;
    self = _self;

    self->on_click = callback;
}

/* ================================================================ */

/**
 * Triggers the button's on_click callback function when a click event occurs.
 * 
 * @param _self pointer to the button instance
 * @param data arbitrary data passed to the `on_click` callback (e.g., event details or user context)
 * 
 * @return None (for now).
 */
void Button_handle_click(const void* _self, va_list* app) {

    const struct button* self;
    self = _self;

    if (self->on_click == NULL) {
        return ;
    }

    self->on_click(app);
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct widget _Button = {

    sizeof(struct button),  /* .size */

    Button_ctor,            /* .ctor */
    Button_dtor,            /* .dtor */

    Button_draw,            /* .draw */

    Button_get_dimensions,  /* get_dimensions */
    Button_get_label,       /* get_label */

    Button_bind_callback,   /* bind */
    Button_handle_click,    /* handle_click */
};

const void* Button = &_Button;

/* ================================================================ */
