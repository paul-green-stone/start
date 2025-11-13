#ifndef _START_PARTICLE_CLASS_H
#define _START_PARTICLE_CLASS_H

/**
 * This header defines a "particle class" structure that acts as a blueprint for different types of particles.
 * It uses a table of function pointers to specify how each particle type should be constructed, 
 * destroyed, moved, updated, and drawn. 
 * This design allows for polymorphic behavior—meaning you can create various particle types
 * that share the same interface but have different implementations for each operation.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdlib.h>

/* ================================================================ */

struct particle_class {

    size_t size;

    /* Constructor */
    void* (*ctor)(void* self, va_list* args);
    /* Destructor */
    void* (*dtor)(void* self);

    /* ================================ */

    /* This function governs the particle movement */
    int (*move)(void* self, va_list* args);
    /* This function governs the particle decay */
    int (*update)(void* self, va_list* args);
    /* This function governs the particle drawing */
    int (*draw)(const void* self);
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_PARTICLE_CLASS_H */
