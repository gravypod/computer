#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "ops.h"
#include "convert.h"

int main() {
    char *args[32];

    char *line = NULL;
    size_t lin_len;
    ssize_t len = 0;
    int line_number = -1;
    char memory_location = 0;

    while ((len = getline(&line, &lin_len, stdin)) > 0) {

        // Print out line as comment
        line_number += 1;
        printf("# Line %d> %s\n", line_number, line);

        char *opname = NULL;
        int num_args = 0;
        for (char *token = strtok(line, " \t\n"); token != NULL; token = strtok(NULL, " ,\n")) {
            if (opname)
                args[num_args++] = strdup(token);
            else
                opname = strdup(token);
        }

        if (!opname && !num_args)
            break;

        int op_id = find_opcode_for(opname);

        if (op_id < 0) {
            printf("ERR: Unknown opname %s\n", opname);
            return 1;
        }

        if (opcodes[op_id]->num_args != num_args) {
            printf("ERR: Incorrect number of args line %d op %s\n", line_number, opname);
            return 1;
        }

        printf("%s\n", make_binary_string_for((unsigned char) op_id));
        memory_location += 1; // We wrote a byte

        // Check type values and print out binary literals as you process
        for (int i = 0; i < num_args; i++) {
            char *binary_value = convert_argument(args[i], (size_t) opcodes[op_id]->args[i]);

            if (!binary_value) {
                printf("Incorrect token type on line %d\n", line_number);
                return 1;
            }

            printf("\t%s\n", binary_value);
            memory_location += 1; // We wrote a byte
        }

        if (memory_location > 256) {
            printf("ERR: Program too large for system memory");
            return 1;
        }
    }
    return 0;
}