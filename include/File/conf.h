#ifndef _START_LIBCONFIG_H
#define _START_LIBCONFIG_H

#include <libconfig.h>

/* ================================================================ */

typedef enum Setting_Value {
    INT,            /* Simple integer */
    INT64,          /* 64-bit integer */
    FLOAT,          /* Floating-Point mumber */
    BOOLEAN,        /* Boolean value, either 0 or 1 */
    STRING          /* String, textual data */
} Setting_Value;

/* ================================================================ */

/**
 * Initializes and parses a configuration file using the `libconfig` library.
 * 
 * @param config a pointer to an initialized `config_t` structure
 * @param filename path to the configuration file to parse
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
int Conf_parse_file(config_t* config, const char* filename);

/**
 * Extracts a configuration value of a specified type from a `libconfig` configuration object at a given path,
 * storing the result in the provided output pointer.
 * 
 * @param config pointer to an initialized libconfig configuration object
 * @param path dot-separated path string specifying the location of the setting within the configuration
 * @param type an enumeration or identifier specifying the expected type of the setting
 * @param data pointer to the memory location where the extracted value will be stored. The caller must ensure this points to a variable of the correct type corresponding to type
 * 
 * @return Returns 0 on success, -1 otherwise.
 */
int Conf_extract(config_t* config, const char* path, Setting_Value type, void* data);

/**
 * Looks up a configuration setting within a libconfig configuration object at the specified path.
 * 
 * @param config pointer to an initialized `libconfig` configuration object
 * @param path a dot-separated string specifying the path to the desired setting
 * @param setting output parameter. On success, set to point to the found configuration setting
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
int Conf_lookup(const config_t* config, const char* path, config_setting_t** setting);

/* ================================================================ */

#endif /* _START_LIBCONFIG_H */
