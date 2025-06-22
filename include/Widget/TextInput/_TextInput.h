#ifndef _START_TEXT_INPUT_H
#define _START_TEXT_INPUT_H

#include "../_Widget.h"
#include "../../Text.h"
#include "../../Texture.h"

/* ================================================================ */

struct text_input {

    const struct widget _;

    /* The number of characters that is going to appear on the screen */
    int length;
    int curr_pos;

    /* Text that appears near the field */
    Text* input;

    SDL_Rect ifd;
};

/* ================================================================ */

#endif /* _START_TEXT_INPUT_H */
