/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] William Colburn
 * [TERM] FALL 2023
 * 
 ****************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH  200

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        // if incorrect number of arguments
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fin = fopen( argv[1], "r" );
    if (fin == NULL) {
        perror("Unable to open file!");
        exit(EXIT_FAILURE);
    }

    char out_file[strlen(argv[1]) + 1];
    strcpy(out_file, argv[1]);
    strcat(out_file, ".echo");

	return 0;
}
