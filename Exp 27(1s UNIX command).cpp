#include <stdio.h>
#include <windows.h>
int main() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    char directory[200];
    printf("Enter directory path (e.g., C:\\Windows\\*): ");
    scanf("%s", directory);
    hFind = FindFirstFile(directory, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Unable to open directory or invalid path.\n");
        return 1;
    }
    printf("\n----- Simulating ls Command -----\n\n");
    do {
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
    return 0;
}

