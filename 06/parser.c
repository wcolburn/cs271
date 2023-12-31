/****************************************
 * Project 6 for CS 271
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
int parse(FILE * file, instruction *instructions) {

    unsigned int line_num = 0;
    unsigned int instr_num = 0;
    char line[MAX_LINE_LENGTH];
    instruction instr;

    add_predefined_symbols();

    while (fgets(line, sizeof(line), file)) {

        line_num++;
        if (instr_num > MAX_INSTRUCTIONS) {
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
            if (!parse_A_instruction(line, &instr.a_instr)){
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.instr_type = A_Type;
            if (instr.a_instr.is_addr) {
                printf("A: %d\n", instr.a_instr.a_instruction_type.address);
            } else {
                printf("A: %s\n", instr.a_instr.a_instruction_type.label);
            }
        } else if (is_label(line)) {
            inst_type = 'L';
        } else if (is_Ctype(line)) {
            inst_type = 'C';
            char tmp_line[MAX_LINE_LENGTH];
            strcpy(tmp_line, line);
            parse_C_instruction(tmp_line, &instr.c_instr);
            if (instr.c_instr.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            if (instr.c_instr.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }
            if (instr.c_instr.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }
            instr.instr_type = C_Type;
            printf("C: d=%d, c=%d, j=%d\n", instr.c_instr.dest, instr.c_instr.comp, instr.c_instr.jump);
        }
        // printf("%u: %c  %s\n", instr_num, inst_type, line);

        instructions[instr_num++] = instr;
    }
    return instr_num;
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
    char *s = (char *) malloc(strlen(line));
    strcpy(s, line+1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end) {
        instr->a_instruction_type.label = (char *) malloc(strlen(line));
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

void parse_C_instruction(char *line, c_instruction *instr) {
    int a_bit;
    char *dest;

    dest = strtok(line, ";");
    char *jump = strtok(NULL, ";");

    dest = strtok(dest, "=");
    char* comp = strtok(NULL, "=");

    instr->jump = str_to_jumpid(jump);

    if (comp == NULL) {
        instr->comp = str_to_compid(dest, &a_bit);
        instr->dest = str_to_destid(comp);
    } else {
        instr->comp = str_to_compid(comp, &a_bit);
        instr->dest = str_to_destid(dest);
    }

    instr->a = a_bit;
    // printf("%hd\n", instr->comp);
}

void assemble(const char * file_name, instruction* instructions, int num_instructions) {
    int variable_addr = 16;

    char new_name[strlen(file_name) + 6];
    strcpy(new_name, file_name);
    strcat(new_name, ".hack");

    FILE *fout = fopen( new_name, "w" );

    for (int i = 0; i < num_instructions; i++) {
        opcode op = 0;
        // A Type
        if (instructions[i].instr_type == 0) {
            if (instructions[i].a_instr.is_addr) {
                op = instructions[i].a_instr.a_instruction_type.address;
            } else { // Label
                Symbol *label = symtable_find(instructions[i].a_instr.a_instruction_type.label);
                if (label == NULL) {
                    symtable_insert(instructions[i].a_instr.a_instruction_type.label,variable_addr);
                    op = variable_addr;
                    variable_addr++;
                } else {
                    op = label->addr;
                }
                free(instructions[i].a_instr.a_instruction_type.label);
            }
        } else { // C type
            op = instruction_to_opcode(instructions[i].c_instr);
        }
        fprintf(fout, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", OPCODE_TO_BINARY(op));
    }

    fclose(fout);

}

opcode instruction_to_opcode(c_instruction instr) {
    opcode op = 0;
    op |= (7 << 13);
    op |= (instr.a << 12);
    op |= (instr.comp << 6);
    op |= (instr.dest << 3);
    op |= (instr.jump);

    return op;
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
