#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_SIZE 100
#define MAX_NAME_LEN 50
#define MAX_FILES 20

int disk[DISK_SIZE];

struct Block {
    int block_number;
    struct Block* next;
};

struct File {
    char name[MAX_NAME_LEN];
    struct Block* head;
};

int main() {
    // Initialize disk
    for (int i = 0; i < DISK_SIZE; i++) disk[i] = 0;

    struct File files[MAX_FILES];
    int n;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int f = 0; f < n; f++) {
        printf("\nEnter file name: ");
        scanf("%s", files[f].name);

        int num_blocks;
        printf("Enter number of blocks for '%s': ", files[f].name);
        scanf("%d", &num_blocks);

        struct Block* head = NULL;
        struct Block* current = NULL;

        printf("Enter %d block numbers:\n", num_blocks);
        int success = 1;
        for (int i = 0; i < num_blocks; i++) {
            int blockNumber;
            scanf("%d", &blockNumber);

            if (blockNumber < 0 || blockNumber >= DISK_SIZE) {
                printf("Block %d is out of range!\n", blockNumber);
                success = 0;
                break;
            }
            if (disk[blockNumber] == 1) {
                printf("Block %d is already allocated!\n", blockNumber);
                success = 0;
                break;
            }

            struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
            newBlock->block_number = blockNumber;
            newBlock->next = NULL;
            disk[blockNumber] = 1;

            if (head == NULL) {
                head = newBlock;
                current = newBlock;
            } else {
                current->next = newBlock;
                current = current->next;
            }
        }

        if (!success) {
            // Cleanup any allocated blocks for this file
            while (head != NULL) {
                struct Block* temp = head;
                disk[head->block_number] = 0;
                head = head->next;
                free(temp);
            }
            printf("File '%s' allocation aborted. Please re-enter.\n", files[f].name);
            f--; // retry this file
            continue;
        }

        files[f].head = head;
        printf("File '%s' allocated successfully.\n", files[f].name);
    }

    // Display allocation info for all files
    printf("\n--- Allocation Table ---\n");
    for (int f = 0; f < n; f++) {
        printf("File: %s\nBlocks: ", files[f].name);
        struct Block* temp = files[f].head;
        while (temp != NULL) {
            printf("%d -> ", temp->block_number);
            temp = temp->next;
        }
        printf("NULL\n");
    }

    printf("\nUsed blocks on disk: ");
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 1) printf("%d ", i);
    }
    printf("\n");

    // Free memory for all files
    for (int f = 0; f < n; f++) {
        struct Block* temp = files[f].head;
        while (temp != NULL) {
            struct Block* next = temp->next;
            free(temp);
            temp = next;
        }
    }

    return 0;
}