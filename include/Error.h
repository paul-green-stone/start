#ifndef _START_ERROR_H
#define _START_ERROR_H

#include "Start.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

/** Constructs a formatted error message string
 * that combines the current error message
 * with the name of the function where the error occurred.
 */
#define __construct_error_msg__ \
    char error_msg[256]; \
    snprintf(error_msg, sizeof(error_msg), "%s in %s%s%s", Error_get_msg(), BYELLOW, Error_get_func(), RESET); \
    Error_set_msg(error_msg)

#define STRICTMODE

#define __set_error__(error_code, name) \
    Error_set((error_code)); \
    Error_set_func((name));

typedef enum error {
    SSUCCESS = 0,
    SERR_NULL_POINTER = -1,
    SERR_LIBCONFIG = -2,
    SERR_UNKNOWN_TYPE = -3,
    SERR_ITEM_NOT_FOUND = -4,
    SERR_INVALID_RANGE = -5,
    SERR_SYSTEM = -6,
} Error;

/* ================================================================ */

/**
 * 
 */
void Error_set(Error error_code);

/**
 * 
 */
const char* Error_get_msg(void);

/**
 * 
 */
void Error_set_msg(const char* msg);

/**
 * 
 */
void Error_set_func(const char* name);

/**
 * 
 */
const char* Error_get_func(void);


/* ================================================================ */

#endif /* _START_ERROR_H */
