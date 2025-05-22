#include <errno.h>

#include "../include/Error.h"

/* ================================================================ */
/* ========================= DEFINITIONS ========================== */
/* ================================================================ */

struct _error {

    int error_code;
    char error_string[128];     /* Error description */
};

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

static const char* error_descriptions[] = {
    "Success",
    "attempted to dereference a null pointer",
    "libconfig error",
    "type mismatch error",
    "data not found",
    "input value is out of valid range",
    "",     /* reserved for system errors */
    "",     /* resrved for SDL errors */
    "method not implemented",
    "division by zero",
};

/* ======== */

static struct _error _Error;

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

void Error_set(Error error_code) {

    _Error.error_code = error_code;

    strncpy(_Error.error_string, (_Error.error_code == SERR_SYSTEM) ? strerror(errno) : error_descriptions[_Error.error_code * -1], sizeof(_Error.error_string) - 1);
    _Error.error_string[strlen(_Error.error_string)] = '\0';
}

/* ================================================================ */

const char* Error_string(void) {
    return _Error.error_string;
}

/* ================================================================ */

void Error_set_string(const char* string) {
    strncpy(_Error.error_string, string, sizeof(_Error.error_string) - 1);
}

/* ================================================================ */
