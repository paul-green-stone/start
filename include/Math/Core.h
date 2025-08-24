#ifndef _START_CORE_MATH_H
#define _START_CORE_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */

/**
 * Checks if a point is inside a given rectangle.
 * 
 * @param x x-coordinate of the point.
 * @param y y-coordinate of the point.
 * @param rect Pointer to an `SDL_Rect` like structure with members `x`, `y`, `w`, and `h`
 * 
 * @return Non-zero (true) if the point is inside the rectangle; zero (false) otherwise.
 */
#define PinR(x, y, rect) ((x) > (rect)->x && x < (rect)->x + (rect)->w) && (y > (rect)->y && y < (rect)->y + (rect)->h)

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_CORE_MATH_H */
