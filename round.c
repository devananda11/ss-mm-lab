#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rem;
};

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rem = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int completed = 0, currentTime = 0, queue[200], front = 0, rear = 0, inQueue[n];
    for (int i = 0; i < n; i++) inQueue[i] = 0;

    // Initially enqueue all processes that have arrived at t=0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    int start[200], finish[200], order[200], idx = 0;

    while (completed < n) {
        if (front < rear) {
            int i = queue[front++];
            int exec = (p[i].rem < quantum) ? p[i].rem : quantum;

            start[idx] = currentTime;
            order[idx] = p[i].pid;

            p[i].rem -= exec;
            currentTime += exec;

            finish[idx] = currentTime;
            idx++;

            // Check new arrivals
            for (int j = 0; j < n; j++) {
                if (p[j].at <= currentTime && !inQueue[j] && p[j].rem > 0) {
                    queue[rear++] = j;
                    inQueue[j] = 1;
                }
            }

            if (p[i].rem == 0) {
                p[i].ct = currentTime;
                completed++;
            } else {
                queue[rear++] = i;
            }
        } else {
            // CPU Idle
            start[idx] = currentTime;
            order[idx] = -1;
            currentTime++;
            finish[idx] = currentTime;
            idx++;
            // Add new arrivals at this idle moment
            for (int j = 0; j < n; j++) {
                if (p[j].at <= currentTime && !inQueue[j] && p[j].rem > 0) {
                    queue[rear++] = j;
                    inQueue[j] = 1;
                }
            }
        }
    }

    // Gantt Chart
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < idx; i++) printf("-------");
    printf("\n|");
    for (int i = 0; i < idx; i++) {
        if (order[i] == -1)
            printf(" IDLE |");
        else
            printf("  P%d  |", order[i]);
    }
    printf("\n ");
    for (int i = 0; i < idx; i++) printf("-------");
    printf("\n%d", start[0]);
    for (int i = 0; i < idx; i++) printf("     %d", finish[i]);
    printf("\n");

    // Results
    float totalWT = 0, totalTAT = 0;
    printf("\nProcess  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAverage TAT = %.2f\n", totalTAT / n);
    printf("Average WT  = %.2f\n", totalWT / n);

    return 0;
}