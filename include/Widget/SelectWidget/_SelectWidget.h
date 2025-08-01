#ifndef _START_SELECT_WIDGET_H
#define _START_SELECT_WIDGET_H

#include "../_Widget.h"
#include "../../Text.h"
#include "../../List.h"

/* ================================================================ */

struct select_widget {

    /* Base widget class */
    const struct widget _;

    /* A linked list of options */
    List options;
    Node* node_option;
    Text* text_option;

    /* Where to render the option on the screen */
    SDL_Rect option_dst;
};

/* ================================================================ */

#endif /* _START_SELECT_WIDGET_H */

