
#include <stdio.h>

int main() {
    int nb, np;
    int b[10], p[10], alloc[10];
    int i, j, ch;

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

    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter choice: ");
    scanf("%d", &ch);

    for (i = 0; i < np; i++)
        alloc[i] = -1;

    if (ch == 1) {
        for (i = 0; i < np; i++) {
            for (j = 0; j < nb; j++) {
                if (b[j] >= p[i]) {
                    alloc[i] = j;
                    b[j] -= p[i];
                    break;
                }
            }
        }
    } else if (ch == 2) {
        for (i = 0; i < np; i++) {
            int best = -1;
            for (j = 0; j < nb; j++) {
                if (b[j] >= p[i]) {
                    if (best == -1 || b[j] < b[best])
                        best = j;
                }
            }
            if (best != -1) {
                alloc[i] = best;
                b[best] -= p[i];
            }
        }
    } else if (ch == 3) {
        for (i = 0; i < np; i++) {
            int worst = -1;
            for (j = 0; j < nb; j++) {
                if (b[j] >= p[i]) {
                    if (worst == -1 || b[j] > b[worst])
                        worst = j;
                }
            }
            if (worst != -1) {
                alloc[i] = worst;
                b[worst] -= p[i];
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

