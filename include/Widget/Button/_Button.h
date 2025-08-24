#ifndef _START_BUTTON_H
#define _START_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../Text.h"
#include "../../Texture.h"
#include "../_Widget.h"

/* ================================================================ */
    
struct button {

    const struct widget _;

    /* The button's label is what appears on the screen */
    Text *label;

    /* The button's texture if it has any */
    Texture *texture;
    /* Used for drawing widgets via `Menu_draw()` */
    SDL_Rect *default_src;
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_BUTTON_H */
