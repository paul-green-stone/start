#include "../include/Camera.h"
#include "../include/Error.h"

/* ================================================================ */

int Camera_bind(Camera* camera, Vector2* point) {

    /* === Do not dereference `NULL === */
    if ((camera == NULL) || (point == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    camera->obj = point;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Camera_center(Camera* camera) {

    /* === Let's omit the checking for `NULL` === */

    /* === Centering the camera === */
    camera->pos.x = camera->obj->x - (camera->dmns.w / 2);
    camera->pos.y = camera->obj->y - (camera->dmns.h / 2);

    camera->dmns.x = camera->pos.x;
    camera->dmns.y = camera->pos.y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

void Camera_transform(const Camera* camera, float x, float y, float* _x, float* _y) {

    /* === Let's omit the checking for `NULL` === */
    if (_x) { *_x = x - camera->pos.x; }
    if (_y) { *_y = y - camera->pos.y; }
}

/* ================================================================ */
