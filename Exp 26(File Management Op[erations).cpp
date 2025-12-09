#include <stdio.h>
#include <stdlib.h>
void createFile() {
    char fname[50];
    FILE *fp;
    printf("Enter file name to create: ");
    scanf("%s", fname);
    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return;
    }
    printf("File '%s' created successfully.\n", fname);
    fclose(fp);
}
void writeFile() {
    char fname[50], data[500];
    FILE *fp;
    printf("Enter file name to write into: ");
    scanf("%s", fname);
    fp = fopen(fname, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter text to write: ");
    fflush(stdin);
    fgets(data, sizeof(data), stdin);
    fputs(data, fp);
    printf("Data written successfully.\n");
    fclose(fp);
}
void readFile() {
    char fname[50], ch;
    FILE *fp;
    printf("Enter file name to read: ");
    scanf("%s", fname);
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("File does not exist!\n");
        return;
    }
    printf("\n--- File Content ---\n");
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    printf("\n--------------------\n");
    fclose(fp);
}
void appendFile() {
    char fname[50], data[500];
    FILE *fp;
    printf("Enter file name to append data: ");
    scanf("%s", fname);
    fp = fopen(fname, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter text to append: ");
    fflush(stdin);
    fgets(data, sizeof(data), stdin);
    fputs(data, fp);
    printf("Data appended successfully.\n");
    fclose(fp);
}
void deleteFile() {
    char fname[50];
    printf("Enter file name to delete: ");
    scanf("%s", fname);
    if (remove(fname) == 0)
        printf("File '%s' deleted successfully.\n", fname);
    else
        printf("Error deleting file or file does not exist.\n");
}
int main() {
    int choice;
    while (1) {
        printf("\n--- File Management System ---\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Append to File\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1: createFile(); break;
        case 2: writeFile(); break;
        case 3: readFile(); break;
        case 4: appendFile(); break;
        case 5: deleteFile(); break;
        case 6: exit(0);
        default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

