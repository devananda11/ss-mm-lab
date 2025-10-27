#include <stdio.h>

int findLRU(int time[], int frames) {
    int min = 9999, minIndex = -1;
    for (int i = 0; i < frames; i++) {
        if (time[i] < min) {
            min = time[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {
    int frames, n;

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int memory[frames], time[frames];
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    int pagefault = 0;
    int counter = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            int pos = -1;

            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = findLRU(time, frames); // ✅ Fixed this line
            }

            memory[pos] = pages[i];
            time[pos] = ++counter;
            pagefault++;
        }

        printf("After referencing %d: ", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (memory[j] != -1)
                printf("%d ", memory[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pagefault);
    return 0;
}