#include <stdio.h>

#define MAX_P 10 // Maximum number of processes
#define MAX_R 10 // Maximum number of resources

void isSafe(int P, int R, int need[MAX_P][MAX_R], int allocation[MAX_P][MAX_R], int available[MAX_R]) {
    int work[MAX_R], finish[MAX_P] = {0}, safeSequence[MAX_P];
    int completed = 0;

    // Copy available resources to work array
    for (int i = 0; i < R; i++)
        work[i] = available[i];

    while (completed < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) { // If process is not finished
                int j;
                int c=0;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break;
                    else{
                        c++;
                    }
                }

                if (c == R) { // If all needs can be satisfied
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    safeSequence[completed++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state!\n");
            return;
        }
    }

    // Print safe sequence
    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
}

int main() {
    int P, R;
    printf("Enter the number of processes: ");
    scanf("%d", &P);
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    int max[MAX_P][MAX_R], allocation[MAX_P][MAX_R], need[MAX_P][MAX_R], available[MAX_R];

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter the Maximum Matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &available[i]);

    // Calculate Need Matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Check system safety
    isSafe(P, R, need, allocation, available);

    return 0;
}