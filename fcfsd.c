#include <stdio.h>
#include <stdlib.h>

void fcfs(int req[], int n, int head) {
    int seek = 0;
    printf("Seek sequence:\n");
    printf("%d -> ", head);  

    for (int i = 0; i < n; i++) {
        printf("%d", req[i]);
        if (i != n - 1) printf(" -> ");  
        seek += abs(req[i] - head);
        head = req[i];
    }

    printf("\n");
    printf("Total seek time: %d\n", seek);
}

int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    fcfs(req, n, head);

    return 0;
}
