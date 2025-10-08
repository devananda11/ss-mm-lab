#include <stdio.h>
#include <string.h>

#define DISK_SIZE 100
#define MAX_NAME_LEN 50

int disk[DISK_SIZE];

struct File {
    char name[MAX_NAME_LEN];
    int indexBlock;
    int dataBlocks[DISK_SIZE];
    int blockCount;
};

int main() {
    struct File file;
    // Initialize disk
    for (int i = 0; i < DISK_SIZE; i++) disk[i] = 0;

    printf("Enter file name: ");
    scanf("%s", file.name);

    printf("Enter number of data blocks required: ");
    scanf("%d", &file.blockCount);

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
        return 1;
    }
    file.indexBlock = indexBlock;

    printf("Enter %d block numbers for data blocks (0-%d):\n", file.blockCount, DISK_SIZE-1);
    for (int i = 0; i < file.blockCount; i++) {
        int blockNum;
        scanf("%d", &blockNum);
        if (blockNum < 0 || blockNum >= DISK_SIZE || disk[blockNum] == 1) {
            printf("Block %d is not free or invalid. Aborting.\n", blockNum);
            // Free already allocated blocks
            for (int j = 0; j < i; j++) disk[file.dataBlocks[j]] = 0;
            disk[indexBlock] = 0;
            return 1;
        }
        file.dataBlocks[i] = blockNum;
        disk[blockNum] = 1;
    }

    printf("\nFile '%s' allocated.\n", file.name);
    printf("Index Block: %d\n", file.indexBlock);
    printf("Data Blocks: ");
    for (int i = 0; i < file.blockCount; i++) printf("%d ", file.dataBlocks[i]);
    printf("\n");

    printf("Used blocks: ");
    for (int i = 0; i < DISK_SIZE; i++) if (disk[i]) printf("%d ", i);
    printf("\n");

    return 0;
}