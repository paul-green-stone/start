#include <stdlib.h>

#include "../../include/State/_State.h"
#include "../../include/State/State.h"
#include "../../include/Error.h"
#include "../../include/_error.h"

/* ================================================================ */

void* State_create(const void* _state_descriptor, ...) {
    
    void* new_state = NULL;
    const struct state* state_descriptor = _state_descriptor; /* Table of pointers to functions */

    va_list ap;
    int status = SSUCCESS;
    /* ======== */

    if (_state_descriptor == NULL) {
        
        status = SERR_NULL_POINTER;
        /* ======== */
        goto ERROR;
    }

    if ((new_state = calloc(1, state_descriptor->size)) == NULL) {
        
        status = SERR_SYSTEM;
        /* ======== */
        goto ERROR;
    }

    *(const struct state**) new_state = state_descriptor;

    if (state_descriptor->ctor != NULL) {

        va_start(ap, _state_descriptor);
        new_state = state_descriptor->ctor(new_state, &ap);
        va_end(ap);
    }

    /* ======== */
    return new_state;

    /* ================ */
    ERROR: {

        /* Constructing and updating the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return new_state;
    };
}

/* ================================================================ */

int State_destroy(void* _state) {

    const struct state* const* state_p = _state;
    /* ======== */

    if ((_state != NULL) && (*state_p != NULL)) {
        return SERR_NULL_POINTER;
    }

    if ((*state_p)->dtor != NULL) {
        _state = (*state_p)->dtor(_state);
    }

    free(_state);
    _state = NULL;

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int State_handle(void* state, ...) {

    const struct state* const* state_p = state;
    va_list ap;
    /* ======== */

    if ((state != NULL) && (*state_p != NULL)) {
        return SERR_NULL_POINTER;
    }

    if ((*state_p)->handle != NULL) {

        va_start(ap, state);
        (*state_p)->handle(state, &ap);
        va_end(ap);
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int State_update(void* state, ...) {
    
    const struct state* const* state_p = state;
    va_list ap;
    /* ======== */

    if ((state != NULL) && (state_p != NULL)) {
        return SERR_NULL_POINTER;
    }

    if ((*state_p)->update != NULL) {

        va_start(ap, state);
        (*state_p)->update(state, &ap);
        va_end(ap);
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
