#include "../../include/Particles/_Class.h"
/* List of Particles */
#include "../../include/Particles/Particles.h"
/* Interface */
#include "../../include/Particles/Particle.h"
#include "../../include/Particles/Base/_BaseParticle.h"

#include "../../include/Error.h"

/* ================================================================ */

void* Particle_create(const void* _class, ...) {

    const struct particle_class* class = _class;
    void* particle = NULL;

    va_list ap;
    /* ======== */

    if ((particle = calloc(1, class->size)) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    *(const struct particle_class**) particle = class;

    if (class->ctor) {

        va_start(ap, _class);

        if ((particle = class->ctor(particle, &ap)) == NULL) {

            Particle_destroy(particle);
            particle = NULL;
        }

        va_end(ap);
    }

    /* ======== */
    return particle;
}

/* ================================================================ */

int Particle_destroy(void* particle) {

    const struct particle_class** particle_class = particle;
    /* ======== */

    if ((*particle_class)->dtor != NULL) { particle = (*particle_class)->dtor(particle); }

    free(particle);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Particle_move(void* particle, ...) {

    const struct particle_class** particle_class = particle;
    int status = SERR_NOT_IMPLEMENTED;

    va_list ap;
    /*======== */ 

    if ((*particle_class)->move != NULL) {

        va_start(ap, particle);
        
        status = (*particle_class)->move(particle, &ap); 

        va_end(ap);
    }

    /* ======== */
    return status;
}

/* ================================================================ */

int Particle_update(void* particle, ...) {

    const struct particle_class** particle_class = particle;
    int status = SERR_NOT_IMPLEMENTED;

    va_list ap;
    /*======== */ 

    if ((*particle_class)->update != NULL) {

        va_start(ap, particle);
        
        status = (*particle_class)->update(particle, &ap); 

        va_end(ap);
    }

    /* ======== */
    return status;
}

/* ================================================================ */

int Particle_draw(const void* particle) {

    const struct particle_class** particle_class = (void*) particle;
    int status = SERR_NOT_IMPLEMENTED;
    /*======== */ 

    if ((*particle_class)->draw != NULL) { return (status = (*particle_class)->draw(particle)); }

    /* ======== */
    return status;
}

/* ================================================================ */

bool Particle_isAlive(const void* particle) {

    const struct base_particle* base = particle;
    /* ======== */
    
    return base->is_alive;
}

/* ================================================================ */
