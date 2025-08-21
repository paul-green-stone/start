#ifndef _START_CAMERA_H
#define _START_CAMERA_H

#include <SDL2/SDL.h>

#include "Math/Vector2D.h"

/* ================================================================ */

typedef struct camera {

    /* Camera's dimensions */
    SDL_Rect dmns;

    /* Camera's position (top left corner) */
    Vector2 pos;

    /* A point of camera binding */
    Vector2* obj;
} Camera;

/* ================================================================ */

/**
 * Binds a `Camera` object to a specific `Vector2` point.
 * 
 * @param camera pointer to a `Camera` structure that will be bound to the specified point.
 * @param point pointer to a `Vector2` structure representing the position or object to which the camera should be bound.
 * 
 * @return Returns `SSUCCESS` (0) on success, or a negative error code on failure. call `Error_get()` for more information. 
 */
int Camera_bind(Camera* camera, Vector2* point);

/**
 * Centers the camera on its bound object.
 * 
 * @param camera pinter to a `Camera` structure whose position will be centered on its bound object.
 * 
 * @return Returns `SSUCCESS` (0) on success, or a negative error code on failure. call `Error_get()` for more information.
 */
int Camera_center(Camera* camera);

/**
 * Transforms world coordinates (x, y) into camera-relative (screen) coordinates.
 * 
 * @param camera pointer to a constant `Camera` structure representing the camera's current state and position.
 * @param x the world coordinate to be transformed.
 * @param y the world coordinate to be transformed.
 * @param _x output pointers for the transformed coordinates.
 * @param _y output pointers for the transformed coordinates.
 * 
 * @return Returns none.
 */
void Camera_transform(const Camera* camera, float x, float y, float* _x, float* _y);

/* ================================================================ */

#endif /* _START_CAMERA_H */
