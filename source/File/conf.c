#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include "../../include/File/conf.h"

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * Function pointer type for retrieving a configuration value.
 */
typedef int (*getter)(const config_t*, const char* path, const char* value);

/**
 * Looks up a string value in a `libconfig` configuration object at the given `path`.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path a dot-separated path string specifying the setting to look up
 * @param value output parameter. On success, set to point to the string value in the configuration
 * 
 * @return `CONFIG_TRUE` if the setting was found and is a string. `CONFIG_FALSE` if the setting was not found or is not a string.
 */
static int _config_lookup_string(const config_t* config, const char* path, char** value) {

    config_setting_t* settings;

    if ((settings = config_lookup(config, path)) == NULL) {
        return CONFIG_FALSE;
    }

    *value = (char*) config_setting_get_string(settings);

    /* ======== */

    return CONFIG_TRUE;
}

/**
 * Represents a single entry in a lookup table
 * that maps configuration setting types to their corresponding metadata and retrieval functions
 */
struct lookup_table_configuration_entry {

    Setting_Value value_type;       /* Value type */
    const char* str_value_type;     /* A string representation of the value type */

    /* A function pointer to a getter function that retrieves the value  */
    getter getter;
};

/* ================================ */

/**
 * A static array of `lookup_table_configuration_entry` structures that maps configuration setting types to their corresponding string representations and getter functions.
 */
static struct lookup_table_configuration_entry lookup_table[] = {
    {INT,     "INTEGER",   (getter) config_lookup_int},
    {INT64,   "INTEGER64", (getter) config_lookup_int64},
    {FLOAT,   "FLOAT",     (getter) config_lookup_float},
    {BOOLEAN, "BOOLEAN",   (getter) config_lookup_bool},
    {STRING,  "STRING",    (getter) _config_lookup_string},
};

/* ================================================================ */

int Conf_parse_file(config_t* config, const char* filename) {

    if ((filename == NULL) || (config == NULL)) {
        return -1;
    }

    /* Initializes the `config_t` structure */
    config_init(config);

    /* Read and parse a configuration from the file */
    if (config_read_file(config, filename) == CONFIG_FALSE) {

        config_destroy(config);

        /* ======== */

        return -2;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int Conf_extract(config_t* config, const char* path, Setting_Value type, void* data) {

    if ((config == NULL) || (path == NULL) || (data == NULL)) {
        return -1;
    }

    if ((type < INT) || (type > STRING)) {
        return -2;
    }

    if ((lookup_table[type].getter(config, path, data)) == CONFIG_FALSE) {
        return -1;
    }

    /* ======== */

    return 0;
}

/* ================================================================ */

int directory_exist(const char* path) {

    struct stat info;

    /* ======== */

    return (stat(path, &info) == 0 && S_ISDIR(info.st_mode));
}

/* ================================================================ */

void directory_new(const char* path) {

    struct stat st;

    /* ======== */

    memset(&st, 0, sizeof(st));

    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

/* ================================================================ */
