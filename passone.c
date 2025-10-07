#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char label[20], opcode[20], operand[20];
    char optab_opcode[20], optab_value[20];
    int locctr, start, length;
    FILE *input, *symtab, *optab, *intermediate, *lengthf;

    input = fopen("input.txt", "r");
    symtab = fopen("symtab.txt", "w");
    optab = fopen("optab.txt", "r");
    intermediate = fopen("intermediate.txt", "w");
    lengthf = fopen("length.txt", "w");

    if (!input || !symtab || !optab || !intermediate || !lengthf) {
        printf("Error opening file(s)\n");
        return 1;
    }

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
        locctr = start;
        fprintf(intermediate, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        if (strcmp(label, "~") != 0) {
            fprintf(symtab, "%s\t%04X\n", label, locctr);
        }

        int found = 0;
        rewind(optab);
        while (fscanf(optab, "%s\t%s", optab_opcode, optab_value) == 2) {
            if (strcmp(opcode, optab_opcode) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    locctr += strlen(operand) - 3;
                } else if (operand[0] == 'X') {
                    locctr += (strlen(operand) - 3) / 2;
                } else {
                    locctr += 1;
                }
            }
        }

        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;
    fprintf(lengthf, "%04X", length);

    fclose(input);
    fclose(symtab);
    fclose(optab);
    fclose(intermediate);
    fclose(lengthf);

    printf("Pass 1 completed successfully. Program length: %X\n", length);
    return 0;
}
