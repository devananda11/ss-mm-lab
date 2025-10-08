#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DISK_SIZE 100
#define MAX_NAME_LEN 50

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

    struct File file;
    printf("Enter file name: ");
    scanf("%s", file.name);

    int num_blocks;
    printf("Enter number of blocks: ");
    scanf("%d", &num_blocks);

    struct Block* head = NULL;
    struct Block* current = NULL;

    printf("Enter %d block numbers:\n", num_blocks);
    for (int i = 0; i < num_blocks; i++) {
        int blockNumber;
        scanf("%d", &blockNumber);

        if (blockNumber < 0 || blockNumber >= DISK_SIZE) {
            printf("Block %d is out of range!\n", blockNumber);
            // Cleanup
            while (head != NULL) {
                struct Block* temp = head;
                disk[head->block_number] = 0;
                head = head->next;
                free(temp);
            }
            return 1;
        }
        if (disk[blockNumber] == 1) {
            printf("Block %d is already allocated!\n", blockNumber);
            // Cleanup
            while (head != NULL) {
                struct Block* temp = head;
                disk[head->block_number] = 0;
                head = head->next;
                free(temp);
            }
            return 1;
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

    file.head = head;

    printf("\nFile '%s' allocated successfully.\nBlocks: ", file.name);
    struct Block* temp = file.head;
    while (temp != NULL) {
        printf("%d -> ", temp->block_number);
        temp = temp->next;
    }
    printf("NULL\n");

    printf("Used blocks on disk: ");
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 1) printf("%d ", i);
    }
    printf("\n");

    // Free memory
    temp = file.head;
    while (temp != NULL) {
        struct Block* next = temp->next;
        free(temp);
        temp = next;
    }

    return 0;
}