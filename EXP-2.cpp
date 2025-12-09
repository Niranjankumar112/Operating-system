#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *src, *dest;
    char ch;

    src = fopen("source.txt", "w");
    if (src == NULL) {
        printf("Error creating source file.\n");
        return 1;
    }
    fprintf(src, "This is sample text written inside the program.\n");
    fprintf(src, "File copy operation will duplicate this content.\n");

    fclose(src);

    src = fopen("source.txt", "r");
    if (src == NULL) {
        printf("Error opening internally created source file.\n");
        return 1;
    }
    dest = fopen("destination.txt", "w");
    if (dest == NULL) {
        printf("Error creating destination file.\n");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("Source.txt created and copied to destination.txt successfully.\n");

    return 0;
}

