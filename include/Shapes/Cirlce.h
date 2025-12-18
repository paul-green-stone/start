#ifndef _START_CIRCLE_SHAPE_H
#define _START_CIRCLE_SHAPE_H

#include "../Math/Vector2D.h"

/* ================================================================ */

/**
 * 
 */
typedef struct circle {

    Vector2 center;
    float radius;
} Circle;

/**
 * Draws a circle using the midpoint circle algorithm.
 * 
 * @param circle pointer to a `Circle` structure.
 * 
 * @return None.
 * 
 * @note The behavior is undefined if a circle is `NULL`.
 */
void Cirlce_draw(const Circle* circle);

/* ================================================================ */

#endif /* _START_CIRCLE_SHAPE_H */