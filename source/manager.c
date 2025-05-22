#include "../include/Manager.h"
#include "../include/Error.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* ================================================================ */
/* ======================= DEFINEs&TYPEDEFs ======================= */
/* ================================================================ */

#define TABLE_SIZE 256
#define CONSTANT 0.6180339887l

#define _hash(key, i) (pjw_hash((key)) + ((i) * multiplicative_hash((key))))

/* ======== */

struct resource_manager {

    void* elements[TABLE_SIZE];             /* The array in which the elements are stored */
    char* keys[TABLE_SIZE];                 /* The array of keys of the elements stored in the table  */

    size_t size;                            /* The number of elements currently in the table */
};

static struct resource_manager Manager;

/* ================================================================ */
/* ===================== AUXILIARY FUNCTIONS ====================== */
/* ================================================================ */

/* @param prime_size the size of the hash table, typically a prime number */

/**
 * Computes a hash value for a given string `key` using the Peter J. Weinberger (PJW) hash algorithm.
 * 
 * @param key a pointer to a null-terminated string to be hashed.
 * 
 * @return The computed hash value, an integer in the range `[0, TABLE_SIZE - 1]`
 */
static size_t pjw_hash(const char* key) {

    size_t hash_coding = 0;
    size_t tmp;
    /* ======== */

    /* ================================================================ */
    /* == Hash the key by performing a number of bit operations on it = */
    /* ================================================================ */

    while (*key != '\0') {

        hash_coding = (hash_coding << 4) + (*key);

        if ((tmp = (hash_coding & 0xf0000000))) {

            hash_coding ^= (tmp >> 24);
            hash_coding ^= tmp;
        }

        key++;
    }

    /* ======== */
    return hash_coding;
}

/* ================================================================ */

/**
 * Computes a hash value for a given null-terminated string key using a multiplicative hashing technique.
 * 
 * @param key a pointer to a null-terminated string to be hashed
 * 
 * @return Returns the computed hash value, an integer in the range [0, TABLE_SIZE - 1]
 */
static size_t multiplicative_hash(const char* key) {

    size_t hash_coding = 0;
    size_t tmp = 0;
    /* ======== */

    while (*key != '\0') {
        tmp = tmp * 31 + (size_t) *key;
        key++;
    }

    hash_coding = floor(TABLE_SIZE * (fmod(tmp * CONSTANT, 1)));

    /* ======== */
    return hash_coding;
}

/* ================================================================ */
/* ==================== FUNCTIONS DEFENITIONS ===================== */
/* ================================================================ */

void* Manager_lookup(const char* key) {

    size_t position = 0;
    size_t i = 0;
    /* ======== */

    for (i = 0; i < TABLE_SIZE; i++) {

        position = _hash(key, i) % TABLE_SIZE;

        if (Manager.elements[position] == NULL) {

            /* Data was not found */
            return NULL;
        }
        else if (strcmp(Manager.keys[position], key) == 0) {

            /* Pass back the data from the table */
            return Manager.elements[position];
        }
    }

    /* ======== */
    return NULL;
}

/* ================================================================ */

int Manager_insert(const char* key, const void* data) {

    size_t position = 0;
    size_t i = 0;
    /* ======== */

    /* Do not exceed the number of positions in the table */
    if (Manager.size == TABLE_SIZE) {
        
        Error_set(SERR_INVALID_RANGE);
        /* ======== */
        return SERR_INVALID_RANGE;
    }

    /* Do nothing if the data is already in the table */
    if (Manager_lookup(key) != NULL) {
        return 1;
    }

    for (i = 0; i < TABLE_SIZE; i++) {

        position = _hash(key, i) % TABLE_SIZE;

        if (Manager.elements[position] == NULL) {

            /*  Insert the data into the table */
            Manager.elements[position] = (void*) data;
            Manager.keys[position] = (char*) key;

            Manager.size++;

            /* ======== */
            return SSUCCESS;
        }
    }

    /* ======== */
    return -1;
}

/* ================================================================ */

void* Manager_remove(const char* key) {

    size_t position;
    size_t i;

    void* data = NULL;
    /* ======== */

    for (i = 0; i < TABLE_SIZE; i++) {

        position = _hash(key, i) % TABLE_SIZE;

        if (Manager.elements[position] == NULL) {

            /* Return that the data was not found */
            break ;
        }
        else if (strcmp(Manager.keys[position], key) == 0) {

            data = Manager.elements[position];

            Manager.elements[position] = (Manager.keys[position] = NULL);
            Manager.size--;

            break ;
        }
    }

    /* ======== */
    return data;
}

/* ================================================================ */

size_t Manager_size(void) {
    return Manager.size;
}

/* ================================================================ */
