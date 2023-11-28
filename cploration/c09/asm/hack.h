/****************************************
 * C-ploration 9 for CS 271
 *
 * [NAME] William Colburn
 * [TERM] FALL 2023
 *
 ****************************************/

#ifndef __ERROR_H__
#define __ERROR_H__


#define NUM_PREDEFINED_SYMBOLS 23

enum symbol_id {
    SYM_R0 = 0,
    SYM_R1,
    SYM_R2,
    SYM_R3,
    SYM_R4,
    SYM_R5,
    SYM_R6,
    SYM_R7,
    SYM_R8,
    SYM_R9,
    SYM_R10,
    SYM_R11,
    SYM_R12,
    SYM_R13,
    SYM_R14,
    SYM_R15,
    SYM_SCREEN = 16384,
    SYM_KBD = 24576,
    SP = 0,
    LCL,
    ARG,
    THIS,
    THAT
};

#endif
