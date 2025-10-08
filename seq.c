#include <stdio.h>
#include <string.h>

#define MAX_BLOCKS 100

struct File {
    char name[20];
    int start;
    int end;
    int length;
};

int main() {
    int disk[MAX_BLOCKS] = {0};
    struct File files[20];
    int fileCount = 0;

    int totalBlocks;
    printf("Enter total number of disk blocks: ");
    scanf("%d", &totalBlocks);

    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    for (int f = 0; f < n; f++) {
        char fname[20];
        int size;
        printf("\nEnter file name: ");
        scanf("%s", fname);
        printf("Enter file size (blocks): ");
        scanf("%d", &size);

      
        int start = -1, count = 0;
        for (int i = 0; i < totalBlocks; i++) {
            if (disk[i] == 0) {
                count++;
                if (count == size) {
                    start = i - size + 1;
                    break;
                }
            } else {
                count = 0;
            }
        }

        if (start == -1) {
            printf("Not enough contiguous space for file %s\n", fname);
        } else {
         
            for (int i = start; i < start + size; i++)
                disk[i] = 1;

            strcpy(files[fileCount].name, fname);
            files[fileCount].start = start;
            files[fileCount].end = start + size - 1;
            files[fileCount].length = size;
            fileCount++;

            printf("File %s allocated from block %d to %d\n", fname, start, start + size - 1);
        }
    }

  
    printf("\nFile Allocation Table:\n");
    printf("Filename\tStart\tEnd\tLength\n");
    for (int i = 0; i < fileCount; i++) {
        printf("%s\t\t%d\t%d\t%d\n",
               files[i].name,
               files[i].start,
               files[i].end,
               files[i].length);
    }

    printf("\nBlock List:\n");
    printf("Block No\tStatus\n");
    for (int i = 0; i < totalBlocks; i++) {
        if (disk[i] == 1)
            printf("%d\t\tOccupied\n", i);
        else
            printf("%d\t\tFree\n", i);
    }

    return 0;
}
