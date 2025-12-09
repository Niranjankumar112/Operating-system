#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES 10
int disk[MAX_BLOCKS];  
struct File {
    char name[20];
    int start;      
    int length;    
} directory[MAX_FILES];
int fileCount = 0;
void initDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        disk[i] = -2;
}
int findContiguousBlocks(int length) {
    int freeCount = 0, start = -1;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == -2) {
            freeCount++;
            if (freeCount == length)
                return i - length + 1; 
        } else {
            freeCount = 0;
        }
    }
    return -1; 
}
void createFile() {
    if (fileCount >= MAX_FILES) {
        printf("Directory full!\n");
        return;
    }
    char fname[20];
    int size;
    printf("Enter file name: ");
    scanf("%s", fname);
    printf("Enter number of blocks needed: ");
    scanf("%d", &size);
    int start = findContiguousBlocks(size);
    if (start == -1) {
        printf("Not enough contiguous free blocks! File creation failed.\n");
        return;
    }
    for (int i = start; i < start + size; i++)
        disk[i] = 1;
    strcpy(directory[fileCount].name, fname);
    directory[fileCount].start = start;
    directory[fileCount].length = size;
    fileCount++;
    printf("\nFile '%s' created successfully!\n", fname);
}
void accessFile() {
    char fname[20];
    printf("Enter file name to access: ");
    scanf("%s", fname);
    for (int i = 0; i < fileCount; i++) {
        if (strcmp(directory[i].name, fname) == 0) {
            printf("\nSequentially reading file '%s':\n", fname);
            for (int b = 0; b < directory[i].length; b++) {
                printf("Reading Block %d\n", directory[i].start + b);
            }
            return;
        }
    }
    printf("File not found!\n");
}
void showDirectory() {
    if (fileCount == 0) {
        printf("No files created.\n");
        return;
    }
    printf("\nDirectory Listing:\n");
    for (int i = 0; i < fileCount; i++) {
        printf("\nFile: %s", directory[i].name);
        printf("\nStart Block: %d", directory[i].start);
        printf("\nLength: %d blocks\n", directory[i].length);
    }
}
int main() {
    int choice;
    initDisk();
    while (1) {
        printf("\n--- Contiguous Allocation Simulation ---\n");
        printf("1. Create File\n");
        printf("2. Sequentially Access File\n");
        printf("3. Directory Listing\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createFile(); break;
            case 2: accessFile(); break;
            case 3: showDirectory(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
