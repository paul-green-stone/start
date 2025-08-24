#ifndef _START_WINDOW_INTERFACE_H
#define _START_WINDOW_INTERFACE_H

#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

/* Forward Declaration */
typedef struct _window Window;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Create a new instance of a `Window`. The `Window` contains information
 * about `SDL_Window` and `SDL_Renderer` serving as an aggregate.
 * 
 * @param title the title of the window, in UTF-8 encoding.
 * @param width the width of the window, in screen coordinates.
 * @param height the height of the window, in screen coordinates.
 * @param window_flags 0, or one or more `SDL_WindowFlags` OR'd together.
 * 
 * @return Returns the `Window` that was created or `NULL` on failure; call `Error_string()` for more information.
 */
Window* Window_new(const char* title, int width, int height, Uint32 window_flags, Uint32 renderer_flags);

/**
 * Destroy a window.
 * 
 * @param w the window to destroy (`&window`).
 * 
 * @return Returns `SSUCCESS` (0) on success or a negative error code on failure; call `Error_string()` for more information.
 */
int Window_destroy(Window** window);

/**
 * Retrieve the rendering context of a window.
 * 
 * @param window the window from which to retrieve the context.
 * 
 * @return Returns the `SDL_Renderer*` of the window or `NULL` on failure; call `Error_string()` for more information.
 */
SDL_Renderer* Window_get_context(const Window* window);

/**
 * Returns the underlying `SDL_Window` pointer associated with the given `Window` wrapper object.
 * 
 * @param window pointer to the `Window` instance to query
 * 
 * @return Returns the `SDL_Window*` stored inside the `Window` instance, `NULL` on failure; call `Error_string()` for more information.
 */
SDL_Window* Window_get_window(const Window* window);

/* ================================================================ */

#endif /* _START_WINDOW_INTERFACE_H */
