#include "../../../include/Particles/Base/_BaseParticle.h"
#include "../../../include/Particles/_Class.h"
/* Interface */
#include "../../../include/Particles/Particle.h"
#include "../../../include/Math/Core.h"
#include "../../../include/Start.h"


#ifdef _MSC_VER
    #include <SDL.h>
#else
    #include <SDL2/SDL.h>
#endif

#include <stdint.h>
#include <stdbool.h>

/* ================================================================ */

/**
 * 
 */
static void* base_particle_ctor(void* _self, va_list* args) {
    
    struct base_particle* self = _self;
    /* ======== */

    self->position.x = va_arg(*args, double); /* 2 */
    self->position.y = va_arg(*args, double); /* 3 */

    self->velocity.x = va_arg(*args, double); /* 4 */
    self->velocity.y = va_arg(*args, double); /* 5 */

    self->speed = va_arg(*args, double); /* 6 */

    self->is_alive = true;

    self->size = va_arg(*args, int); /* 7 */
    self->color = va_arg(*args, unsigned int); /* 8 */
    self->alpha = va_arg(*args, int); /* 9 */

    /* ======== */
    return self;
}

/**
 * 
 */
int base_particle_move(void* _self, va_list* args) {

    struct base_particle* self = _self;
    /* ======== */

    self->position.x += self->velocity.x * self->speed * get_delta();
    self->position.y += self->velocity.y * self->speed * get_delta();

    /* ======== */
    return SSUCCESS;
}

/**
 * 
 */
int base_particle_update(void* _self, va_list* args) {

    struct base_particle* self = _self;
    /* ======== */

    self->alpha--;

    self->is_alive = (self->alpha <= 0) ? false : true;

    /* ======== */
    return SSUCCESS;
}

/**
 * 
 */
int base_particle_draw(const void* _self) {

    const struct base_particle* self = _self;
    SDL_Rect where2draw = {
        .x = self->position.x,
        .y = self->position.y,
        .w = self->size,
        .h = self->size,
    };
    /* ======== */

    SDL_SetRenderDrawColor(get_context(), (self->color >> 16) & 0xFF, (self->color >> 8) & 0xFF, (self->color >> 0) & 0xFF, self->alpha);
    //SDL_SetRenderDrawColor(get_context(), 255, 0, 0, 255);
    SDL_RenderFillRect(get_context(), &where2draw);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

static const struct particle_class base_particle = {

    .size = sizeof(struct base_particle),

    .ctor = base_particle_ctor,
    .dtor = NULL,

    /* ================================ */

    .move = base_particle_move,
    .update = base_particle_update,
    .draw = base_particle_draw
};

const void* BaseParticle = &base_particle;

/* ================================================================ */
