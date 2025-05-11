#include <libconfig.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>

#include "../include/Start.h"
#include "../include/Core.h"
#include "../include/File/conf.h"

#include "../include/Error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

#define DEFAULT_CONFIGURATION_FILE "system.conf"
#define BUFFER_SIZE 128

#define combine(buffer) \
    memset(buffer, '\0', sizeof(buffer)); \
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
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

int Start(void) {

    int flags;
    int status;

    char filepath[64];
    /* ======== */

    combine(filepath);

    if (!directory_exists(DEFAULT_CONFIGURATION_DIRECTORY)) {
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
/* ======================== MISCELLANEOUS ========================= */
/* ================================================================ */

int lookup_table_find(struct lookup_table_entry* table, int table_size, const char* flag, int* dest) {

    int i;
    /* ======== */

    /* ====== Do not dereference a NULL pointer ======= */
    if ((table == NULL) || (flag == NULL) || (dest == NULL)) {
        
        /* Constructing and updating the error message */
        __set_error__(SERR_NULL_POINTER, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_NULL_POINTER;
    }

    /* ===== Prevent going past the array borders ===== */
    if ((table_size < 0) || (table_size > USHRT_MAX)) {

        /* Constructing and updating the error message */
        __set_error__(SERR_INVALID_RANGE, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_INVALID_RANGE;
    }

    for (i = 0; i < table_size; i++) {
        if (strcmp((table + i)->str_value, flag) == 0) {

            *dest = (table + i)->int_value;

            /* ======== */
            return SSUCCESS;
        }
    }

    /* ======== */
    return SERR_ITEM_NOT_FOUND;
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

    /* File does not exist */
    return 0;
}

/* ================================================================ */

int directory_exists(const char* path) {

    struct stat info;
    /* ======== */

    memset(&info, 0, sizeof(info));

    /* ======== */
    return ((stat(path, &info) == 0) && (S_ISDIR(info.st_mode)));
}

/* ================================================================ */

int directory_new(const char* path) {

    /* =============== Directory exists =============== */
    if (directory_exists(path) == 1) {
        return 1;
    }
    /* ============= Creating a directory ============= */
    else if ((directory_exists(path) == 0) && (mkdir(path, 0755) == 0)) {
        return SSUCCESS;
    }
    
    /* Constructing and updating the error message */
    __set_error__(SERR_SYSTEM, __func__);
    __construct_error_msg__;

    #ifdef STRICTMODE
        error(stderr, "%s\n", Error_get_msg());
    #endif

    /* ======== */
    return SERR_SYSTEM;
}

/* ================================================================ */

void print_message(FILE* stream, Message_Type msg_type, const char* format, ...) {

    char buffer[BUFFER_SIZE];
    size_t bytes_written;

    va_list args;
    va_start(args, format);

    char* prefix = NULL;

    /* Determine the output stream: use stderr for ERROR, stdout otherwise */
    stream = (!stream) ? ((msg_type == ERROR) ? stderr : stdout) : stream;

    /* Set the message prefix based on the message type */
    switch (msg_type) {

        case ERROR:
            prefix = BRED "Error" RESET;
            break ;

        case INFO:
            prefix = BYELLOW "Info" RESET;
            break ;

        case SUCCESS:
            prefix = BGREEN "Success" RESET;
            break ;
    }

    /* Format the prefix into the buffer and check for errors */
    if (((bytes_written = snprintf(buffer, sizeof(buffer), "%s: ", prefix)) < 0) || (bytes_written >= sizeof(buffer))) {
        fprintf(stream, "%s%s%s: error formatting error message\n", RED, "Error", WHITE);

        return ;
    }

    /* Format the additional message into the buffer and check for errors */
    if ((bytes_written = vsnprintf(buffer + bytes_written, sizeof(buffer) - bytes_written, format, args) < 0) || (bytes_written >= sizeof(buffer) - bytes_written)) {
        fprintf(stream, "%s%s%s: error formatting error message\n", RED, "Error", WHITE);

        return ;
    }

    fprintf(stream, "%s", buffer);
    fflush(stream);

    va_end(args);
}

/* ================================================================ */
