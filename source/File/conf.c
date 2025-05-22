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
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_string(config, path, (const char**) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ======== */

/**
 * Looks up an int value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the int value in the configuration
 * 
 * @return `SSUCCESS` if the setting was found and is an int. `SERR_ITEM_NOT_FOUND` if the setting was not found or is not an int.
 */
static int _config_lookup_int(const config_t* config, const char* path, void* value) {

    config_setting_t* settings;
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_int(config, path, (int*) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ======== */

/**
 * Looks up an int64 value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the int64 value in the configuration
 * 
 * @return `SSUCCESS` if the setting was found and is an int64. `SERR_ITEM_NOT_FOUND` if the setting was not found or is not an int64.
 */
static int _config_lookup_int64(const config_t* config, const char* path, void* value) {

    config_setting_t* settings;
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_int64(config, path, (long long*) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ======== */

/**
 * Looks up a float value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the float value in the configuration
 * 
 * @return `SSUCCESS` if the setting was found and is an float. `SERR_ITEM_NOT_FOUND` if the setting was not found or is not an float.
 */
static int _config_lookup_float(const config_t* config, const char* path, void* value) {

    config_setting_t* settings;
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_float(config, path, (double*) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
    }

    /* ======== */
    return SSUCCESS;
}

/* ======== */

/**
 * Looks up a boolean value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the boolean value in the configuration
 * 
 * @return `SSUCCESS` if the setting was found and is an boolean. `SERR_ITEM_NOT_FOUND` if the setting was not found or is not an boolean.
 */
static int _config_lookup_bool(const config_t* config, const char* path, void* value) {

    config_setting_t* settings;
    /* ======== */

    /* Item not found */
    if (((settings = config_lookup(config, path)) == NULL) || (config_lookup_bool(config, path, (int*) value) == 0)) {
        return SERR_ITEM_NOT_FOUND;
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
    {INT,     (getter) _config_lookup_int},
    {INT64,   (getter) _config_lookup_int64},
    {FLOAT,   (getter) _config_lookup_float},
    {BOOLEAN, (getter) _config_lookup_bool},
    {STRING,  (getter) _config_lookup_string},
};

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

int Conf_parse_file(config_t* config, const char* filename) {

    char error_msg[256]; /* Error message buffer */
    int status = SSUCCESS;
    /* ======== */

    /* ====== Do not dereference a NULL pointer ======= */
    if (config == NULL) {

        status = SERR_NULL_POINTER;
        /* ========= */
        goto ERROR;
    }

    /* ===== Try to read and parse the given file ===== */
    if (config_read_file(config, filename) == CONFIG_FALSE) {

        status = SERR_LIBCONFIG;
        /* ======== */
        goto ERROR;
    }

    /* ======== */
    return SSUCCESS;

    /* ================ */
    ERROR: {

        /* Constructing the error message */
        Error_set(status);

        if (status == SERR_LIBCONFIG) {

            (errno == ENOENT) ? Error_set_string(strerror(errno)) : Error_set(status);
            (errno == ENOENT) ? snprintf(error_msg, sizeof(error_msg), "%s - %s", config_error_text(config), Error_string()) : snprintf(error_msg, sizeof(error_msg), "%s on line %d in %s%s%s", config_error_text(config), config_error_line(config), BBLUE, config_error_file(config), RESET);
            Error_set_string(error_msg);
        }

        /* ======== */
        return status;
    };
}

/* ================================================================ */

int Conf_extract(config_t* config, const char* path, Setting_Value type, void* data) {

    /* ====== Do not dereference a NULL pointer ======= */
    if ((config == NULL) || (path == NULL) || (data == NULL)) {

        Error_set(SERR_NULL_POINTER);
        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* === Prevent access to areas beyond the array === */
    if ((type < INT) || (type > STRING)) {

        Error_set(SERR_UNKNOWN_TYPE);
        /* ======== */
        return SERR_UNKNOWN_TYPE;
    }
    
    /* ============= Extracting the data ============== */
    if ((lookup_table[type].getter(config, path, data)) == SERR_ITEM_NOT_FOUND) {

        Error_set(SERR_ITEM_NOT_FOUND);
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

        Error_set(SERR_NULL_POINTER);
        /* ========== */
        return SERR_NULL_POINTER;
    }

    /* ======= Looking for a specified setting ======== */
    if ((*setting = config_lookup(config, path)) == NULL) {

        Error_set(SERR_LIBCONFIG);
        /* ======== */
        return SERR_LIBCONFIG;
    }

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */
