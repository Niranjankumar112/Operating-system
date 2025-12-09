#include <stdio.h>
int main() {
    int pages[50], frame[10], recent[10];
    int n, f, i, j, hit = 0, fault = 0;
    printf("Enter number of page references: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    for (i = 0; i < f; i++) {
        frame[i] = -1;
        recent[i] = 0;}
    printf("\nLRU Page Replacement Simulation:\n");
    for (i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        for (j = 0; j < f; j++)
            recent[j]++;
        for (j = 0; j < f; j++) {
            if (frame[j] == page) {
                hit++;
                recent[j] = 0;   
                found = 1;
                break; }
        }
        if (!found) {
            fault++;
            int placed = 0;
            for (j = 0; j < f; j++) {
                if (frame[j] == -1) {
                    frame[j] = page;
                    recent[j] = 0;
                    placed = 1;
                    break;}
            }
            if (!placed) {
                int lru = 0;
                for (j = 1; j < f; j++) {
                    if (recent[j] > recent[lru])
                        lru = j; }
                frame[lru] = page;
                recent[lru] = 0;}
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
