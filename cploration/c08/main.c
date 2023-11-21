/****************************************
 * C-ploration 8 for CS 271
 * 
 * [NAME] William Colburn
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[])
{

    if (argc != 2) {
        // if incorrect number of arguments
        printf("Usage: %s [filename]\n", argv[0]);
        exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }

    FILE *fin = fopen( argv[1], "r" );
    if (fin == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    parse(fin);
    fclose(fin);

}


