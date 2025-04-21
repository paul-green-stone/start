#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../include/Math/Vector2D.h"

/* ================================================================ */

Vector2* Vector2_create(float x, float y) {

    Vector2* vector;
    vector = NULL;

    /* ================================ */
    /* === Vector Memory Allocation === */
    /* ================================ */

    if ((vector = calloc(1, sizeof(Vector2))) == NULL) {
        return NULL;
    }

    vector->x = x;
    vector->y = y;

    /* ======== */

    return vector;
}

/* ================================================================ */

int Vector2_destroy(Vector2** v) {

    if ((v == NULL) && (*v == NULL)) {
        return -1;
    }

    /* ================================ */
    /* === Deallocating a Container === */
    /* ================================ */

    free(*v);
    *v = NULL;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_multiply(Vector2* v, Vector2* dst, float s) {

    if (v == NULL) {
        return -1;
    }

    if (dst == NULL) {

        v->x *= s;
        v->y *= s;

        /* ======== */

        return 0;
    }

    dst->x = v->x * s;
    dst->y = v->y * s;

    /* ======== */

    return 0;

}

/* ================================================================ */

int Vector2_divide(Vector2* v, Vector2* dst, float s) {

    float reciprocal;
    reciprocal = 1.0 / s;

    if (v == NULL) {
        return -1;
    }

    if (dst == NULL) {

        v->x *= reciprocal;
        v->y *= reciprocal;

        /* ======== */

        return 0;
    }

    dst->x *= reciprocal;
    dst->y *= reciprocal;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_negate(Vector2* v) {

    if (v == NULL) {
        return -1;
    }

    v->x = -v->x;
    v->y = -v->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_get_magnitude(const Vector2* v, float* dst) {

    if (v == NULL) {
        return -1;
    }

    *dst = sqrt(v->x * v->x + v->y * v->y);

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_normalize(Vector2* v) {

    float magnitude;

    if (v == NULL) {
        return -1;
    }

    magnitude = sqrt(v->x * v->x + v->y * v->y);

    /* ======== */

    return Vector2_divide(v, NULL, magnitude);
}

/* ================================================================ */

int Vector2_add(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    if ((a == NULL) || (b == NULL)) {
        return -1;
    }

    if (dst_vector == NULL) {

        /* Addition is commutative */
        b->x += a->x;
        b->y += a->y;

        /* ======== */

        return 0;
    }

    dst_vector->x = b->x + a->x;
    dst_vector->y = b->y + a->y;

    /* ======== */

    return 0;
}

/* ================================================================ */

int Vector2_subtract(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    if ((a == NULL) || (b == NULL)) {
        return -1;
    }

    if (dst_vector == NULL) {

        b->x = a->x - b->x;
        b->y = a->y - b->y;

        /* ======== */

        return 0;
    }

    dst_vector->x = a->x - b->x;
    dst_vector->y = a->y - b->y;

    /* ======== */

    return 0;
}

/* ================================================================ */
