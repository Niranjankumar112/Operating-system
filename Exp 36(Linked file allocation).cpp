#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES 10
int disk[MAX_BLOCKS];
struct File {
    char name[20];
    int start;
    int end;
} dir[MAX_FILES];
int fileCount = 0;
void initDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        disk[i] = -2; 
}
void createFile() {
    if (fileCount >= MAX_FILES) {
        printf("Directory Full!\n");
        return;
    }
    char fname[20];
    int size;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter file size (number of blocks required): ");
    scanf("%d", &size);
    int freeCount = 0;
    for (int i = 0; i < MAX_BLOCKS; i++)
        if (disk[i] == -2)
            freeCount++;
    if (freeCount < size) {
        printf("Not enough free blocks available!\n");
        return;
    }
    int prev = -1, first = -1, current;
    for (int i = 0; i < size; i++) {
        for (current = 0; current < MAX_BLOCKS; current++)
            if (disk[current] == -2)
                break;
        disk[current] = -1; 
        if (first == -1)
            first = current;
        if (prev != -1)
            disk[prev] = current; 
        prev = current;
    }
    disk[prev] = -1;
    strcpy(dir[fileCount].name, fname);
    dir[fileCount].start = first;
    dir[fileCount].end = prev;
    fileCount++;
    printf("\nFile '%s' created successfully!\n", fname);
}
void displayFiles() {
    if (fileCount == 0) {
        printf("No files in directory.\n");
        return;
    }
    for (int i = 0; i < fileCount; i++) {
        printf("\nFile: %s\n", dir[i].name);
        printf("Start Block: %d\n", dir[i].start);
        printf("End Block: %d\n", dir[i].end);
        printf("Blocks: ");
        int b = dir[i].start;
        while (b != -1) {
            printf("%d -> ", b);
            b = disk[b];
        }
        printf("END\n");
    }
}
int main() {
    int choice;
    initDisk();
    while (1) {
        printf("\n--- Linked Allocation Simulation ---\n");
        printf("1. Create File\n");
        printf("2. Display Directory & Blocks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createFile(); break;
            case 2: displayFiles(); break;
            case 3: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
    return 0;
}
