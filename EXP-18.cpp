/* 18. Producer-Consumer using semaphores  */
#include <windows.h>
#include <stdio.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

HANDLE emptySem, fullSem, mutexSem;
HANDLE prodThread, consThread;

DWORD WINAPI producer(LPVOID param) {
    for (int i = 1; i <= 10; i++) {
        WaitForSingleObject(emptySem, INFINITE);
        WaitForSingleObject(mutexSem, INFINITE);

        buffer[in] = i;
        printf("Producer produced %d at %d\n", i, in);
        in = (in + 1) % SIZE;

        ReleaseSemaphore(mutexSem, 1, NULL);
        ReleaseSemaphore(fullSem, 1, NULL);
        Sleep(200);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    for (int i = 1; i <= 10; i++) {
        WaitForSingleObject(fullSem, INFINITE);
        WaitForSingleObject(mutexSem, INFINITE);

        int item = buffer[out];
        printf("Consumer consumed %d from %d\n", item, out);
        out = (out + 1) % SIZE;

        ReleaseSemaphore(mutexSem, 1, NULL);
        ReleaseSemaphore(emptySem, 1, NULL);
        Sleep(300);
    }
    return 0;
}

int main() {
    emptySem = CreateSemaphore(NULL, SIZE, SIZE, NULL);
    fullSem = CreateSemaphore(NULL, 0, SIZE, NULL);
    mutexSem = CreateSemaphore(NULL, 1, 1, NULL);

    prodThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    CloseHandle(prodThread);
    CloseHandle(consThread);
    CloseHandle(emptySem);
    CloseHandle(fullSem);
    CloseHandle(mutexSem);

    return 0;
}

