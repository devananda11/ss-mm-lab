#include <stdio.h>
#include <string.h>

#define DISK_SIZE 100
#define MAX_NAME_LEN 50
#define MAX_FILES 20

int disk[DISK_SIZE];

struct File {
    char name[MAX_NAME_LEN];
    int indexBlock;
    int dataBlocks[DISK_SIZE];
    int blockCount;
};

int main() {
    struct File files[MAX_FILES];
    int n;

    // Initialize disk
    for (int i = 0; i < DISK_SIZE; i++) disk[i] = 0;

    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int f = 0; f < n; f++) {
        printf("\nEnter file name: ");
        scanf("%s", files[f].name);

        printf("Enter number of data blocks required: ");
        scanf("%d", &files[f].blockCount);

        // Allocate index block
        int indexBlock = -1;
        for (int i = 0; i < DISK_SIZE; i++) {
            if (disk[i] == 0) {
                indexBlock = i;
                disk[i] = 1;
                break;
            }
        }
        if (indexBlock == -1) {
            printf("No free block for index block.\n");
            f--; // retry this file
            continue;
        }
        files[f].indexBlock = indexBlock;

        printf("Enter %d block numbers for data blocks (0-%d):\n", files[f].blockCount, DISK_SIZE-1);
        int success = 1;
        for (int i = 0; i < files[f].blockCount; i++) {
            int blockNum;
            scanf("%d", &blockNum);
            if (blockNum < 0 || blockNum >= DISK_SIZE || disk[blockNum] == 1) {
                printf("Block %d is not free or invalid. Aborting this file.\n", blockNum);
                // Free already allocated blocks for this file
                for (int j = 0; j < i; j++) disk[files[f].dataBlocks[j]] = 0;
                disk[indexBlock] = 0;
                success = 0;
                break;
            }
            files[f].dataBlocks[i] = blockNum;
            disk[blockNum] = 1;
        }
        if (!success) {
            f--; // retry this file
            continue;
        }
        printf("File '%s' allocated.\n", files[f].name);
    }

    // Display allocation info for all files
    printf("\n--- Allocation Table ---\n");
    for (int f = 0; f < n; f++) {
        printf("File: %s\n", files[f].name);
        printf("  Index Block: %d\n", files[f].indexBlock);
        printf("  Data Blocks: ");
        for (int i = 0; i < files[f].blockCount; i++) printf("%d ", files[f].dataBlocks[i]);
        printf("\n");
    }

    printf("\nUsed blocks: ");
    for (int i = 0; i < DISK_SIZE; i++) if (disk[i]) printf("%d ", i);
    printf("\n");

    return 0;
}