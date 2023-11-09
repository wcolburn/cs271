/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] William Colburn
 * [TERM] FALL 2023
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH = MAX_LINE_LENGTH - 2;

typedef int16_t hack_addr;
typedef int16_t opcode;

enum instruction_types {
    Invalid = -1,
    A_Type = 0,
    C_Type = 1
};

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

char *extract_label(const char *line, char* label);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
