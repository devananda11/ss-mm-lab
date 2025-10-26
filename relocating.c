#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert hex bitmask to binary string
void convert(char h[12])
{
    int i, l;
    strcpy(bit, "");        // Clear the bit string
    l = strlen(h);

    // For each hex digit, append its binary equivalent to bit string
    for (i = 0; i < l; i++)
    {
        switch (h[i])
        {
            case '0': strcat(bit, "0");    break;
            case '1': strcat(bit, "1");    break;
            case '2': strcat(bit, "10");   break;
            case '3': strcat(bit, "11");   break;
            case '4': strcat(bit, "100");  break;
            case '5': strcat(bit, "101");  break;
            case '6': strcat(bit, "110");  break;
            case '7': strcat(bit, "111");  break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
            default:  break;
        }
    }
}

char bitmask[12];          // Stores the bitmask from the text record
char bit[12] = {0};        // Stores the binary string after conversion

void main()
{
    char add[6], length[10], input[10], binary[12], relocbit, ch, pn[5];
    int start, inp, len, i, address, opcode, addr, actualadd, tlen;
    FILE *fp1, *fp2;

    // Prompt user for the actual starting address for relocation
    printf("\nEnter the actual starting address : ");
    scanf("%x", &start);

    // Open input and output files
    fp1 = fopen("RLIN.txt", "r");
    fp2 = fopen("RLOUT.txt", "w");

    // Read the first record type (H/T/E)
    fscanf(fp1, "%s", input);

    // Print header to output file
    fprintf(fp2, " ----------------------------\n");
    fprintf(fp2, " ADDRESS\tCONTENT\n");
    fprintf(fp2, " ----------------------------\n");

    // Process records until end record is found
    while (strcmp(input, "E") != 0)
    {
        // If header record, read and skip program name, address, and length
        if (strcmp(input, "H") == 0)
        {
            fscanf(fp1, "%s", pn);      // Program name
            fscanf(fp1, "%s", add);     // Program starting address
            fscanf(fp1, "%s", length);  // Program length
            fscanf(fp1, "%s", input);   // Read next record type
        }

        // If text record, process relocation
        if (strcmp(input, "T") == 0)
        {
            fscanf(fp1, "%x", &address);    // Read starting address of text record
            fscanf(fp1, "%x", &tlen);       // Read length of text record
            fscanf(fp1, "%s", bitmask);     // Read relocation bitmask

            address += start;               // Relocate the starting address
            convert(bitmask);               // Convert bitmask to binary string

            len = strlen(bit);              // Number of bits (instructions) in bitmask
            if (len >= 11)
                len = 10;                   // Limit to 10 instructions

            // For each instruction in the text record
            for (i = 0; i < len; i++)
            {
                fscanf(fp1, "%x", &opcode); // Read opcode
                fscanf(fp1, "%x", &addr);   // Read address/operand

                relocbit = bit[i];          // Get corresponding bit from bitmask
                if (relocbit == '0')
                    actualadd = addr;       // If bit is 0, address is absolute
                else
                    actualadd = addr + start; // If bit is 1, relocate address

                // Write relocated instruction to output file
                fprintf(fp2, "\n %x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;               // Move to next instruction address (assuming 3 bytes per instruction)
            }

            fscanf(fp1, "%s", input);       // Read next record type
        }
    }

    // Print footer to output file
    fprintf(fp2, " ----------------------------\n");

    // Close files
    fclose(fp2);
    fclose(fp1);

    printf("Successfully implemented relocating loader.\n");
}

