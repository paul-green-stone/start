#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#include "../../include/Math/Vector2D.h"
#include "../../include/Error.h"
#include "../../include/_error.h"

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Vector2* Vector2_create(float x, float y) {

    Vector2* vector;

    /* ================================ */
    /* === Vector Memory Allocation === */
    /* ================================ */

    vector = NULL;

    if ((vector = calloc(1, sizeof(Vector2))) == NULL) {

        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        Error_set_msg(strerror(errno));

        #ifdef STRICTMODE
            error(stderr, "%s\n", error_msg);
        #endif

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

    if ((v == NULL) && (*v == NULL)) {

        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ================================ */
    /* === Deallocating a Container === */
    /* ================================ */

    free(*v);
    *v = NULL;

    /* ======== */

    return SSUCCESS;
}

/* ================================================================ */

int Vector2_multiply(Vector2* v, Vector2* dst, float s) {

    if (v == NULL) {

        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (dst == NULL) {

        v->x *= s;
        v->y *= s;

        /* ======== */
        return SSUCCESS;
    }

    dst->x = v->x * s;
    dst->y = v->y * s;

    /* ======== */
    return SSUCCESS;

}

/* ================================================================ */

int Vector2_divide(Vector2* v, Vector2* dst, float s) {

    float reciprocal;
    reciprocal = 1.0 / s;

    if (v == NULL) {

        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (dst == NULL) {

        v->x *= reciprocal;
        v->y *= reciprocal;

        /* ======== */
        return SSUCCESS;
    }

    dst->x *= reciprocal;
    dst->y *= reciprocal;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_negate(Vector2* v) {

    if (v == NULL) {
        
        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

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

    if (v == NULL) {
        
        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

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

    if (v == NULL) {
        
        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    magnitude = sqrt(v->x * v->x + v->y * v->y);

    /* ======== */
    return Vector2_divide(v, NULL, magnitude);
}

/* ================================================================ */

int Vector2_add(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    if ((a == NULL) || (b == NULL)) {
        
        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (dst_vector == NULL) {

        /* Addition is commutative */
        b->x += a->x;
        b->y += a->y;

        /* ======== */
        return SSUCCESS;
    }

    dst_vector->x = b->x + a->x;
    dst_vector->y = b->y + a->y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Vector2_subtract(const Vector2* a, Vector2* b, Vector2* dst_vector) {

    if ((a == NULL) || (b == NULL)) {
        
        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        /* ======== */
        return SERR_NULL_POINTER;
    }

    if (dst_vector == NULL) {

        b->x = a->x - b->x;
        b->y = a->y - b->y;

        /* ======== */
        return SSUCCESS;
    }

    dst_vector->x = a->x - b->x;
    dst_vector->y = a->y - b->y;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
