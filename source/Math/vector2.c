#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

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

    /* ====== Do not dereference a NULL pointer ======= */
    if ((v == NULL) && (*v == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Deallocating a Container === */
    free(*v);
    *v = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_multiply(Vector2* v, Vector2* dst, float s) {

    /* ====== Do not dereference a NULL pointer ======= */
    if (v == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    dst = (dst == NULL) ? v : dst;
    dst->x = v->x * s;
    dst->y = v->y * s;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_divide(Vector2* v, Vector2* dst, float s) {

    float reciprocal;
    /* ======== */

    /* ============ Do not divide by zero ============= */
    if (s == 0) {

        Error_set(ERR_DIVIDE_ZERO);
        /* ======== */
        return ERR_DIVIDE_ZERO;
    }

    /* ====== Do not dereference a NULL pointer ======= */
    if (v == NULL) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    reciprocal = 1.0 / s;
    dst = (dst == NULL) ? v : dst;
    dst->x = v->x * reciprocal;
    dst->y = v->y * reciprocal;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_negate(Vector2* v) {

    /* ====== Do not dereference a NULL pointer ====== */
    if (v == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    v->x = -v->x;
    v->y = -v->y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_get_magnitude(const Vector2* v, float* dst) {

    /* ====== Do not dereference a NULL pointer ====== */
    if (v == NULL) {
    
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    *dst = sqrt(v->x * v->x + v->y * v->y);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_normalize(Vector2* v) {

    float magnitude;
    /* ======== */

    /* ====== Do not dereference a NULL pointer ====== */
    if (v == NULL) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    magnitude = sqrt(v->x * v->x + v->y * v->y);

    /* ======== */
    return Vector2_divide(v, NULL, magnitude);
}

/* ================================================================ */

int Vector2_add(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    /* ====== Do not dereference a NULL pointer ====== */
    if ((a == NULL) || (b == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    dst_vector = (dst_vector == NULL) ? b : dst_vector;
    dst_vector->x = b->x + a->x;
    dst_vector->y = b->y + a->y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_subtract(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    /* ====== Do not dereference a NULL pointer ====== */
    if ((a == NULL) || (b == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    dst_vector = (dst_vector == NULL) ? b : dst_vector;
    dst_vector->x = a->x - b->x;
    dst_vector->y = a->y - b->y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
