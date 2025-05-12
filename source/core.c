#include <libconfig.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Start.h"
#include "../include/Core.h"
#include "../include/File/conf.h"

#include "../include/Error.h"
#include "../include/_error.h"

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

#define DEFAULT_CONFIGURATION_FILE "system.conf"
#define BUFFER_SIZE 128

/* ======== */

/**
 * Concatenates the default configuration directory path and filename into the provided buffer
 */
#define combine(buffer) \
    memset(buffer, '\0', sizeof(buffer)); \
    strcat((buffer), DEFAULT_CONFIGURATION_DIRECTORY); \
    strcat((buffer), "/"); \
    strcat((buffer), DEFAULT_CONFIGURATION_FILE); \
    (buffer)[strlen((buffer))] = '\0'; \

/* ======== */

/**
 * Encapsulates SDL and SDL_image initialization flags into a single structure
 */
struct flags {

    Uint32 SDL_flags;
    int IMG_flags;
};

/* ================================================================ */
/* ======================== STATIC STORAGE ======================== */
/* ================================================================ */

/**
 * Provides a mapping between string representations of
 * SDL initialization flags and their corresponding integer constants used by `SDL_Init()`.
 */
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

/* ======== */

/**
 * Maps string names of image initialization flags
 * to their corresponding integer constants used by SDL_image's `IMG_Init()` function.
 */
static struct lookup_table_entry IMG_Init__flags[] = {
    {"IMG_INIT_JPG", IMG_INIT_JPG},
    {"IMG_INIT_PNG", IMG_INIT_PNG},
    {"IMG_INIT_TIF", IMG_INIT_TIF},
    {"IMG_INIT_WEBP", IMG_INIT_WEBP},
    {"IMG_INIT_JXL", IMG_INIT_JXL},
    {"IMG_INIT_AVIF", IMG_INIT_AVIF},
};

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/**
 * Creates a default system configuration file containing an array of system initialization flags.
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure.
 */
