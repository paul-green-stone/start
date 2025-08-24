#ifndef _START_ERROR_H
#define _START_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Start.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

typedef enum error {

    SSUCCESS = 0,
    SERR_NULL_POINTER = -1,
    SERR_LIBCONFIG = -2,
    SERR_UNKNOWN_TYPE = -3,
    SERR_ITEM_NOT_FOUND = -4,
    SERR_INVALID_RANGE = -5,
    SERR_SYSTEM = -6,
    SERR_SDL = -7,
    SERR_NOT_IMPLEMENTED = -8,
    ERR_DIVIDE_ZERO = -9,
} Error;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Sets the error state with the specified error code and corresponding error message.
 * 
 * @param error_code the error code to set. If it equals `SERR_SYSTEM`, the system error message is used
 * 
 * @return None.
 */
void Error_set(Error error_code);

/**
 * Retrieves the current error message string.
 * 
 * @return None.
 */
const char* Error_string(void);

/**
 * Sets the error message string to a custom user-provided string.
 * 
 * @param string a pointer to a null-terminated string containing the custom error message
 * 
 * @return None.
 */
void Error_set_string(const char* string);

/* ================================================================ */

#ifdef __cplusplus
}
#endif

#endif /* _START_ERROR_H */
