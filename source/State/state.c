#include <stdlib.h>

#include "../../include/State/_State.h"
#include "../../include/State/State.h"

/* ================================================================ */

void* State_create(const void* _state_descriptor, ...) {

    /* Table of pointers to functions */
    const struct state* state_descriptor;
    void* new_state;
    va_list ap;

    /* ======== */

    state_descriptor = _state_descriptor;
    new_state = NULL;

    if ((new_state = calloc(1, state_descriptor->size)) == NULL) {
        return NULL;
    }

    *(const struct state**) new_state = state_descriptor;

    if (state_descriptor->ctor) {

        va_start(ap, _state_descriptor);
        new_state = state_descriptor->ctor(new_state, &ap);
        va_end(ap);
    }

    /* ======== */

    return new_state;
}

/* ================================================================ */

int State_destroy(void* _state) {

    const struct state* const* state_p = _state;

    if ((_state != NULL) && (*state_p != NULL) && ((*state_p)->dtor != NULL)) {
        _state = (*state_p)->dtor(_state);

        /* ======== */

        return 0;
    }

    free(_state);
    _state = NULL;

    /* ======== */
    
    return -1;
}

/* ================================================================ */

int State_handle(void* state, ...) {

    const struct state* const* state_p = state;
    va_list ap;
    int status = -1;

    if ((state != NULL) && (state_p != NULL) && ((*state_p)->handle != NULL)) {

        va_start(ap, state);
        (*state_p)->handle(state, &ap);
        va_end(ap);

        status = 0;
    }

    /* ======== */

    return status;
}

/* ================================================================ */

int State_update(void* state, ...) {
    
    const struct state* const* state_p = state;
    va_list ap;
    int status = -1;

    if ((state != NULL) && (state_p != NULL) && ((*state_p)->update != NULL)) {

        va_start(ap, state);
        (*state_p)->update(state, &ap);
        va_end(ap);

        status = 0;
    }

    /* ======== */

    return status;
}

/* ================================================================ */
