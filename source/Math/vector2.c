#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#include "../../include/Math/Vector2D.h"
#include "../../include/Error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Vector2* Vector2_create(float x, float y) {

    Vector2* vector = NULL;
    /* ======== */

    if ((vector = calloc(1, sizeof(Vector2))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    vector->x = x;
    vector->y = y;

    /* ======== */
    return vector;
}

/* ================================================================ */

int Vector2_destroy(Vector2** v) {

    /* === Deallocating a Container === */
    free(*v);
    *v = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

Vector2 Vector2_negate(const Vector2* v) {

    Vector2 res = {0, 0};
    /* ========= */

    res.x = -v->x;
    res.y = -v->y;

    /* ======== */
    return res;
}

/* ================================================================ */

float Vector2_get_magnitude(const Vector2* v) {
    return sqrt(v->x * v->x + v->y * v->y);
}

/* ================================================================ */

Vector2 Vector2_normalize(const Vector2* v) {
    return Vector2_scale(v, 1 / Vector2_get_magnitude(v));
}

/* ================================================================ */

Vector2 Vector2_add(const Vector2* a, const Vector2* b) {

    Vector2 res = {0, 0};
    /* ======== */

    res.x = a->x + b->x;
    res.y = a->y + b->y;

    /* ======== */
    return res;
}

/* ================================================================ */

Vector2 Vector2_subtract(const Vector2* a, const Vector2* b) {

    Vector2 res = {0, 0};
    /* ======== */

    res.x = a->x - b->x;
    res.y = a->y - b->y;

    /* ======== */
    return res;
}

/* ================================================================ */

Vector2 Vector2_scale(const Vector2* a, float scalar) {

    Vector2 res = {a->x, a->y};
    
    /* ======== */

    res.x *= scalar;
    res.y *= scalar;

    /* ======== */
    return res;
}

/* ================================================================ */

Vector2 Vector2_unscale(const Vector2* a, float scalar) {

    Vector2 res = {a->x, a->y};

    assert(scalar != 0);
    
    /* ======== */

    res.x /= scalar;
    res.y /= scalar;

    /* ======== */
    return res;
}

/* ================================================================ */

Vector2 Vector2_rotate(Vector2* v, float degrees) {

    float rad = deg2rad(degrees);
    float sine = sinf(rad);
    float cosine = cosf(rad);
    
    Vector2 res = {0, 0};
    /* ======== */

    res.x = v->x * cosine - v->y * sine;
    res.y = v->x * sine + v->y * cosine;

    /* ======== */
    return res;
}

/* ================================================================ */

float Vector2_dot_product(const Vector2* a, const Vector2* b) {
    return a->x * b->x + a->y * b->y;
}

/* ================================================================ */
