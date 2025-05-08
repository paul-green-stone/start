#include <libconfig.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/Start.h"
#include "../include/Core.h"
#include "../include/File/conf.h"

#define DEFAULT_CONFIGURATION_FILE "system.conf"

#define combine(buffer) \
    (buffer)[0] = '\0'; \
    strcat((buffer), DEFAULT_CONFIGURATION_DIRECTORY); \
    strcat((buffer), "/"); \
    strcat((buffer), DEFAULT_CONFIGURATION_FILE); \
    (buffer)[strlen((buffer))] = '\0'; \

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

static struct lookup_table_entry SDL_Init__flags[] = {
    {"SDL_INIT_TIMER", SDL_INIT_TIMER},
    {"SDL_INIT_AUDIO", SDL_INIT_AUDIO},
    {"SDL_INIT_VIDEO", SDL_INIT_VIDEO},
    {"SDL_INIT_JOYSTICK", SDL_INIT_JOYSTICK},
    {"SDL_INIT_HAPTIC", SDL_INIT_HAPTIC},
    {"SDL_INIT_GAMECONTROLLER", SDL_INIT_GAMECONTROLLER},
    {"SDL_INIT_EVENTS", SDL_INIT_EVENTS},
    {"SDL_INIT_EVERYTHING", SDL_INIT_EVERYTHING},
    {"SDL_INIT_NOPARACHUTE", SDL_INIT_NOPARACHUTE},
};

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * Creates a default system configuration file containing an array of system initialization flags.
 * 
 * @return Returns 0 on success or a negative error code on failure.
 */
static int _write_default_system_config_file(void) {

    config_t config;
    config_setting_t* root;
    config_setting_t* system_array;
    config_setting_t* elm;

    char filepath[64];
    
    /* ======== */

    config_init(&config);
    root = config_root_setting(&config);
    system_array = config_setting_add(root, "system", CONFIG_TYPE_ARRAY);

    /* ======== */

    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "SDL_INIT_TIMER");

    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "SDL_INIT_VIDEO");

    /* ======== */

    combine(filepath);

    /* Writing to the file */
    if (config_write_file(&config, filepath) == CONFIG_FALSE) {

        config_destroy(&config);

        /* ======== */

        return -2;
    }

    config_destroy(&config);

    /* ======== */

    return 0;
}

/* ================================================================ */

/**
 * Reads and parses the default system configuration file to extract SDL initialization flags.
 * 
 * @return Returns a bitmask representing the combined SDL initialization flags extracted from the configuration file.  Returns 0 if an error occurs.
 */
static int _read_default_system_config_file(void) {

    config_t config;
    config_setting_t* array;

    int status;
    int len, i;
    int t;

    char filepath[64];

    Uint64 flags;

    /* ======== */

    flags = 0;
    
    config_init(&config);

    combine(filepath);

    if ((status = Conf_parse_file(&config, filepath)) != 0) {

        config_destroy(&config);

        /* ======== */

        return status;
    }

    if ((array = config_lookup(&config, "system")) == NULL) {

        config_destroy(&config);

        /* ======== */

        return -2;
    }

    len = config_setting_length(array);
    for (i = 0; i < len; i++) {

        status = lookup_table_find(SDL_Init__flags, sizeof(SDL_Init__flags) / sizeof(SDL_Init__flags[0]), config_setting_get_string_elem(array, i), &t);

        flags |= (status == 0) ? t : 0;
    }

    config_destroy(&config);

    /* ======== */

    return flags;
}

/* ================================================================ */

int Start(void) {

    int flags;
    char filepath[64];

    int status;

    /* ======== */

    combine(filepath);

    if (!directory_exist(DEFAULT_CONFIGURATION_DIRECTORY)) {
        directory_new(DEFAULT_CONFIGURATION_DIRECTORY);
    }

    if (!file_exists(filepath)) {
        
        if (_write_default_system_config_file() < 0) {
            return 0;
        }
    }

    flags = _read_default_system_config_file();

    if ((status = SDL_Init(flags)) != 0) {
        return status;
    }
    
    /* ======== */

    return 0;
}

/* ================================================================ */

int Stop(void) {
    
    SDL_Quit();

    /* ======== */

    return 0;
}

/* ================================================================ */
/* ======================== Miscellaneous ========================= */
/* ================================================================ */

int lookup_table_find(struct lookup_table_entry* table, int table_size, const char* flag, int* dest) {

    int i;

    /* ======== */

    if ((table == NULL) || (flag == NULL) || (dest == NULL)) {
        return -1;
    }

    for (i = 0; i < table_size; i++) {
        if (strcmp((table + i)->str_value, flag) == 0) {

            *dest = (table + i)->int_value;

            /* ======== */
            
            return 0;
        }
    }

    /* ======== */

    return -2;
}

/* ================================================================ */

int file_exists(const char* filename) {

    FILE* file;

    /* ======== */

    if ((file = fopen(filename, "r")) != NULL) {

        fclose(file);

        /* ======== */

        return 1;
    }

    /* ======== */

    /* File does not exist */
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
