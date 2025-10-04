#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
};

void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs(struct Process p[], int n) {
    int currentTime = 0;
    int start[n], finish[n];

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        start[i] = currentTime;
        p[i].ct = currentTime + p[i].bt;
        finish[i] = p[i].ct;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime = p[i].ct;
    }

    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");
    for (int i = 0; i < n; i++) {
        printf("  P%d  |", p[i].pid);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n%d", start[0]);
    for (int i = 0; i < n; i++) {
        printf("     %d", finish[i]);
    }
    printf("\n");
}

void display(struct Process p[], int n) {
    float totalTAT = 0, totalWT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f\n", totalWT / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    sortByArrivalTime(p, n);
    fcfs(p, n);
    display(p, n);

    return 0;
}
