#include <windows.h>
#include <stdio.h>
#include <string.h>

void run_child_pipe() {
    HANDLE hPipe;
    char buffer[128];
    DWORD bytesWritten;

    Sleep(500);

    hPipe = CreateFileA(
        "\\\\.\\pipe\\MyMsgQueuePipe",
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Child: cannot open pipe.\n");
        return;
    }

    strcpy(buffer, "Hello from child via message queue (named pipe)");

    if (!WriteFile(
            hPipe,
            buffer,
            (DWORD)(strlen(buffer) + 1),
            &bytesWritten,
            NULL)) {
        printf("Child: WriteFile failed.\n");
        CloseHandle(hPipe);
        return;
    }

    printf("Child: message sent.\n");

    CloseHandle(hPipe);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        run_child_pipe();
        return 0;
    }

    HANDLE hPipe;
    char buffer[128];
    DWORD bytesRead;
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    char exePath[MAX_PATH];
    char cmdLine[512];

    hPipe = CreateNamedPipeA(
        "\\\\.\\pipe\\MyMsgQueuePipe",
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        0,
        0,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Parent: CreateNamedPipe failed.\n");
        return 1;
    }

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
        CloseHandle(hPipe);
        return 1;
    }

    printf("Parent: waiting for child to connect to pipe...\n");

    if (!ConnectNamedPipe(hPipe, NULL)) {
        printf("Parent: ConnectNamedPipe failed.\n");
        CloseHandle(hPipe);
        return 1;
    }

    if (!ReadFile(
            hPipe,
            buffer,
            sizeof(buffer),
            &bytesRead,
            NULL)) {
        printf("Parent: ReadFile failed.\n");
        CloseHandle(hPipe);
        return 1;
    }

    printf("Parent: message received: %s\n", buffer);

    CloseHandle(hPipe);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}

