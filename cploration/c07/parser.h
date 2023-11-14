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

typedef struct c_instruction {
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jump:3;
} c_instruction;

typedef struct a_instruction {
    union {
        hack_addr address;
        char *label;
    } a_instruction_type;
    bool is_addr;
} a_instruction;

typedef struct instruction {
    union {
        a_instruction a_instr;
        c_instruction c_instr;
    };
    enum instruction_types instr_type;
} instruction;

/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

char *extract_label(const char *line, char* label);

bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);
