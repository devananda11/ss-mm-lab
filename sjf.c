#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, at, bt, ct, tat, wt, completed, st;
};

int findShortestJob(struct Process p[], int n, int currentTime) {
    int minIndex = -1, minBurst = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].at <= currentTime && p[i].bt < minBurst) {
            minBurst = p[i].bt;
            minIndex = i;
        }
    }
    return minIndex;
}

void sjf(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    while (completed < n) {
        int idx = findShortestJob(p, n, currentTime);
        if (idx == -1) {
            currentTime++;
            continue;
        }
        p[idx].st = currentTime;
        p[idx].ct = currentTime + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        currentTime = p[idx].ct;
        p[idx].completed = 1;
        completed++;
    }
}

void display(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);
}

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");

    for (int i = 0; i < n; i++) printf("--------");
    printf("-\n");

    for (int i = 0; i < n; i++) printf("|  P%-2d  ", p[i].pid);
    printf("|\n");

    for (int i = 0; i < n; i++) printf("--------");
    printf("-\n");

    for (int i = 0; i < n; i++) {
        if (i == 0) printf("%-8d", p[i].st);
        printf("%-8d", p[i].ct);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    sjf(p, n);
    display(p, n);
    printGanttChart(p, n);

    return 0;
}
