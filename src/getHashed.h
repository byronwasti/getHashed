#ifndef GETHASHED_H
#define GETHASHED_H

/* Pairing struct */
typedef struct pair_s{
    char *key;
    void *data;
    struct pair_s *next;
    struct pair_s *previous;
} pair_t;

/* Dictionary object */
typedef struct ghashed_s{
    unsigned int size;       // Number of indices
    unsigned int collisions; // Number of collisions in indices
    pair_t **keys;           // Keys array
} ghashed_t;


/* Create a dictionary */
/* 
 *   This function creates a dictionary struct, and allocates memory to it.
 *
 * Parameters
 *    size = The size of the dictionary to create, or how many indices 
 *           to give it. Larger value means faster lookup, but more 
 *           memory used.
 *
 * Return
 *    success = Pointer to dictionary memory
 *    failure = NULL pointer
 */
ghashed_t *gh_create(unsigned int size);


/* Put a key-data pair in dictionary*/
/*    
 *    This function puts a key->value pair in the dictionary.
 *    The key must be a string, and the value is a void pointer.
 *    The value is NOT copied, and just points to that data.
 *    Will replace value stored by key if new value is given.
 *
 * Parameters
 *    table = Table object returned by createDict()
 *    key   = String 
 *    data  = Pointer to data
 *
 * Return
 *    Unique Index     = 0
 *    Non-Unique Index = 1
 *    Replaced key     = 2
 *    Failed           = -1
 */
int gh_put(ghashed_t *table, const char *key, void *data);


/* Get the pointer from key */
/*
 *    This is the lookup function. Can be used to get a value,
 *    or check if key is in the dictionary.
 *
 * Parameters
 *    table = Table object returned by createDict()
 *    key   = String
 *
 * Return
 *    Found     = Void pointer to data
 *    Not Found = NULL
 */
void *gh_get(ghashed_t *table, const char *key);


/* Delete a key from the dictionary */
/*
 *    This function will delete a key from the table.
 *    It will NOT remove the data pointed to by the key.
 *
 * Parameters
 *    table = Table object returned by createDict()
 *    key   = String
 *
 * Return
 *    Deleted key  = 0
 *    No Key Found = 1
 */
int gh_delete_key( ghashed_t *table, const char *key);


/* Delete the entire dictionary */
/*
 *    This function will delete a table, and remove
 *    free memory allocated to the table and keys.
 *
 * Parameters
 *    table = Pointer to table object;
 *            ex:   ghashed_t *table;
 *                  table = createDict(10);
 *                  dictDelete( &table );
 *              
 * Return
 *    Success = 0
 *    Failure = -1
 */
int gh_delete(ghashed_t **table);

#endif
