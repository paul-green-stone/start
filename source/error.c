#include <errno.h>

#include "../include/Error.h"

/* ================================================================ */
/* ========================= DEFINITIONS ========================== */
/* ================================================================ */

struct _error {

    int error_code;
    char error_string[128];     /* Error description */

    char function_name[64];     /* The name of the function where an error occurred */
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
};

/* ======== */

static struct _error _Error;

/* ================================================================ */

void Error_set(Error error_code) {

    _Error.error_code = error_code;

    strncpy(_Error.error_string, (_Error.error_code == SERR_SYSTEM) ? strerror(errno): error_descriptions[_Error.error_code * -1], 127);
    _Error.error_string[strlen(_Error.error_string)] = '\0';
}

/* ================================================================ */

void Error_set_msg(const char* msg) {
    strncpy(_Error.error_string, msg, 127);
}

/* ================================================================ */

void Error_set_func(const char* name) {
    strncpy(_Error.function_name, name, 63);
}

/* ================================================================ */

const char* Error_get_func(void) {
    return _Error.function_name;
}

/* ================================================================ */

const char* Error_get_msg(void) {
    return _Error.error_string;
}

/* ================================================================ */
