#ifndef _START_PARTICLE_H
#define _START_PARTICLE_H

#ifdef __cplusplus
extern "C" {
#endif
    
#ifdef _MSC_VER
#include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include "Math/Core.h"

/* ================================================================ */

typedef struct particle {
        
    Vector2 position;
    Vector2 velocity;
    float speed;
    
    float size;
    SDL_Color color;
} Particle;

/* ================================ */
    
/**
 *
 */
Particle* Particle_create(float x, float y, float speed, float size, SDL_Color* color);

/**
 *
 */
void Particle_draw(Particle* particle);
    
/**
 *
 */
void Particle_update(Particle* particle);

/* ================================================================ */
    
#ifdef __cplusplus
}
#endif

#endif /* _START_PARTICLE_H */
