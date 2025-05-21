#ifndef _START_STATE_INTERFACE_H
#define _START_STATE_INTERFACE_H

#include <stdarg.h>

/* ================================================================ */

/**
 * Creates a new state object. The function allocates memory for the state,
 * initializes it with a descriptor,
 * and optionally calls a custom constructor for further setup.
 * 
 * @param state pointer to a `struct state` descriptor
 * @param ... arguments passed to the descriptor's constructor (if defined)
 * 
 * @return Returns a pointer to the initialized state object on success, NULL on failure.
 */
void* State_create(const void* state, ...);

/**
 * Destroys a state object by invoking its descriptor-defined destructor and freeing its memory.
 * 
 * @param state pointer to the state object to destroy
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure.
 */
int State_destroy(void* state);

/**
 * Invokes a state-specific handler function with variadic arguments.
 * his function delegates processing to the handler defined in the state's descriptor,
 * enabling polymorphic behavior for state objects.
 * 
 * @param state pointer to the state object to process
 * @param ... variadic arguments passed to the state's handler
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure.
 */ 
int State_handle(void* state, ...);

/**
 * Calls the update function of a given state object, passing variadic arguments to it.
 * This allows the state to perform time-based or event-driven updates in a polymorphic manner.
 * 
 * @param state pointer to the state object to update
 * @param ... variadic arguments forwarded to the state's update function
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure.
 */
int State_update(void* state, ...);

/* ================================================================ */

#endif /* _START_STATE_INTERFACE_H */
