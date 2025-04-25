#ifndef _START_APPLICATION_H
#define _START_APPLICATION_H

/* ================================================================ */

/**
 * Initializes the application by creating the main window and setting up basic parameters.
 * 
 * @param title a null-terminated string specifying the title of the application window
 * 
 * @return Returns 0 on success, or -1 if window creation fails.
 */
int App_init(const char* title);

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
* @return The delta time in seconds as a double-precision floating-point value
 */
double get_delta(void);

/**
 * Retrieves the current actual frames per second (FPS) of the application.
 * 
 * @return The current actual FPS as an integer.
 */
int get_fps(void);

/**
 * Retrieves the `SDL_Renderer` associated with the application's main window.
 * 
 * @return A pointer to the SDL_Renderer used by the application.
 */
SDL_Renderer* get_context(void);

/* ================================================================ */

#endif /* _START_APPLICATION_H */
