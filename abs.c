#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char recordType[2];
    char progName[10];
    char startAddr[10], length[10];
    char line[200], objCode[10];

    fp = fopen("objectcode1.txt", "r");
    if (!fp) {
        printf("Error: objectcode.txt not found.\n");
        exit(0);
    }

    // ---- HEADER RECORD ----
    fscanf(fp, "%s", recordType);
    if (recordType[0] == 'H') {
        fscanf(fp, "%s %s %s", progName, startAddr, length);
        printf("Program name: %s\n", progName);
        printf("Start address: %s\n", startAddr);
        printf("Program length: %s\n\n", length);
    }

    // ---- READ REMAINING LINES ----
    while (fscanf(fp, "%s", recordType) != EOF) {
        if (recordType[0] == 'T') {
            fscanf(fp, "%s %s", startAddr, length);
            printf("Text record starts at address: %s (length: %s)\n", startAddr, length);

            // Read the rest of that line
            fgets(line, sizeof(line), fp);

            // Convert start address to decimal
            int addr = (int)strtol(startAddr, NULL, 16);

            // Split the line into object codes (each separated by space)
            char *token = strtok(line, " \n");
            while (token != NULL) {
                // Print address and object code
                printf("%04X\t%s\n", addr, token);
                addr += (strlen(token) / 2);
                token = strtok(NULL, " \n");
            }
            printf("\n");
        }
        else if (recordType[0] == 'E') {
            fscanf(fp, "%s", startAddr);
            printf("End of program. Execution starts at: %s\n", startAddr);
        }
    }

    fclose(fp);
    return 0;
}