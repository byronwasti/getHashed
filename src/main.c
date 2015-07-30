#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

int main( int argc, char **argv ) {
    dict_t *table = createDict(5);
    if( table == NULL){
        fprintf(stderr, "Could not create dictionary, exiting.\n");
        return -1;
    }
    char *k00 = "bb", *k01 = "hello", *k02 = "b";
    char *d00 = "d1", *d01 = "d2", *d02 = "d3";
    char *k10 = "f", *k11 = "k", *k12 = "a";
    char *d10 = "d4", *d11 = "d5", *d12 = "d6";
    char *k20 = "i", *k21 = "d";
    char *d20 = "d7", *d21 = "d8";

    // Add everything to dictionary
    printf("Adding everything to dictionary\n");
    dictPut(table, k00, d00);
    dictPut(table, k01, d01);
    dictPut(table, k02, d02);
    dictPut(table, k10, d10);
    dictPut(table, k11, d11);
    dictPut(table, k12, d12);
    dictPut(table, k20, d20);
    dictPut(table, k21, d21);
    printf("0 %s: %s\n", k00,(char*)dictGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)dictGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)dictGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)dictGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)dictGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)dictGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)dictGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)dictGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Delete some keys from start, middle, end
    printf("Delete keys from start, middle, end\n");
    dictDeleteKey(table, k00);
    dictDeleteKey(table, k11);
    dictDeleteKey(table, k21);
    printf("0 %s: %s\n", k00,(char*)dictGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)dictGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)dictGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)dictGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)dictGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)dictGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)dictGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)dictGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Put a key back
    dictPut(table, k21, d21);
    printf("Put a key back\n");
    printf("0 %s: %s\n", k00,(char*)dictGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)dictGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)dictGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)dictGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)dictGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)dictGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)dictGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)dictGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Delete all keys from an index
    printf("Delete all keys from an index\n");
    dictDeleteKey(table, k00);
    dictDeleteKey(table, k01);
    dictDeleteKey(table, k02);
    printf("0 %s: %s\n", k00,(char*)dictGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)dictGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)dictGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)dictGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)dictGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)dictGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)dictGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)dictGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Add a key to that index
    printf("Put a key back into that index\n");
    dictPut(table, k02, d02);
    printf("0 %s: %s\n", k00,(char*)dictGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)dictGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)dictGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)dictGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)dictGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)dictGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)dictGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)dictGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    printf("Delete the table\n");
    dictDelete(&table);
    if(table == NULL){
      puts("It is deleted.");
    }

    return 0;
}
