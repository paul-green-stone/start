#ifndef _START_PARTICLE_INTERFACE_H
#define _START_PARTICLE_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "Particles.h"

/* ================================================================ */

/**
 * 
 */
void* Particle_create(const void* type, ...);

/**
 * 
 */
int Particle_destroy(void* particle);

/**
 * 
 */
int Particle_move(void* particle, ...);

/**
 * 
 */
int Particle_update(void* particle, ...);

/**
 * 
 */
int Particle_draw(const void* particle);

/**
 * 
 */
bool Particle_isAlive(const void* particle);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_PARTICLE_INTERFACE_H */