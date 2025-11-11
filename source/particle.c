#include "../include/Particle.h"
#include "../include/Error.h"

/* ================================================================ */

Particle* Particle_create(float x, float y, float speed, float size, SDL_Color* color) {
    
    Particle* p = NULL;
    /* ======== */
    
    if ((p = calloc(1, sizeof(struct particle))) == NULL) {
        
        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }
    
    p->position.x = x;
    p->position.y = y;
    p->velocity.x = rand_float(-1.0f, 1.0f);
    p->velocity.y = rand_float(-1.0f, 1.0f);
    p->speed = speed;
    
    v2_nrm(&p->velocity);
    
    p->size = size;
    p->color = *color;
    
    /* ======== */
    return p;
}

void Particle_draw(Particle* p) {
    
    SDL_Rect where = {p->position.x, p->position.y, p->size, p->size};
    
    SDL_SetRenderDrawColor(get_context(), p->color.r, p->color.g, p->color.b, p->color.a);
    SDL_RenderFillRect(get_context(), &where);
}

void Particle_update(Particle* p) {
    
    p->position.x += p->velocity.x * p->speed * get_delta();
    p->position.y += p->velocity.y * p->speed * get_delta();
}

/* ================================================================ */
