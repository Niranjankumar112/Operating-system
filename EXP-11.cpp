
#include <windows.h>
#include <stdio.h>

DWORD WINAPI threadFunc(LPVOID param) {
    int id = (int)(intptr_t)param;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d running iteration %d\n", id, i + 1);
        Sleep(500);
    }
    return 0;
}

int main() {
    HANDLE threads[2];
    threads[0] = CreateThread(NULL, 0, threadFunc, (LPVOID)1, 0, NULL);
    threads[1] = CreateThread(NULL, 0, threadFunc, (LPVOID)2, 0, NULL);

    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    CloseHandle(threads[0]);
    CloseHandle(threads[1]);

    printf("Main thread finished.\n");
    return 0;
}

