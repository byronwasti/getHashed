#include <stdlib.h>
#include <stdio.h>
#include "getHashed.h"

int main( int argc, char **argv ) {
    gHash_t *table = gHashNew(5);
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
    gHashPut(table, k00, d00);
    gHashPut(table, k01, d01);
    gHashPut(table, k02, d02);
    gHashPut(table, k10, d10);
    gHashPut(table, k11, d11);
    gHashPut(table, k12, d12);
    gHashPut(table, k20, d20);
    gHashPut(table, k21, d21);
    printf("0 %s: %s\n", k00,(char*)gHashGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)gHashGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)gHashGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)gHashGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)gHashGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)gHashGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)gHashGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)gHashGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Delete some keys from start, middle, end
    printf("Delete keys from start, middle, end\n");
    gHashDeleteKey(table, k00);
    gHashDeleteKey(table, k11);
    gHashDeleteKey(table, k21);
    printf("0 %s: %s\n", k00,(char*)gHashGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)gHashGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)gHashGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)gHashGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)gHashGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)gHashGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)gHashGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)gHashGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Put a key back
    gHashPut(table, k21, d21);
    printf("Put a key back\n");
    printf("0 %s: %s\n", k00,(char*)gHashGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)gHashGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)gHashGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)gHashGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)gHashGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)gHashGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)gHashGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)gHashGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Delete all keys from an index
    printf("Delete all keys from an index\n");
    gHashDeleteKey(table, k00);
    gHashDeleteKey(table, k01);
    gHashDeleteKey(table, k02);
    printf("0 %s: %s\n", k00,(char*)gHashGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)gHashGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)gHashGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)gHashGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)gHashGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)gHashGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)gHashGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)gHashGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    // Add a key to that index
    printf("Put a key back into that index\n");
    gHashPut(table, k02, d02);
    printf("0 %s: %s\n", k00,(char*)gHashGet(table, k00));
    printf("0 %s: %s\n", k01,(char*)gHashGet(table, k01));
    printf("0 %s: %s\n", k02,(char*)gHashGet(table, k02));
    printf("1 %s: %s\n", k10,(char*)gHashGet(table, k10));
    printf("1 %s: %s\n", k11,(char*)gHashGet(table, k11));
    printf("1 %s: %s\n", k12,(char*)gHashGet(table, k12));
    printf("2 %s: %s\n", k20,(char*)gHashGet(table, k20));
    printf("2 %s: %s\n", k21,(char*)gHashGet(table, k21));
    printf("Collisions: %d\n\n", table->collisions);

    printf("Delete the table\n");
    gHashDelete(&table);
    if(table == NULL){
      puts("It is deleted.");
    }

    return 0;
}
