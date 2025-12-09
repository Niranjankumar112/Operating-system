#include <stdio.h>
#include <stdlib.h>
int main() {
    int i, j, n, head, disk_size;
    int requests[100], left[100], right[100];
    int lcount = 0, rcount = 0, seek = 0;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &disk_size);
    for (i = 0; i < n; i++) {
        if (requests[i] < head)
            left[lcount++] = requests[i];
        else
            right[rcount++] = requests[i];
    }
    left[lcount++] = 0;
    right[rcount++] = disk_size - 1;
    for (i = 0; i < lcount - 1; i++)
        for (j = 0; j < lcount - 1 - i; j++)
            if (left[j] > left[j + 1]) {
                int temp = left[j];
                left[j] = left[j + 1];
                left[j + 1] = temp;
            }
    for (i = 0; i < rcount - 1; i++)
        for (j = 0; j < rcount - 1 - i; j++)
            if (right[j] > right[j + 1]) {
                int temp = right[j];
                right[j] = right[j + 1];
                right[j + 1] = temp;
            }
    printf("\nC-SCAN Disk Scheduling Order:\n");
    for (i = 0; i < rcount; i++) {
        printf("%d -> ", right[i]);
        seek += abs(head - right[i]);
        head = right[i];
    }
    head = 0;
    for (i = 0; i < lcount; i++) {
        printf("%d -> ", left[i]);
        seek += abs(head - left[i]);
        head = left[i];
    }
    printf("\n\nTotal Seek Time = %d\n", seek);
    return 0;
}
