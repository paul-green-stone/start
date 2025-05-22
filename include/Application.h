#ifndef _START_APPLICATION_H
#define _START_APPLICATION_H

#include "Core.h"

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Initializes the application by creating the main window and setting up basic parameters.
 * 
 * @return Returns the `Clock` that was created or NULL on failure; call `Error_get()` for more information
 */
int App_init(void);

/**
 * Cleans up and shuts down the application.
 * 
 * @return None.
 */
void App_quit(void);

/**
 * Checks whether the application is currently running.
 * 
 * @return Returns a non-zero value if the application is running, or 0 if it has been stopped.
 */
int App_isRunning(void);

/**
 * Handles rendering the current frame and manages frame timing to maintain a consistent FPS.
 * 
 * @return None.
 */
void App_render(void);

/**
 * Sets the desired frames per second (FPS) for the application (between 1 and 60)
 * 
 * @param fps The target frames per second to set
 */
void App_setFPS(int fps);

/**
 * Toggles the running state of the application.
 * 
 * @return None.
 */
void App_stop(void);

/**
 * Retrieves the time elapsed between the current and previous frame.
 * 
* @return The delta time in seconds as a double-precision floating-point value.
 */
double get_delta(void);

/**
 * Retrieves the current actual frames per second (FPS) of the application.
 * 
 * @return The current actual FPS as an integer.
 */
int get_fps(void);

/**
 * Retrieves the `SDL_Renderer*` associated with the application's main window.
 * 
 * @return A pointer to the `SDL_Renderer` used by the application on success, `NULL` on failure; call `Error_get()` for more information.
 */
SDL_Renderer* get_context(void);

/**
 * Captures the current rendering output from the `SDL_Window` and saves it as a PNG image file in a `screenshots` directory.
 * 
 * @param filename name of the PNG file to save the screenshot as (e.g., "capture.png")
 * 
 * @return Returns 0 on success or a negative error code on failure; call `Error_get()` for more information.
 */
int take_screenshot(const char* filename);

/**
 * Sets the current application state.
 * 
 * @param state pointer to the new state to set as current
 * 
 * @return None.
 */
void set_state(const void* state);

/**
 * Retrieves the current application state pointer.
 * 
 * @return returns a `void*` pointer to the current state object
 */
void* get_state(void);

/**
 * Retrieves the `SDL_Window*` associated with the application's main window.
 * 
 * @return A pointer to the `SDL_Window` used by the application on success, `NULL` on failure; call `Error_get()` for more information.
 */
SDL_Window* get_window(void);

/* ================================================================ */

#endif /* _START_APPLICATION_H */
