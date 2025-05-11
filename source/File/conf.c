#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "../../include/Error.h"
#include "../../include/File/conf.h"

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

/* ======== */

/**
 * Function pointer type for retrieving a configuration value
 */
typedef int (*getter)(const config_t*, const char* path, const char* value);

/* ======== */

/**
 * Represents a single entry in a lookup table
 * that maps configuration setting types to their corresponding metadata and retrieval functions
 */
struct lookup_table_type_entry {

    Setting_Value value_type;       /* Value type */
    /* A function pointer to a getter function that retrieves the value  */
    getter getter;
};

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * Looks up a string value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the string value in the configuration
 * 
 * @return `SSUCCESS` if the setting was found and is a string. `SERR_ITEM_NOT_FOUND` if the setting was not found or is not a string.
 */
static int _config_lookup_string(const config_t* config, const char* path, char** value) {

    config_setting_t* settings;
    char* temp;
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_string(config, path, (const char**) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
    }
    else {
        //printf("%s\n", config_setting_get_string(settings));
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

/**
 * A static array of `lookup_table_type_entry` structures
 * that maps setting types to their corresponding string representations
 * and getter functions.
 */
static struct lookup_table_type_entry lookup_table[] = {
    {INT,     (getter) config_lookup_int},
    {INT64,   (getter) config_lookup_int64},
    {FLOAT,   (getter) config_lookup_float},
    {BOOLEAN, (getter) config_lookup_bool},
    {STRING,  (getter) _config_lookup_string},
};

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

int Conf_parse_file(config_t* config, const char* filename) {

    /* Error message buffer */
    char error_msg[256];

    /* ====== Do not dereference a NULL pointer ======= */
    if (config == NULL) {

        /* Constructing the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ===== Try to read and parse the given file ===== */
    if (config_read_file(config, filename) == CONFIG_FALSE) {

        __set_error__(SERR_LIBCONFIG, __func__);

        /* Constructing the error message */
        (errno == ENOENT) ? Error_set_msg(strerror(errno)) : Error_set_msg(Error_get_msg());
        (errno == ENOENT) ? snprintf(error_msg, sizeof(error_msg), "%s - %s", config_error_text(config), Error_get_msg()) : snprintf(error_msg, sizeof(error_msg), "%s on line %d in %s%s%s", config_error_text(config), config_error_line(config), BBLUE, config_error_file(config), RESET);
        Error_set_msg(error_msg);

        #ifdef STRICTMODE
            error(stderr, "%s\n", error_msg);
        #endif

        /* ======== */
        return SERR_LIBCONFIG;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Conf_extract(config_t* config, const char* path, Setting_Value type, void* data) {

    /* ====== Do not dereference a NULL pointer ======= */
    if ((config == NULL) || (path == NULL) || (data == NULL)) {

        /* Constructing and updating the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Prevent access to areas beyond the array === */
    if ((type < INT) || (type > STRING)) {

        /* Constructing and updating the error message */
        __set_error__(SERR_UNKNOWN_TYPE, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_UNKNOWN_TYPE;
    }
    
    /* ============= Extracting the data ============== */
    if ((lookup_table[type].getter(config, path, data)) == SERR_ITEM_NOT_FOUND) {
        
        /* Constructing the error message */
        __set_error__(SERR_ITEM_NOT_FOUND, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Conf_lookup(const config_t* config, const char* path, config_setting_t** setting) {

    /* ====== Do not dereference a NULL pointer ======= */
    if ((config == NULL) || (setting == NULL)) {
        
        /* Constructing and updating the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ======= Looking for a specified setting ======== */
    if ((*setting = config_lookup(config, path)) == NULL) {
        
        /* Constructing the error message */
        __set_error__(SERR_ITEM_NOT_FOUND, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
