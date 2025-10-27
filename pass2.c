#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20], symlabel[20];
    int address, symaddr, start = 0, length;

    // Open all necessary files
    FILE *intermediate = fopen("intermediate.txt", "r");
    FILE *optab = fopen("optab.txt", "r");
    FILE *symtab = fopen("symtab.txt", "r");
    FILE *lenfile = fopen("length.txt", "r");

    if (!intermediate || !optab || !symtab || !lenfile) {
        printf("Error: One or more files could not be opened.\n");
        return 1;
    }

    // Read first line (label, opcode, operand)
    fscanf(intermediate, "%s %s %s", label, opcode, operand);
    fscanf(lenfile, "%d", &length);

    // If opcode is START, set start address
    if (strcmp(opcode, "START") == 0)
        start = atoi(operand);
    else
        start = 0;

    // Print Header record
    printf("H^%s^%06X^%06X\n", label, start, length);

    // Read the next line (actual code lines)
    fscanf(intermediate, "%d %s %s %s", &address, label, opcode, operand);

    // Process each line until END is encountered
    while (strcmp(opcode, "END") != 0) {
        int found = 0;

        // Search OPTAB for opcode
        while (fscanf(optab, "%s %s", code, mnemonic) == 2) {
            if (strcmp(opcode, code) == 0) {
                found = 1;

                // Find operand address from SYMTAB
                while (fscanf(symtab, "%s %d", symlabel, &symaddr) == 2) {
                    if (strcmp(operand, symlabel) == 0) {
                        printf("T^%06X^%s%06X\n", address, mnemonic, symaddr);
                        break;
                    }
                }
                break;
            }
        }

        // If opcode is not in OPTAB, handle directives
        if (!found) {
            if (strcmp(opcode, "WORD") == 0)
                printf("T^%06X^%06X\n", address, atoi(operand));
            else if (strcmp(opcode, "BYTE") == 0)
                printf("T^%06X^%s\n", address, operand);
        }

        // ✅ Rewind both tables before next instruction
        rewind(optab);
        rewind(symtab);

        // Read next instruction
        fscanf(intermediate, "%d %s %s %s", &address, label, opcode, operand);
    }

    // Print End record
    printf("E^%06X\n", start);

    // Close files
    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(lenfile);

    return 0;
}