#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void cscan(int req[], int n, int ds, int head, int dir) {
    sort(req, n);

    int seek = 0;
    printf("Seek sequence:\n");
    printf("%d", head);

    if (dir == 1) {
        int i = 0;
        while (i < n && req[i] < head) i++;
        for (int j = i; j < n; j++) {
            seek += abs(req[j] - head);
            head = req[j];
            printf(" -> %d", req[j]);
        }
       
        if (head != ds - 1) {
            seek += abs((ds - 1) - head);
            head = ds - 1;
            printf(" -> %d", head);
        }
  
        seek += (ds - 1);
        head = 0;
        printf(" -> %d", head);
       
        for (int j = 0; j < i; j++) {
            seek += abs(req[j] - head);
            head = req[j];
            printf(" -> %d", req[j]);
        }
    } else {
       
        int i = n - 1;
        while (i >= 0 && req[i] > head) i--;
        for (int j = i; j >= 0; j--) {
            seek += abs(req[j] - head);
            head = req[j];
            printf(" -> %d", req[j]);
        }
      
        if (head != 0) {
            seek += abs(head - 0);
            head = 0;
            printf(" -> %d", head);
        }
      
        seek += (ds - 1);
        head = ds - 1;
        printf(" -> %d", head);
    
        for (int j = n - 1; j > i; j--) {
            seek += abs(req[j] - head);
            head = req[j];
            printf(" -> %d", req[j]);
        }
    }

    printf("\nTotal seek time: %d\n", seek);
}

int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    int head;
    printf("Enter head: ");
    scanf("%d", &head);

    int dir;
    printf("Enter direction (1 for right, 0 for left): ");
    scanf("%d", &dir);

    int ds;
    printf("Enter disk size: ");
    scanf("%d", &ds);

    cscan(req, n, ds, head, dir);
    return 0;
}
