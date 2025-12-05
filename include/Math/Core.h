#ifndef _START_CORE_MATH_H
#define _START_CORE_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Vector2D.h"
#include <math.h>
#include <stdbool.h>

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

/**
 * Generate a random number (`float`) from the given range 
 */
#define rand_float(min, max) (((float) rand() / (float) RAND_MAX) * (max - min) + min)

/**
 * Generate a random number (`int`) from the given range 
 */
#define rand_int(min, max) (rand() % ((max) - (min) + 1) + (min))

/**
 * Find which of the two numbers is smaller
 */
#define min(x, y) ((x) > (y) ? (y) : (x))

/**
 * Find which of the two numbers is bigger
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

/**
 * Compares two floating-point values for approximate equality.
 */
#define eqf(a, b) fasbs((a) - (b)) < 1.0f / 8192.0f

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_CORE_MATH_H */
