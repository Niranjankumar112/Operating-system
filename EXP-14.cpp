
#include <stdio.h>
#include <string.h>

struct file {
    char name[20];
};

int main() {
    struct file dir[20];
    int count = 0;
    int ch;
    char fname[20];
    int i;

    while (1) {
        printf("\n1. Create file\n2. Delete file\n3. Search file\n4. List files\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Enter file name: ");
            scanf("%s", dir[count].name);
            count++;
        } else if (ch == 2) {
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            int found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(dir[i].name, fname) == 0) {
                    dir[i] = dir[count - 1];
                    count--;
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("File not found\n");
        } else if (ch == 3) {
            printf("Enter file name to search: ");
            scanf("%s", fname);
            int found = 0;
            for (i = 0; i < count; i++) {
                if (strcmp(dir[i].name, fname) == 0) {
                    printf("File found\n");
                    found = 1;
                    break;
                }
            }
            if (!found)
                printf("File not found\n");
        } else if (ch == 4) {
            printf("Files:\n");
            for (i = 0; i < count; i++)
                printf("%s\n", dir[i].name);
        } else {
            break;
        }
    }
    return 0;
}

