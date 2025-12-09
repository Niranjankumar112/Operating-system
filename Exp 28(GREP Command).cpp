#include <stdio.h>
#include <string.h>

int main() {
    char pattern[100], filename[100], line[500];
    FILE *fp;

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    printf("Enter filename: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    printf("\n----- Matching Lines (GREP Simulation) -----\n\n");

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}

