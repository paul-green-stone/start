#ifndef _START_RECTANGLE_SHAPE_H
#define _START_RECTANGLE_SHAPE_H

#include "../Math/Vector2D.h"

/* ================================================================ */

/**
 * 
 */
typedef struct rectangle {

    Vector2 origin;
    Vector2 size;
} Rectangle;

/**
 * 
 */
typedef struct oriented_rectangle {

    Vector2 center;
    Vector2 half_extend;
    float rotation;
} oRectangle;

/* ================================================================ */

#endif /* _START_RECTANGLE_SHAPE_H */