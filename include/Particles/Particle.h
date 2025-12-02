#ifndef _START_PARTICLE_INTERFACE_H
#define _START_PARTICLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "Particles.h"

/* ================================================================ */

/**
 * Creates a new particle instance using the specified type.
 *
 * @param type Pointer to the particle_class defining the particle type.
 * @param ...  Additional arguments passed to the class constructor.
 *
 * @return Pointer to the created particle on success, `NULL` on failure.
 */
void* Particle_create(const void* type, ...);

/**
 * Destroys a particle instance, invoking its destructor if present and freeing memory.
 *
 * If the particle's class has a destructor, it is called before freeing the memory.
 * After destruction, the particle's memory is deallocated.
 *
 * @param particle Pointer to the particle to destroy.
 *
 * @return `SSUCCESS` on successful destruction.
 *
 * @note The function is safe to call with `NULL`, but behavior is undefined if the particle is not valid.
 */
int Particle_destroy(void* particle);

/**
 * Moves a particle by invoking its class-specific move method.
 *
 * @param particle Pointer to the particle to move.
 * @param ...      Additional arguments passed to the move method.
 *
 * @return `SSUCCESS` if the move method was called successfully, ``SERR_NOT_IMPLEMENTED` if not.
 */
int Particle_move(void* particle, ...);

/**
 * Updates a particle by invoking its class-specific update method.
 *
 * @param particle Pointer to the particle to update.
 * @param ...      Additional arguments passed to the update method.
 *
 * @return `SSUCCESS` if the update method was called successfully, `SERR_NOT_IMPLEMENTED` if not.
 */
int Particle_update(void* particle, ...);

/**
 * Draws a particle by invoking its class-specific draw method.
 *
 * @param particle Pointer to the const particle to draw.
 *
* @return `SSUCCESS` if the update method was called successfully, `SERR_NOT_IMPLEMENTED` if not.
 */
int Particle_draw(const void* particle);

/**
 * Checks if a particle is still alive.
 *
 * Returns the value of the `is_alive` flag from the base particle.
 *
 * @param particle Pointer to the const particle to check.
 *
 * @return `true` if the particle is alive, `false` otherwise.
 */
bool Particle_isAlive(const void* particle);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_PARTICLE_INTERFACE_H */