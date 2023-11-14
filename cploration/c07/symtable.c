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