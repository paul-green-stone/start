#ifndef _START_CORE_H
#define _START_CORE_H

#include <SDL2/SDL.h>

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

/* Defines the default directory name where configuration files are stored */
#define DEFAULT_CONFIGURATION_DIRECTORY "configs"

/* Defines symbolic names for different types of messages used in logging or user output */
typedef enum {ERROR, INFO, SUCCESS} Message_Type;

/**
 * Represents an entry in a lookup table for mapping
 */
struct lookup_table_entry {

    char* str_value;     /* pointer to a string that represents the flag name */
    int int_value;       /* integer that represents the corresponding value associated with the string */
};

/**
 * A shorthand for generating a message that indicates a failed operation.
 */
#define error(stream, format, ...) print_message((stream), ERROR, (format), __VA_ARGS__)

/**
 * This function serves as a shorthand method to generate and display warning messages.
 */
#define warning(stream, format, ...) print_message((stream), INFO, (format), __VA_ARGS__)

/**
 * This function serves as a shorthand for generating a message that indicates the successful completion of an operation.
 */
#define success(stream, format, ...) print_message((stream), SUCCESS, (format), __VA_ARGS__)

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Initializes the application.
 * 
 * @return None.
 */
int Start(void);

/**
 * Cleans up and shuts down the subsystems by calling their respective quit functions.
 * 
 * @return None.
 */
int Stop(void);

/* ================================================================ */
/* ======================== MISCELLANEOUS ========================= */
/* ================================================================ */

/**
 * Searches a lookup table for a given string key (flag) and returns the associated integer value if found.
 * 
 * @param table pointer to the first element of an array of `lookup_table_entry` structures
 * @param table_size the number of entries in the lookup table
 * @param flag the string key to search for in the table
 * @param dest output parameter where the found integer value is stored
 * 
 * @return Returns `SSUCCESS` on success or a negative error code on failure.
 */
int lookup_table_find(struct lookup_table_entry* table, int table_size, const char* flag, int* dest);

/**
 * Checks whether a file exists and is accessible for reading.
 * 
 * @param filename a null-terminated string specifying the path to the file to check
 * 
 * @return Returns 1 if the file exists and can be opened for reading. 0 if the file does not exist or cannot be opened.
 */
int file_exists(const char* filename);

/**
 * Checks whether a directory exists at the specified filesystem path.
 * 
 * @param path a null-terminated string specifying the path to check
 * 
 * @return Returns 1 if the path exists and is a directory. 0 if the path does not exist or is not a directory.
 */
int directory_exists(const char* path);

/**
 * Creates a new directory at the specified filesystem path if it does not already exist.
 * 
 * @param path a null-terminated string specifying the directory path to create
 * 
 * @return Returns 1 if the directory already exists, 0 if it was created, and a negative error code on failure.
 */
int directory_new(const char* path);

/**
 * Formats and prints a message with a colored prefix to the specified output stream.
 * 
 * @param stream pointer to the output stream where the message will be printed
 * @param msg_type enum indicating the type of message, which determines the prefix and color
 * @param format a `printf`-style format string for the message body
 * @param ... variable arguments corresponding to the format specifiers in `format`
 * 
 * @return None.
 */
void print_message(FILE* stream, Message_Type msg_type, const char* format, ...);

/* ================================================================ */

#endif /* _START_CORE_H */
