#ifndef _START_CORE_H
#define _START_CORE_H

#include <SDL2/SDL.h>

#define DEFAULT_CONFIGURATION_DIRECTORY "configs"

/**
 * Represents an entry in a lookup table for mapping
 */
struct lookup_table_entry {

    char* str_value;     /* pointer to a string that represents the flag name */
    int int_value;       /* integer that represents the corresponding value associated with the string */
};

/* ================================================================ */

/**
 * 
 */
int Start(void);

/**
 * 
 */
int Stop(void);

/* ================================================================ */
/* ======================== Miscellaneous ========================= */
/* ================================================================ */

/**
 * Searches a lookup table for a given string key (flag) and returns the associated integer value if found.
 * 
 * @param table pointer to the first element of an array of `lookup_table_entry` structures
 * @param table_size the number of entries in the lookup table
 * @param flag the string key to search for in the table
 * 
 * @return Returns the integer value associated with the matching key if found. 0 if the key is NULL or not found in the table
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
int directory_exist(const char* path);

/**
 * Creates a new directory at the specified filesystem path if it does not already exist.
 * 
 * @param path a null-terminated string specifying the directory path to create
 * 
 * @return None.
 */
void directory_new(const char* path);

/* ================================================================ */

#endif /* _START_CORE_H */
