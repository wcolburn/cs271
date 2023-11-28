/****************************************
 * C-ploration 8 for CS 271
 *
 * [NAME] William Colburn
 * [TERM] FALL 2023
 *
 ****************************************/
#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *string) {
    unsigned long hash = 5381;
    int c;

    while ((c = *string++)) {
        hash = ((hash << 5) + hash) + c;
    }
    hash = hash % SYMBOL_TABLE_SIZE;
    return hash;
}

// Code from https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm
void symtable_insert(char *key, hack_addr addr) {
    Symbol *item = (Symbol*) malloc(sizeof(Symbol));
    item->name = strdup(key);
    item->addr = addr;

    int hashIndex = hash(key);

    while (hashArray[hashIndex] != NULL) {
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }

    hashArray[hashIndex] = item;
}

Symbol *symtable_find(char *key) {
    int hashIndex = hash(key);

    while (hashArray[hashIndex]  != NULL) {
        if (strcmp(hashArray[hashIndex]->name, key) == 0) {
            return hashArray[hashIndex];
        }
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

void symtable_display_table() {
    int i = 0;
    for (i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL) {
            printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->addr);
        }
        else {
            printf(" ~~ ");
        }
    }
    printf("\n");
}

void symtable_print_labels() {
    int i = 0;
    for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
            printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
    }
}