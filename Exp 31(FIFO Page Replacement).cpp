#include <stdio.h>
int main() {
    int pages[50], frame[10];
    int n, f, i, j, hit = 0, fault = 0, pointer = 0;
    printf("Enter number of page references: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++)
        frame[i] = -1;
    printf("\nFIFO Page Replacement Simulation:\n");
    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        for (j = 0; j < f; j++) {
            if (frame[j] == page) {
                hit++;
                found = 1;
                break;
            }
        }
        if (!found) {
            fault++;
            frame[pointer] = page;
            pointer = (pointer + 1) % f;
        }
        printf("\nAfter page %d: ", page);
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
