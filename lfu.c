#include <stdio.h>

int findLFU(int freq[], int time[], int frames) {
    int minFreq = freq[0], minTime = time[0], pos = 0;
    for (int i = 1; i < frames; i++) {
        if (freq[i] < minFreq || (freq[i] == minFreq && time[i] < minTime)) {
            minFreq = freq[i];
            minTime = time[i];
            pos = i;
        }
    }
    return pos;
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

    int memory[frames], freq[frames], time[frames];
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    int pagefault = 0, currentTime = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (memory[j] == pages[i]) {
                found = 1;
                freq[j]++;
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
                pos = findLFU(freq, time, frames);
            }

            memory[pos] = pages[i];
            freq[pos] = 1;
            time[pos] = currentTime++;
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