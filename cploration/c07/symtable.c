/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] William Colburn
 * [TERM] FALL 2023
 *
 ****************************************/
#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *string) {
    int hash = 5381;
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
    item->name = key;
    item->addr = addr;

    int hashIndex = hash(key);

    while (hashArray[hashIndex] != NULL) {
        ++hashIndex;
        hashIndex %= SYMBOL_TABLE_SIZE;
    }

    hashArray[hashIndex] = item;
}