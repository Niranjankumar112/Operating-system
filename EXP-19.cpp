/* 19. Process synchronization using mutex lock  */
#include <windows.h>
#include <stdio.h>

int counter = 0;
HANDLE mutexLock;
HANDLE t1, t2;

DWORD WINAPI incrementFunc(LPVOID param) {
    for (int i = 0; i < 100000; i++) {
        WaitForSingleObject(mutexLock, INFINITE);
        counter++;
        ReleaseMutex(mutexLock);
    }
    return 0;
}

int main() {
    mutexLock = CreateMutex(NULL, FALSE, NULL);

    t1 = CreateThread(NULL, 0, incrementFunc, NULL, 0, NULL);
    t2 = CreateThread(NULL, 0, incrementFunc, NULL, 0, NULL);

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(t1);
    CloseHandle(t2);
    CloseHandle(mutexLock);

    printf("Final counter value: %d\n", counter);
    return 0;
}