static int _write_default_system_config_file(void) {

    config_t config;
    config_setting_t* root;
    config_setting_t* system_array;
    config_setting_t* elm;

    char filepath[64];
    /* ======== */

    config_init(&config);

    /* ================================================ */
    /* = Creating an array & populating it with data == */
    /* ================================================ */

    /* There is no need to check for an error because the function is static and cannot be modified from outside */
    root = config_root_setting(&config);
    system_array = config_setting_add(root, "system", CONFIG_TYPE_ARRAY);

    /* Adding data to the array */
    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "SDL_INIT_TIMER");

    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "SDL_INIT_VIDEO");
    /* ======== */

    system_array = config_setting_add(root, "graphics", CONFIG_TYPE_ARRAY);

    /* Adding data to the array */
    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "IMG_INIT_PNG");

    elm = config_setting_add(system_array, NULL, CONFIG_TYPE_STRING);
    config_setting_set_string(elm, "IMG_INIT_TIF");
    /* ======== */

    combine(filepath);
    
    /* ============= Writing to the file ============== */
    if (config_write_file(&config, filepath) == CONFIG_FALSE) {

        config_destroy(&config);

        /* Constructing the error message */
        __set_error__(SERR_LIBCONFIG, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_LIBCONFIG;
    }

    config_destroy(&config);

    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

/**
 * Reads and parses the default system configuration file to extract SDL initialization flags.
 * 
 * @return Returns a bitmask representing the combined SDL initialization flags extracted from the configuration file. Returns a negative error code if an error occurs.
 */
static int _read_default_system_config_file(struct flags* _flags) {

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

    /* ======== Parsing the configuration file ======== */
    if ((status = Conf_parse_file(&config, filepath)) != SSUCCESS) {

        config_destroy(&config);

        /* Constructing the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    /* ================================ */
    /* ============= SDL ============== */
    /* ================================ */

    if ((status = Conf_lookup(&config, "system", &array)) != SSUCCESS) {

        config_destroy(&config);

        /* Constructing the error message */
        __set_error__(status, "Start");
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    len = config_setting_length(array);
    for (i = 0; i < len; i++) {

        status = lookup_table_find(SDL_Init__flags, sizeof(SDL_Init__flags) / sizeof(SDL_Init__flags[0]), config_setting_get_string_elem(array, i), &t);

        if (status != SSUCCESS) {
            warning(stdout, "unknown flag (%s%s%s) is ignored\n", RED, config_setting_get_string_elem(array, i), RESET);

            continue ;
        }

        flags |= (status == SSUCCESS) ? t : 0;
    }

    _flags->SDL_flags = flags;
    flags = 0;

    /* ================================ */
    /* ============= IMG ============== */
    /* ================================ */

    if ((status = Conf_lookup(&config, "graphics", &array)) != SSUCCESS) {

        config_destroy(&config);

        /* Constructing the error message */
        __set_error__(status, "Start");
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    len = config_setting_length(array);
    for (i = 0; i < len; i++) {

        status = lookup_table_find(IMG_Init__flags, sizeof(IMG_Init__flags) / sizeof(IMG_Init__flags[0]), config_setting_get_string_elem(array, i), &t);

        if (status != SSUCCESS) {
            warning(stdout, "unknown flag (%s%s%s) is ignored\n", RED, config_setting_get_string_elem(array, i), RESET);

            continue ;
        }

        flags |= (status == SSUCCESS) ? t : 0;
    }

    _flags->IMG_flags = flags;
    /* ======== */

    config_destroy(&config);

    /* ======== */
    return flags;
}

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

int Start(void) {

    struct flags flags;

    int status;

    char filepath[64];
    /* ======== */

    status = SSUCCESS;
    flags.SDL_flags = flags.IMG_flags = 0;

    combine(filepath);

    /* ======= Trying to create a new directory ======= */
    if (!directory_exists(DEFAULT_CONFIGURATION_DIRECTORY) && (status = directory_new(DEFAULT_CONFIGURATION_DIRECTORY)) < 0) {
        
        /* Constructing the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    /* ==== Trying to create a configuration file ===== */
    if (!file_exists(filepath) && (status = _write_default_system_config_file()) != SSUCCESS) {
        
        /* Constructing the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    /* ==== Trying to read the configuration file ===== */
    if ((status = _read_default_system_config_file(&flags)) < 0) {

        /* Constructing the error message */
        __set_error__(status, __func__);
        __construct_error_msg__;

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return status;
    }

    /* ============== Initializaing SDL =============== */
    if (SDL_Init(flags.SDL_flags) != 0) {
        
        /* Constructing the error message */
        __set_error__(SERR_SDL, __func__);
        __construct_error_msg__;

        Error_set_msg(SDL_GetError());

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_SDL;
    }

    /* ============== Initializaing IMG =============== */
    if (!(IMG_Init(flags.IMG_flags) & flags.IMG_flags)) {
        
        /* Constructing the error message */
        __set_error__(SERR_SDL, __func__);
        __construct_error_msg__;

        Error_set_msg(SDL_GetError());

        #ifdef STRICTMODE
            error(stderr, "%s\n", Error_get_msg());
        #endif

        /* ======== */
        return SERR_SDL;
    }
    
    /* ======== */
    return SSUCCESS;
}

/* ================================================================ */

int Stop(void) {
    
    IMG_Quit();
    SDL_Quit();

    /* ======== */
    return SUCCESS;
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
    char* prefix = NULL;

    size_t bytes_written;

    va_list args;
    /* ======== */

    va_start(args, format);

    /* Determine the output stream: use `stderr` for ERROR, `stdout` otherwise */
    stream = (!stream) ? ((msg_type == ERROR) ? stderr : stdout) : stream;

    /* Set the message prefix based on the message type */
    switch (msg_type) {

        /* Adjacent string literals are concatenated automatically by the compiler */
        
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
    if (((bytes_written = snprintf(buffer, sizeof(buffer), "%s: ", prefix)) == 0) || (bytes_written >= sizeof(buffer))) {

        fprintf(stream, "%s%s%s: something bad happened while formatting the message\n", RED, "Error", RESET);

        /* ======== */
        return ;
    }

    /* Format the additional message into the buffer and check for errors */
    if ((bytes_written = vsnprintf(buffer + bytes_written, sizeof(buffer) - bytes_written, format, args) == 0) || (bytes_written >= sizeof(buffer) - bytes_written)) {

        fprintf(stream, "%s%s%s: something bad happened while formatting the message\n", RED, "Error", RESET);

        /* ======== */
        return ;
    }

    fprintf(stream, "%s", buffer);
    fflush(stream);

    va_end(args);
}

/* ================================================================ */
