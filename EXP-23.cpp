/* 23. First Fit Memory Allocation */
#include <stdio.h>

int main() {
    int nb, np;
    int b[20], p[20], alloc[20];
    int i, j;

    printf("Enter number of blocks: ");
    scanf("%d", &nb);
    printf("Enter block sizes:\n");
    for (i = 0; i < nb; i++)
        scanf("%d", &b[i]);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter process sizes:\n");
    for (i = 0; i < np; i++)
        scanf("%d", &p[i]);

    for (i = 0; i < np; i++)
        alloc[i] = -1;

    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (b[j] >= p[i]) {
                alloc[i] = j;
                b[j] -= p[i];
                break;
            }
        }
    }

    printf("\nProcess\tSize\tBlock\n");
    for (i = 0; i < np; i++) {
        if (alloc[i] != -1)
            printf("P%d\t%d\tB%d\n", i + 1, p[i], alloc[i] + 1);
        else
            printf("P%d\t%d\tNot allocated\n", i + 1, p[i]);
    }
    return 0;
}

