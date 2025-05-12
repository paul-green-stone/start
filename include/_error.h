#ifndef _START__ERROR_H
#define _START__ERROR_H

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

/** Constructs a formatted error message string
 * that combines the current error message
 * with the name of the function where the error occurred.
 */
#define __construct_error_msg__ \
    char error_msg[256]; \
    snprintf(error_msg, sizeof(error_msg), "%s in %s%s%s (%s:%d)", Error_get_msg(), BYELLOW, Error_get_func(), RESET, __FILE__, __LINE__); \
    Error_set_msg(error_msg)

/* ================================================================ */

#endif /* _START__ERROR_H */
