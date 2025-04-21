#ifndef _START_VECTOR2D_H
#define _START_VECTOR2D_H

#include <math.h>

/* ================================================================ */

struct vector2 {

    float x;
    float y;
};

typedef struct vector2 Vector2;

/* ================================================================ */

#define v2_mul(a, b, s) Vector2_multiply((a), (b), (s))
#define v2_div(a, b, s) Vector2_divide((a), (b), (s))
#define v2_neg(a) Vector2_negate(a)
#define v2_mag(a, dst) Vector2_get_magnitude((a), (dst))
#define v2_nrm(a) Vector2_normalize((a))

/* ================================================================ */

/**
 * Dynamically create a new vector with the given components.
 * 
 * @param x x component
 * @param y y component
 * 
 * @return Returns the `Vector2` or NULL on failure.
 */
Vector2* Vector2_create(float x, float y);

/**
 * Destroy a dynamically allocated vector.
 * 
 * @param vector_ptr the address of a dynamically allocated vector
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_destroy(Vector2** vector_ptr);

/**
 * Multiply a vector by a scalar.
 * 
 * @param vector the vector to multiply
 * @param dst_vector the vector in which to store the result
 * @param scalar the scalar value to multiply by
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_multiply(Vector2* vector, Vector2* dst_vector, float scalar);

/**
 * Divide a vector by a scalar.
 * 
 * @param vector the vector to divide
 * @param dst_vector the vector in which to store the result
 * @param scalar the scalar value to divide by
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_divide(Vector2* vector, Vector2* dst_vector, float scalar);

/**
 * Negate a vector.
 * 
 * @param vector the vector to negate
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_negate(Vector2* vector);

/**
 * Get the magnitude of the vector.
 * 
 * @param vector the vector whose magnitude is to be found
 * @param dst the variable in which to store the result
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_get_magnitude(const Vector2* vector, float* dst);

/**
 * Normalize the given vector.
 * 
 * @param vector the vector to normalize
 * 
 * @return 0 on success or a negative error code on failure.
 */
int Vector2_normalize(Vector2* vector);

/* ================================================================ */

#endif /* _START_VECTOR2D_H */
