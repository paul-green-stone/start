#ifndef _START_MENU_H
#define _START_MENU_H

#include <stdlib.h>
#include <stddef.h>

#include "../Math/Vector2D.h"

/* ================================ */

typedef struct menu Menu;

/**
 * Defines the possible alignment options for arranging widgets inside a menu
 * 
 * @param LEFT align widgets to the left edge of the menu or container
 * @param RIGHT align widgets to the right edge of the menu or container.
 * @param CENTER center widgets horizontally within the menu or container.
 */
typedef enum {LEFT, RIGHT, CENTER} Alignment;

/* ================================================================ */

/**
 * Creates and initializes a new `Menu` structure capable of holding a specified number of widgets.
 * 
 * @param num_widgets number of widget pointers the menu should be able to hold
 * @param position pointer to a `Vector2` struct specifying the menu's position coordinates
 * 
 * @return Returns a pointer to a newly allocated and initialized `Menu` instance or NULL on failure.
 */
Menu* Menu_new(int num_widgets, Vector2* position);

/**
 * Destroys a `Menu` instance by properly releasing all associated resources,
 * including destroying each widget contained in the menu and freeing the menu structure itself.
 * 
 * @param menu a pointer to a pointer to the `Menu` instance to be destroyed
 * 
 * @return Returns 0 on success or -1 on failure.
 */
int Menu_destroy(Menu** menu);

/**
 * Adds a widget to the menu.
 * 
 * @param menu pointer to the menu instance to add the widget to
 * @param widget pointer to the widget instance to be added
 * 
 * @return Returns 0 when the widget is successfully added or a negative error code on failure.
 */
int Menu_pack(Menu* menu, const void* widget);

/**
 * Returns the current number of widgets contained in the given menu.
 * 
 * @param menu pointer to the menu instance to query
 * 
 * @return Returns the number of widgets currently in the menu, -1 if the menu pointer is NULL.
 */
int Menu_get_size(const Menu* menu);

/**
 * Sets the padding value for a menu.
 * The padding typically defines the spacing around or between widgets within the menu.
 * 
 * @param menu pointer to the menu instance to modify
 * @param padding pointer to a `Vector2` struct containing the new padding values
 * 
 * @return Returns 0 on success, -1 on failure.
 */
int Menu_set_padding(Menu* menu, Vector2* padding);

/**
 * Draws all widgets contained within a menu, positioning them vertically with specified alignment along the X axis.
 * 
 * @param menu pointer to the menu instance containing widgets to draw
 * @param a alignment mode for horizontal positioning of widgets
 * 
 * @return Returns 0 on success, -1 on failure.
 */
int Menu_draw(const Menu* menu, Alignment a);

/**
 * Updates the active widget selection in the menu based on keyboard input.
 * 
 * @param menu pointer to the menu instance to update
 * @param up_key `SDL_Scancode` representing the key to move selection up
 * @param down_key `SDL_Scancode` representing the key to move selection down
 * 
 * @return Returns 0 on success, -1 on failure.
 */
int Menu_update(Menu* menu, SDL_Scancode up_key, SDL_Scancode down_key);

/* ================================================================ */

#endif /* _START_MENU_H */
