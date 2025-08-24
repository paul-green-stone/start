#ifndef _START_INPUT_H
#define _START_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

typedef enum {LMB, MMB, RMB} MouseButton;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Updates the input state by polling the current keyboard and mouse states using SDL.
 * It maintains both the current and previous states of keyboard keys and mouse buttons
 * to facilitate input handling such as detecting key/button presses, releases, and holds.
 * 
 * @return None.
 */
void Input_update(void);

/**
 * Checks whether a specific keyboard key is currently pressed.
 * 
 * @param key the SDL scancode representing the keyboard key to check.
 * 
 * @return Non-zero (true) if the specified key is currently pressed, or zero (false) if the key is not pressed.
 */
int Input_isKey_pressed(SDL_Scancode key);

/**
 * Determines whether a specific keyboard key was just pressed in the current update cycle.
 * 
 * @param key the SDL scancode representing the keyboard key to check.
 * 
 * @return Non-zero (true) if the key transitioned from not pressed in the previous state to pressed in the current state (i.e., the key was just pressed). Zero (false) otherwise.
 */
int Input_wasKey_pressed(SDL_Scancode key);

/**
 * Checks whether a specific mouse button is currently pressed.
 * 
 * @param btn the mouse button to check
 * 
 * @return Non-zero (true) if the specified mouse button is currently pressed, or zero (false) if the button is not pressed.
 */
int Input_isBtn_pressed(MouseButton btn);

/**
 * Determines whether a specific mouse button was just pressed in the current update cycle.
 * 
 * @param btn the mouse button to check
 * 
 * @return Non-zero (true) if the button transitioned from not pressed in the previous state to pressed in the current state (i.e., the key was just pressed). Zero (false) otherwise.
 */
int Input_wasBtn_pressed(MouseButton btn);

/**
 * Retrieves the current position of the mouse cursor.
 * 
 * @param[out] x Pointer to an integer where the cursor's X coordinate will be stored
 * @param[out] y Pointer to an integer where the cursor's Y coordinate will be stored
 * 
 * @return None.
 */
void Input_get_cursorPos(int* x, int* y);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_INPUT_H */
