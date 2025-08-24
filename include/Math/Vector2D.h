#ifndef _START_VECTOR2D_H
#define _START_VECTOR2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct vector2 {

    float x;
    float y;
};

typedef struct vector2 Vector2;

/* ======================================= */
/* Shorthands for common vector operations */
/* ======================================= */

#define v2_mul(a, b, s) Vector2_multiply((a), (b), (s))
#define v2_div(a, b, s) Vector2_divide((a), (b), (s))
#define v2_neg(a) Vector2_negate(a)
#define v2_mag(a, dst) Vector2_get_magnitude((a), (dst))
#define v2_nrm(a) Vector2_normalize((a))

/* ======== */

#define v2_add(a, b, dst) Vector2_add((a), (b), (dst))
#define v2_sub(a, b, dst) Vector2_subtract((a), (b), (dst))

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Dynamically create a new vector with the given components.
 * 
 * @param x x component
 * @param y y component
 * 
 * @return Returns the `Vector2` or `NULL` on failure; call `Error_get()` for more information.
 */
Vector2* Vector2_create(float x, float y);

/**
 * Destroy a dynamically allocated vector.
 * 
 * @param vector_ptr the address of a dynamically allocated vector
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_destroy(Vector2** vector_ptr);

/**
 * Multiply a vector by a scalar.
 * 
 * @param vector the vector to multiply
 * @param dst_vector the vector in which to store the result. If it is `NULL`, the `vector` is updated
 * @param scalar the scalar value to multiply by
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_multiply(Vector2* vector, Vector2* dst_vector, float scalar);

/**
 * Divide a vector by a scalar.
 * 
 * @param vector the vector to divide
 * @param dst_vector the vector in which to store the result. If it is `NULL`, the `vector` is updated
 * @param scalar the scalar value to divide by
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_divide(Vector2* vector, Vector2* dst_vector, float scalar);

/**
 * Negate a vector.
 * 
 * @param vector the vector to negate
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_negate(Vector2* vector);

/**
 * Get the magnitude of the vector.
 * 
 * @param vector the vector whose magnitude is to be found
 * @param dst the variable in which to store the result
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_get_magnitude(const Vector2* vector, float* dst);

/**
 * Normalize the given vector.
 * 
 * @param vector the vector to normalize
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_normalize(Vector2* vector);

/**
 * Add two vectors.
 * 
 * @param a the summand vector 1
 * @param b the summand vector 2
 * @param dst_vector the sum vector. If it is NULL, `b` becomes the vector that stores the sum
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_add(const Vector2* a, Vector2* b, Vector2* dst_vector);

/**
 * Subtract one vector from another.
 * 
 * @param a the minuend vector
 * @param b the subtrahend vector
 * @param dst_vector the difference vector. If it is NULL, `b` becomes the vector that stores the difference
 * 
 * @return Returns `SUCCESS` (0) on success or a negative error code on failure; call `Error_get()` for more information.
 */
int Vector2_subtract(const Vector2* a, Vector2* b, Vector2* dst_vector);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_VECTOR2D_H */
