#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 50
#define MAX_FILES 10
int disk[MAX_BLOCKS];
struct File {
    char name[20];
    int indexBlock;         
    int blockCount;        
    int blocks[20];        
} directory[MAX_FILES];
int fileCount = 0;
void initDisk() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        disk[i] = -2;
}
int allocateBlock() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (disk[i] == -2) {
            disk[i] = -1;       
            return i;
        }
    }
    return -1; 
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
    printf("Enter number of blocks required: ");
    scanf("%d", &size);
    int indexBlk = allocateBlock();
    if (indexBlk == -1) {
        printf("No free block available for index!\n");
        return;
    }
    struct File f;
    strcpy(f.name, fname);
    f.indexBlock = indexBlk;
    f.blockCount = size;
    for (int i = 0; i < size; i++) {
        int blk = allocateBlock();
        if (blk == -1) {
            printf("Not enough blocks! File creation failed.\n");
            return;
        }
        f.blocks[i] = blk;
    }
    directory[fileCount++] = f;
    printf("\nFile '%s' created successfully!\n", fname);
}
void displayFiles() {
    if (fileCount == 0) {
        printf("\nNo files in directory.\n");
        return;
    }
    for (int i = 0; i < fileCount; i++) {
        struct File f = directory[i];
        printf("\nFile Name: %s", f.name);
        printf("\nIndex Block: %d", f.indexBlock);
        printf("\nBlocks: ");
        for (int j = 0; j < f.blockCount; j++)
            printf("%d ", f.blocks[j]);

        printf("\n");
    }
}
int main() {
    int choice;
    initDisk();
    while (1) {
        printf("\n--- Indexed Allocation Simulation ---\n");
        printf("1. Create File\n");
        printf("2. Display Directory\n");
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
