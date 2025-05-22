#ifndef _START_ERROR_H
#define _START_ERROR_H

#include "Start.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

#define STRICTMODE

#define __set_error__(error_code, name) \
    Error_set((error_code)); \
    Error_set_func((name));

#define FAILURE -1

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
 * 
 */
void Error_set(Error error_code);

/**
 * 
 */
const char* Error_string(void);

/**
 * 
 */
void Error_set_string(const char* string);

/* ================================================================ */

#endif /* _START_ERROR_H */
