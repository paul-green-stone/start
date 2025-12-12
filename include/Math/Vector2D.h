#ifndef _START_VECTOR2D_H
#define _START_VECTOR2D_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>

#include "Core.h"

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

#define v2_mul(a, b) Vector2_multiply((a), (b))
#define v2_div(a, b) Vector2_divide((a), (b))
#define v2_neg(a) Vector2_negate(a)
#define v2_len(a) Vector2_get_magnitude((a))
#define v2_nrm(a) Vector2_normalize((a))
#define v2_scl(a, s) Vector2_scale((a), (s))
#define v2_uscl(a, s) Vector2_unscale((a), (s))

/* ======== */

#define v2_add(a, b, dst) Vector2_add((a), (b))
#define v2_sub(a, b, dst) Vector2_subtract((a), (b))

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
 * Computes the negation of a 2D vector.
 *
 * @param v Pointer to the `Vector2` to negate.
 * 
 * @return A new Vector2 with negated components.
 * 
 * @note The behavior is undefined if `v` is `NULL`.
 */
Vector2 Vector2_negate(const Vector2* vector);

/**
 * Computes the magnitude (length) of a 2D vector.
 *
 * @param v Pointer to the `Vector2` whose magnitude is to be computed.
 * 
 * @return The magnitude of the vector.
 * 
 * @note The behavior is undefined if `v` is `NULL`.
 */
float Vector2_get_magnitude(const Vector2* vector);

/**
 * Normalizes a 2D vector.
 *
 * @param v Pointer to the `Vector2` to normalize.
 * 
 * @return A new `Vector2` with unit length in the same direction as `v`.
 * 
 * @note The behavior is undefined if `v` is `NULL`.
 */
Vector2 Vector2_normalize(const Vector2* vector);

/**
 * Adds two 2D vectors.
 *
 * @param a Pointer to the first `Vector2`.
 * @param b Pointer to the second `Vector2`.
 * 
 * @return A new `Vector2` representing the sum of `a` and `b`.
 * 
 * @note The behavior is undefined if either `a` or `b` is `NULL`.
 */
Vector2 Vector2_add(const Vector2* a, const Vector2* b);

/**
 * Subtracts two 2D vectors.
 *
 * @param a Pointer to the first `Vector2`.
 * @param b Pointer to the second `Vector2`.
 * 
 * @return A new `Vector2` representing the difference of `a` and `b`.
 * 
 * @note The behavior is undefined if either `a` or `b` is `NULL`.
 */
Vector2 Vector2_subtract(const Vector2* a, const Vector2* b);

/**
 * Scales a 2D vector by a scalar value.
 *
 * @param a      Pointer to the `Vector2` to scale.
 * @param scalar The scalar value to multiply the vector by.
 * 
 * @return A new  `Vector2` vector representing the scaled version of the original one
 * 
 * @note The behavior is undefined if `a` is `NULL`.
 */
Vector2 Vector2_scale(const Vector2* a, float scalar);

/**
 * Rotates a vector by the given number of degrees.
 * 
 * @param a Pointer to the `Vector2` to rotate.
 * @param degrees The scalar value to rotate the vector by.
 * 
 * @return A new `Vector2` representing the rotated version of the original one.
 * 
 * @note The behavior is undefined if `a` is `NULL`.
 */
Vector2 Vector2_rotate(Vector2* a, float degrees);

/**
 * Computes the dot product of two 2D vectors.
 * 
 * @param a Pointer to the first `Vector2`.
 * @param b Pointer to the second `Vector2`.
 * 
 * - When the `dot product equals zero` the angle between the vectors is 90°
 * 
 * - When the `dot product is positive` the angle is less than 90°.
 * 
 * - When the `dot product is negative` the angle is greater than 90°.
 * 
 * @return The dot product of two vectors.
 * 
 * @note The behavior is undefined if vectors are `NULL`.
 */
float Vector2_dot_product(const Vector2* a, const Vector2* b);

/**
 * Computes the enclosed angle between two vectors.
 * 
 * @param a Pointer to the first `Vector2`.
 * @param b Pointer to the second `Vector2`.
 * 
 * @return The angle between vectors.
 * 
 * @note The behavior is undefined if vectors are `NULL`.
 */
float Vector2_eAngle(const Vector2* a, const Vector2* b);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_VECTOR2D_H */
