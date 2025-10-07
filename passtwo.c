#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fint, *ftab, *fsym, *flen;
    char label[20], opcode[10], operand[20];
    char opmne[10], op[10];
    char symtab[20], symaddrstr[20];
    int addr, start, len;

    fint = fopen("intermediate.txt", "r");
    ftab = fopen("optab.txt", "r");
    fsym = fopen("symtab.txt", "r");
    flen = fopen("length.txt", "r");

    if (!fint || !ftab || !fsym || !flen) {
        printf("Error opening file(s)\n");
        return 1;
    }

    // Read header line
    fscanf(fint, "%s\t%s\t%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
    } else {
        start = 0;
    }

    fscanf(flen, "%X", &len);

    printf("H^%s^%06X^%06X\n", label, start, len);

    // Process each intermediate line
    while (fscanf(fint, "%X\t%s\t%s\t%s", &addr, label, opcode, operand) == 4) {
        if (strcmp(opcode, "END") == 0)
            break;

        int found = 0;
        rewind(ftab);

        while (fscanf(ftab, "%s\t%s", opmne, op) == 2) {
            if (strcmp(opcode, opmne) == 0) {
                found = 1;
                rewind(fsym);

                int opaddr = 0;
                while (fscanf(fsym, "%s\t%s", symtab, symaddrstr) == 2) {
                    if (strcmp(operand, symtab) == 0) {
                        opaddr = (int)strtol(symaddrstr, NULL, 16);
                        break;
                    }
                }
                printf("T^%08X^%s%08X\n", addr, op, opaddr);
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                printf("T^%08X^%08X\n", addr, atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    printf("T^%08X^", addr);
                    for (int i = 2; operand[i] != '\'' && operand[i] != '\0'; i++)
                        printf("%02X", operand[i]);
                    printf("\n");
                } else if (operand[0] == 'X') {
                    printf("T^%08X^", addr);
                    for (int i = 2; operand[i] != '\'' && operand[i] != '\0'; i++)
                        printf("%c", operand[i]);
                    printf("\n");
                }
            }
        }
    }

    printf("E^%08X\n", start);

    fclose(fint);
    fclose(ftab);
    fclose(fsym);
    fclose(flen);

    return 0;
}