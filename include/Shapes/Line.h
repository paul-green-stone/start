#ifndef _START_LINE_SHAPE_H
#define _START_LINE_SHAPE_H

#include "../Math/Vector2D.h"

/* ================================================================ */

/**
 * 
 */
typedef struct line {

    Vector2 base;
    Vector2 direction;
} Line;

/**
 * 
 */
typedef struct segment {
    Vector2 p1;
    Vector2 p2;
} Segment;

/**
 * Draws a line on the screen using Bresenham’s line algorithm.
 * 
 * @param line Pointer to a `Line` structure. The `base` field is the starting point, and the `direction` field is the endpoint.
 * 
 * @return None.
 * 
 * @note The behavior is undefined if a line is `NULL`.
 */
void Line_draw(const Line* line);

/* ================================================================ */

#endif /* _START_LINE_SHAPE_H */