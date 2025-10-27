#include <stdio.h>

int main() {
    int frames, pages[50], n, i, j, k, pageFaults = 0, index = 0;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    int memory[frames];
    for(i = 0; i < frames; i++)
        memory[i] = -1;

    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < frames; j++) {
            if(memory[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if(!found) {
            memory[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
    return 0;
}