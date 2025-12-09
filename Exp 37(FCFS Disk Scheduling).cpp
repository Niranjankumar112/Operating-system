#include <stdio.h>
#include <stdlib.h>
int main() {
    int n, head, i, seek = 0;
    int req[100];
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("\nFCFS Disk Scheduling Order:\n");
    for (i = 0; i < n; i++) {
        printf("%d -> ", req[i]);
        seek += abs(head - req[i]);
        head = req[i];
    }
    printf("\n\nTotal Seek Time = %d\n", seek);
    return 0;
}
