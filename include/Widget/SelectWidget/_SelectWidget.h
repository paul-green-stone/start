#ifndef _START_SELECT_WIDGET_H
#define _START_SELECT_WIDGET_H

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif /* _START_SELECT_WIDGET_H */

