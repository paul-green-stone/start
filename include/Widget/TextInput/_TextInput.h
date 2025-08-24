#ifndef _START_TEXT_INPUT_H
#define _START_TEXT_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../_Widget.h"
#include "../../Text.h"
#include "../../Texture.h"

/* ================================================================ */

struct text_input {

    /* Base widget class */
    const struct widget _;

    /* The number of characters that is going to appear on the screen */
    int length;
    /* Position into which we insert a character */
    int curr_pos;

    /* Text that appears near the field */
    Text* input;

    /* Input Field Dimensions. Remember to update this if you make changes */
    SDL_Rect ifd;
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_TEXT_INPUT_H */
