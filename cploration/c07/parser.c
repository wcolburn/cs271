/****************************************
 * C-ploration 7 for CS 271
 * 
 * [NAME] William Colburn
 * [TERM] FALL 2023
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s) {

    char s_new[MAX_LINE_LENGTH];
    int i = 0;

    for (char *s2 = s; *s2; s2++) {
        if (*s2 == '/' && *(s2+1) == '/') {
            break;
        } else if (!isspace(*s2)) {
            s_new[i++] = *s2;
        }
    }

    s_new[i] = '\0';
    strcpy(s, s_new);

    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){

    char line[MAX_LINE_LENGTH];
    int lineNum = 0;

    while (fgets(line, sizeof(line), file)) {

        strip(line);

        if (!*line) {
            continue;
        }

        char extracted_line[MAX_LINE_LENGTH];
        strcpy(extracted_line, line);
        if (is_label(line)) {
            extract_label(line, extracted_line);
        }

        symtable_insert(extracted_line, lineNum);
        lineNum++;

//        char inst_type = '\0';
//        if (is_Atype(line)) {
//            inst_type = 'A';
//        } else if (is_label(line)) {
//            inst_type = 'L';
//        } else if (is_Ctype(line)) {
//            inst_type = 'C';
//        }

//        printf("%c  %s\n", inst_type, extracted_line);
    }
}

char *extract_label(const char *line, char* label) {
    int label_place_counter = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (i == 0) { // Ignore first parenthesis
            continue;
        } else if (line[i] == ')') { // Ignore end parenthesis
            continue;
        }
        label[label_place_counter] = line[i];
        label_place_counter += 1;
    }

    label[label_place_counter] = '\0';
    return label;
}

bool is_Atype(const char *line) {
    return line[0] == '@';
}

bool is_label(const char *line) {
    return (line[0] == '(' && line[strlen(line)-1] == ')');
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line) && line[0] != '/';
}
