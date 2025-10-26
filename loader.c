#include <stdio.h>
#include <string.h>

char input[10], label[10];
int start, length = 0, count = 0, col = 0, memaddr, texaddr;
FILE *fp1, *fp2;

void check() {
    count++;
    memaddr++;
    if (count == 4) {
        fprintf(fp2, " ");
        col++;
        if (col == 4) {
            fprintf(fp2, "\n\n%04X\t\t", memaddr);
            col = 0;
        }
        count = 0;
    }
}

int main() {
    fp1 = fopen("objectcode1.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (!fp1 || !fp2) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(fp1, "%s", input);

    fprintf(fp2, "\t\tAbsolute Loader\n");
    fprintf(fp2, "Address(hex)\t\tContents\n");
    fprintf(fp2, "--------------------------------------\n");

    while (strcmp(input, "E") != 0) {
        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s %x %x %s", label, &start, &length, input);
            memaddr = start;
        } else if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x %x %s", &texaddr, &length, input);
            if (texaddr == start)
                fprintf(fp2, "\n\n%04X\t\t", texaddr);

            fprintf(fp2, "%c%c", input[0], input[1]);
            check();
            fprintf(fp2, "%c%c", input[2], input[3]);
            check();
            fprintf(fp2, "%c%c", input[4], input[5]);
            check();

            fscanf(fp1, "%s", input);
        } else {
            int bytenum = strlen(input);
            if (bytenum == 2) {
                fprintf(fp2, "%c%c", input[0], input[1]);
                check();
                fscanf(fp1, "%s", input);
            } else {
                fprintf(fp2, "%c%c", input[0], input[1]);
                check();
                fprintf(fp2, "%c%c", input[2], input[3]);
                check();
                fprintf(fp2, "%c%c", input[4], input[5]);
                check();
                fscanf(fp1, "%s", input);
            }
        }
    }

    fprintf(fp2, "\n--------------------------------------\n");
    fclose(fp1);
    fclose(fp2);
    return 0;
}

