#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"

/* Static function prototypes */
static unsigned long hash(const char *str);
static int removePairs( pair_t *pair );
static pair_t *getPair(pair_t *sweep, const char *key );
static pair_t *createPair(const char *key, void *data);

/* Function definitions */
static unsigned long hash(const char *str)
{
  unsigned long hash = 5381;
  int c;

  while((c = *str++)){
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}


dict_t *createDict(unsigned int size){
  if( size < 1 ){
    fprintf(stderr, "Size of hash table cannot be less than 1!");
    return NULL;
  }

  dict_t *table = malloc(sizeof(dict_t));
  if( table == NULL ){
    fprintf(stderr, "Could not allocate memory for dictionary object\n");
    fprintf(stderr, "TRACEBACK: %s %d\n", __FILE__, __LINE__);
    return NULL;
  }

  table->keys = malloc(sizeof(pair_t) * size);
  if( table->keys == NULL ){
    free(table);
    fprintf(stderr, "Unable to allocate memory for dictionary buckets\n");
    fprintf(stderr, "TRACEBACK: %s %d\n", __FILE__, __LINE__);
    return NULL;
  }

  memset(table->keys, 0, sizeof(pair_t) * size);
  table->size = size;
  table->collisions = 0;

  return table;
}


int dictDelete(dict_t **table){

  for(int i=0; i< (*table)->size; i++){
    if(removePairs((*table)->keys[i]) < 0 ){
      fprintf(stderr, "Error removing keys.\n");
      return -1;
    }
  }

  free((*table)->keys);
  free((*table));
  *table = NULL;

  return 0;
}


static pair_t *createPair(const char *key, void *data){
  pair_t *pair;
  if((pair = malloc(sizeof(pair_t))) == NULL){
    perror("Error");
    return NULL;
  }

  // Allocate memory for the key
  if((pair->key=malloc(strlen(key)+1)) == NULL){
    free(pair);
    perror("Error");
    return NULL;
  }

  strcpy(pair->key, key);
  pair->data = data;
  pair->next = NULL; 

  return pair;
}


static int removePairs( pair_t *pair ){
  if( pair == NULL ){
    return 0;
  }
  if( pair->next == NULL ){
    free(pair->key);
    free(pair);
    return 0;
  }
  else{
    removePairs(pair->next);
    free(pair->key);
    free(pair);
    return 0;
  }
}


static pair_t *getPair(pair_t *sweep, const char *key ){
  if( sweep == NULL){
    return NULL;
  }

  while( sweep != NULL ){
    if(strcmp(sweep->key, key) == 0){
      return sweep;
    }
    else{
      sweep = sweep->next;
    }
  }

  return NULL;
}


int dictPut(dict_t *table, const char *key, void *data){
  unsigned int index;
  pair_t *pair;

  index = hash(key)%table->size;

  // Pair is in the table already
  if((pair=getPair(table->keys[index], key)) != NULL){

    //Update data
    pair->data = data;
    return 2;
  }

  // Index is unique
  if((pair=table->keys[index]) == NULL){

    // Allocate memory for new pair
    if( (pair=createPair(key, data)) == NULL){
      fprintf(stderr,"Error creating pair\n");
      return -1;
    }
    // No previous pair
    pair->previous = NULL; 

    // Store data in table
    table->keys[index] = pair;

    return 0;
  }

  // Non-unique index; append to last element
  while( pair->next != NULL ){
    pair = pair->next;
  }

  // Create new pair for new
  if((pair->next=createPair(key, data)) == NULL){
    fprintf(stderr, "Error creating pair\n");
    return -1;
  }

  // Set previous pair to this one
  pair->next->previous = pair;

  // Keep track of collisions
  table->collisions++;

  return 1;
}


void *dictGet(dict_t *table, const char *key){
  unsigned int index;
  pair_t *pair;

  index = hash(key)%table->size;

  if(( pair=getPair(table->keys[index], key)) != NULL){
    return pair->data;
  }

  return NULL;
}


int dictDeleteKey( dict_t *table, const char *key){
  unsigned int index;
  pair_t *pair;

  index = hash(key)%table->size;

  if((pair=getPair(table->keys[index], key)) == NULL){
    return 1; // No key existed
  }

  /* Check where pair is */
  if(pair->previous == NULL && pair->next == NULL){
    // Only one in list
    table->keys[index] = NULL;
  }else
    if(pair->previous == NULL && pair->next != NULL){
      // First in list
      table->keys[index] = pair->next;
      pair->next->previous = NULL;
      table->collisions--;
    }else
      if(pair->previous != NULL && pair->next != NULL){
        // Middle of list
        pair->previous->next = pair->next;
        pair->next->previous = pair->previous;
        table->collisions--;
      }else
        if(pair->previous != NULL && pair->next == NULL){
          // Last in list
          pair->previous->next = NULL;
          table->collisions--;
        }

  // Next must be null or else it will remove recursively
  pair->next = NULL;
  removePairs(pair);

  return 0;
}

