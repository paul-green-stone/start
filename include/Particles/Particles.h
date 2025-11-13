#ifndef _START_PARTICLES_H
#define _START_PARTICLES_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================ */

enum ParticleType {
    BASE = 0,
};

/**
 * `Usage: Particle_create(BaseParticle, pos_x, pos_y, vel_x, vel_y, speed, size, color, alpha);`
 * 
 * @param pos_x    Initial x-coordinate of the particle's position.
 * @param pos_y    Initial y-coordinate of the particle's position.
 * @param vel_x    Initial x-component of the particle's velocity.
 * @param vel_y    Initial y-component of the particle's velocity.
 * @param speed    Scalar speed value for the particle.
 * @param size     Visual size of the particle.
 * @param color    Color of the particle in 0xRRGGBB format.
 * @param alpha    Alpha (transparency) value, typically 0-255.
 */
extern const void* BaseParticle;

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_PARTICLE_INTERFACE_H */