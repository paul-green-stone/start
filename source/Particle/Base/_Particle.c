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
 * Constructor for a base particle object.
 *
 * Initializes a `base_particle` struct with provided position, velocity, speed,
 * size, color, and alpha values. The function uses a variadic argument list
 * to set the particle's properties.
 *
 * @param _self Pointer to the base_particle object to initialize.
 * @param args  Pointer to a `va_list` containing the following arguments in order:
 * 
 *              - `double`: x position
 * 
 *              - `double`: y position
 * 
 *              - `double`: x velocity
 * 
 *              - `double`: y velocity
 * 
 *              - `double`: speed
 * 
 *              - `int`: size
 * 
 *              - `unsigned int`: color (typically ARGB or RGBA)
 * 
 *              - `int`: alpha (transparency value)
 *
 * @return Pointer to the initialized `base_particle` object.
 *
 * @note The particle's `is_alive` field is set to true by default.
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
 * Updates the position of a base particle based on its velocity, speed, and delta time.
 *
 * The function modifies the particle's position by applying its velocity vector scaled
 * by its speed and the delta time returned by `get_delta()`.
 *
 * @param _self Pointer to the `base_particle` object to update.
 * @param args  Pointer to a `va_list` (not used in this function).
 *
 * @return `SSUCCESS` on successful update.
 *
 * @note The function does not use the `args` parameter; it only updates the particle's position.
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
 * Updates the state of a base particle for one frame.
 *
 * Decreases the particle's alpha value by 1 and sets its `is_alive` flag based on alpha.
 * If alpha reaches zero or below, the particle is marked as not alive.
 *
 * @param _self Pointer to the `base_particle` object to update.
 * @param args  Pointer to a `va_list` (not used in this function).
 *
 * @return `SSUCCESS` on successful update.
 *
 * @note The function does not use the `args` parameter; it only updates the particle's `alpha` and `is_alive` state.
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
 * Renders a base particle to the screen using SDL.
 *
 * Draws a filled rectangle at the particle's position with its size and color.
 * The alpha value controls the transparency of the rectangle.
 *
 * @param _self Pointer to the const `base_particle` object to draw.
 *
 * @return `SSUCCESS` on successful drawing.
 *
 * @note The function uses `get_context()` to obtain the SDL renderer and extracts RGB components from the color field.
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
