/****************************************
 * C-ploration 9 for CS 271
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

    unsigned int line_num = 0;
    unsigned int instr_num = 0;
    char line[MAX_LINE_LENGTH];

    add_predefined_symbols();

    while (fgets(line, sizeof(line), file)) {

        line_num++;
        if (instr_num > MAX_LINE_LENGTH) {
            exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
        }

        strip(line);

        if (!*line) {
            continue;
        }

        char extracted_line[MAX_LINE_LENGTH];
        strcpy(extracted_line, line);
        if (is_label(line)) {

            extract_label(line, extracted_line);
            if (!isalpha(extracted_line[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, extracted_line);
            }

            if (symtable_find(extracted_line) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, extracted_line);
            }

            symtable_insert(extracted_line, instr_num);
            continue;

        }

        char inst_type = '\0';
        if (is_Atype(line)) {
            inst_type = 'A';
        } else if (is_label(line)) {
            inst_type = 'L';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
        }
        printf("%u: %c  %s\n", instr_num, inst_type, line);

        instr_num++;
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

void add_predefined_symbols() {
    for (int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++) {
        predefined_symbol symbol = predefined_symbols[i];
        symtable_insert(symbol.name, symbol.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr) {
    char *s = (char *) malloc(sizeof(line));
    strcpy(s, line+1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (strcmp(s, s_end)) {
        instr->a_instruction_type.label = (char *) malloc(sizeof(line));
        strcpy(instr->a_instruction_type.label, s);
        instr->is_addr = false;
    } else if (*s_end != 0) {
        return false;
    } else {
        instr->a_instruction_type.address = result;
        instr->is_addr = true;
    }
    return true;
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
