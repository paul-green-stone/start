#ifndef _START_BASE_PARTICEL_H
#define _START_BASE_PARTICEL_H

/* ================================================================ */

/**
 * This class defines a basic particle structure that can be used directly 
 * or serve as a foundation for more specialized particle types. 
 * It contains essential properties such as position, velocity, speed, size, color, and alpha (transparency), 
 * along with a flag to track whether the particle is alive. 
 * The design allows for easy extension, so users can create new particle classes 
 * based on this one by adding or modifying fields as needed.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "../../Math/Core.h"

struct base_particle {

    const void* _class;

    /* ================================ */

    Vector2 position;
    Vector2 velocity;
    float speed;

    bool is_alive;

    float size;
    unsigned int color;
    int alpha;
};

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_BASE_PARTICEL_H */
