#ifndef _START_BUTTON_H
#define _START_BUTTON_H

#include "../_Widget.h"
#include "../../Text.h"
#include "../../Texture.h"

/* ================================================================ */

struct button {

    const struct widget _;

    /* The button's label is what appears on the screen */
    Text* label;

    /* The button's texture if it has any */
    Texture* texture;
    /* Used for drawing widgets via `Menu_draw()` */
    SDL_Rect* default_src;
};

/* ================================================================ */

#endif /* _START_BUTTON_H */
