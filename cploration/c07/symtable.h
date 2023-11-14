/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] William Colburn
 * [TERM] FALL 2023
 *
 ****************************************/
#include <stdio.h>
#include <string.h>

const int SYMBOL_TABLE_SIZE = 1000;
typedef int16_t hack_addr;
typedef struct Symbol {
    char *name;
    hack_addr addr;
} Symbol;

int hash(char *str);
struct Symbol *symtable_find(char *key);
void symtable_insert(char* key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();