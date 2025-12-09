
#include <stdio.h>
#include <string.h>

struct directory {
    char dname[20];
    char fname[10][20];
    int fc;
};

int main() {
    struct directory dir[10];
    int dc = 0;
    int ch, i, j;
    char d[20], f[20];

    while (1) {
        printf("\n1. Create directory\n2. Create file\n3. Search file\n4. List\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Enter directory name: ");
            scanf("%s", dir[dc].dname);
            dir[dc].fc = 0;
            dc++;
        } else if (ch == 2) {
            printf("Enter directory name: ");
            scanf("%s", d);
            int di = -1;
            for (i = 0; i < dc; i++)
                if (strcmp(dir[i].dname, d) == 0)
                    di = i;
            if (di == -1) {
                printf("Directory not found\n");
            } else {
                printf("Enter file name: ");
                scanf("%s", dir[di].fname[dir[di].fc]);
                dir[di].fc++;
            }
        } else if (ch == 3) {
            printf("Enter directory name: ");
            scanf("%s", d);
            printf("Enter file name: ");
            scanf("%s", f);
            int found = 0;
            for (i = 0; i < dc; i++) {
                if (strcmp(dir[i].dname, d) == 0) {
                    for (j = 0; j < dir[i].fc; j++) {
                        if (strcmp(dir[i].fname[j], f) == 0) {
                            printf("File found\n");
                            found = 1;
                        }
                    }
                }
            }
            if (!found)
                printf("File not found\n");
        } else if (ch == 4) {
            for (i = 0; i < dc; i++) {
                printf("Directory %s:\n", dir[i].dname);
                for (j = 0; j < dir[i].fc; j++)
                    printf("  %s\n", dir[i].fname[j]);
            }
        } else {
            break;
        }
    }
    return 0;
}

