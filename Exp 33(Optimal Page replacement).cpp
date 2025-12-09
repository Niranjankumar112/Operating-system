#include <stdio.h>
int findOptimal(int pages[], int frame[], int n, int f, int index) {
    int i, j, farthest = index, replace = -1;
    for (i = 0; i < f; i++) {
        int k;
        for (k = index + 1; k < n; k++) {
            if (frame[i] == pages[k]) {
                if (k > farthest) {
                    farthest = k;
                    replace = i;
                }
                break;
            }
        }
        if (k == n)
            return i;
    }
    if (replace == -1)
        return 0;
    return replace;
}
int main() {
    int pages[30], frame[10];
    int n, f, i, j, hit = 0, fault = 0;
    printf("Enter number of page references: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++)
        frame[i] = -1;
    printf("\nOptimal Page Replacement Simulation:\n");
    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++) {
            if (frame[j] == pages[i]) {
                hit++;
                found = 1;
                break;
            }
        }
        if (!found) {
            fault++;
            int replaced = -1;
            for (j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = pages[i];
                    replaced = j;
                    break;
                }
            }
            if (replaced == -1) {
                int pos = findOptimal(pages, frame, n, f, i);
                frame[pos] = pages[i];
            }
        }
        printf("\nAfter page %d: ", pages[i]);
        for (j = 0; j < f; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
    }
    printf("\n\nTotal Page Hits  = %d", hit);
    printf("\nTotal Page Faults = %d\n", fault);
    return 0;
}

