#include <windows.h>
#include <stdio.h>
#include <string.h>

void run_child() {
    HANDLE hMapFile;
    char *pBuf;

    hMapFile = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        "MySharedMemory"
    );

    if (hMapFile == NULL) {
        printf("Child: OpenFileMapping failed.\n");
        return;
    }

    pBuf = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        0
    );

    if (pBuf == NULL) {
        printf("Child: MapViewOfFile failed.\n");
        CloseHandle(hMapFile);
        return;
    }

    printf("Child: read from shared memory: %s\n", pBuf);

    strcpy(pBuf, "Hello back from child via shared memory");

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        run_child();
        return 0;
    }

    HANDLE hMapFile;
    char *pBuf;
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    char exePath[MAX_PATH];
    char cmdLine[512];

    hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMapFile == NULL) {
        printf("Parent: CreateFileMapping failed.\n");
        return 1;
    }

    pBuf = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        0
    );

    if (pBuf == NULL) {
        printf("Parent: MapViewOfFile failed.\n");
        CloseHandle(hMapFile);
        return 1;
    }

    strcpy(pBuf, "Hello from parent via shared memory");
    printf("Parent: written to shared memory.\n");

    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    sprintf(cmdLine, "\"%s\" child", exePath);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(
            NULL,
            cmdLine,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        printf("Parent: CreateProcess failed.\n");
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    printf("Parent: after child, shared memory now: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

