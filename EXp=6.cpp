/* 6. Pre-emptive Priority Scheduling (smaller priority value = higher priority) */
#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[20], pr[20], at[20], rt[20];
    int wt[20], tat[20], ct[20];
    int i, complete = 0, t = 0, min_pr, shortest;
    int finished[20] = {0};
    float avgwt = 0, avgtat = 0;

    for (i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter priority of P%d (smaller = higher): ", i + 1);
        scanf("%d", &pr[i]);
        rt[i] = bt[i];
    }

    while (complete < n) {
        min_pr = 100000;
        shortest = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= t && !finished[i] && pr[i] < min_pr && rt[i] > 0) {
                min_pr = pr[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            t++;
            continue;
        }

        rt[shortest]--;
        t++;

        if (rt[shortest] == 0) {
            finished[shortest] = 1;
            complete++;
            ct[shortest] = t;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }

    printf("\nP\tAT\tBT\tPr\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }

    avgwt /= n;
    avgtat /= n;
    printf("\nAverage Waiting Time = %.2f\n", avgwt);
    printf("Average Turnaround Time = %.2f\n", avgtat);

    return 0;
}

