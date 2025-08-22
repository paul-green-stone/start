#ifndef _START_RESOURCE_MANAGER_H
#define _START_RESOURCE_MANAGER_H

#include <stdio.h>

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * Inserts a key-data pair into the storage.
 * 
 * @param key A null-terminated string representing the key to insert
 * @param data A pointer to the data associated with the key to store in the hash table
 * 
 * @return Returns 0 if inserting the element is successful, 1 if the element is already in the storage, or –1 otherwise.
 */
int Manager_insert(const char* key, const void* data);

/**
 * Removes the key-data pair associated with the given `key` from the storage.
 * 
 * @param key A null-terminated string representing the key to remove
 * 
 * @return Returns pointer to the data associated with the removed key if found and removed. `NULL` if the key was not found in the table.
 */
void* Manager_remove(const char* key);

/**
 * Searches for a data element associated with the given string `key`.
 * 
 * @param key A null-terminated string representing the key to search for in the table
 * 
 * @return Returns a pointer to the data associated with the key if found. Returns `NULL` if the key does not exist in the table.
 */
void* Manager_lookup(const char* key);

/**
 * Returns the current number of elements in the storage.
 * 
 * @return The count of key-data pairs currently stored in the storage.
 */
size_t Manager_size(void);

/* ================================================================ */

#endif /* _START_RESOURCE_MANAGER_H */
