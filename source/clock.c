#include <SDL2/SDL.h>
#include <math.h>

#include "../include/Clock.h"
#include "../include/Error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

struct clock {

    double timer;
    double accumulator;     /* How much time has passed since the the clock was started */
    double modifier;        /* The time modifier */
    double delta;           /* How much time has passed since the clock was last updated */

    int is_stopped;

    Uint64 previous_ticks;
    Uint64 current_ticks;
};

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

Clock* Clock_new(void) {

    Clock* clock = NULL;
    /* ======== */

    /* === Clock Memory Allocation ==== */
    if ((clock = calloc(1, sizeof(Clock))) == NULL) {

        Error_set(SERR_SYSTEM);
        /* ======== */
        return NULL;
    }

    /* The default clock's speed */
    clock->modifier = 1.0f;

    /* ======== */
    return clock;
}

/* ================================================================ */

int Clock_destroy(Clock** clock) {

    /* === Do not dereference a NULL pointer === */
    if ((clock == NULL) || (*clock == NULL)) {
        
        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Deallocating a Container === */
    free(*clock);
    *clock = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

void Clock_start(Clock* clock) {

    clock->is_stopped = 0;
    clock->previous_ticks = SDL_GetPerformanceCounter();
}

/* ================================================================ */

void Clock_stop(Clock* clock) {
    clock->is_stopped = 1;
}

/* ================================================================ */

void Clock_update(Clock* clock) {

    double delta;
    /* ======== */

    if (clock->is_stopped) {
        return ;
    }

    clock->current_ticks = SDL_GetPerformanceCounter();

    delta = (clock->current_ticks - clock->previous_ticks) / (float) SDL_GetPerformanceFrequency();
    
    clock->previous_ticks = clock->current_ticks;
    clock->delta = delta * clock->modifier;
    clock->accumulator += clock->delta;
}

/* ================================================================ */

int Clock_setSpeed(Clock* clock, double speed) {

    if (speed <= 0) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    clock->modifier = speed;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Clock_isReady(const Clock* clock) {
    return clock->accumulator >= clock->timer;
}

/* ================================================================ */

void Clock_reset(Clock* clock) {
    clock->accumulator = 0;
}

/* ================================================================ */

void Clock_setTimer(Clock* clock, double seconds) {
    clock->timer = fabs(seconds);
}

/* ================================================================ */

double Clock_getDelta(const Clock* clock) {
    return clock->delta;
}

/* ================================================================ */
