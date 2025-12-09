/* 20. Reader-Writer problem using semaphores  */
#include <windows.h>
#include <stdio.h>

int readcount = 0;
int data = 0;

HANDLE mutexSem;
HANDLE rwSem;
HANDLE readers[3], writerThread;

DWORD WINAPI reader(LPVOID param) {
    int id = (int)(intptr_t)param;
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(mutexSem, INFINITE);
        readcount++;
        if (readcount == 1)
            WaitForSingleObject(rwSem, INFINITE);
        ReleaseSemaphore(mutexSem, 1, NULL);

        printf("Reader %d reads data = %d\n", id, data);
        Sleep(200);

        WaitForSingleObject(mutexSem, INFINITE);
        readcount--;
        if (readcount == 0)
            ReleaseSemaphore(rwSem, 1, NULL);
        ReleaseSemaphore(mutexSem, 1, NULL);

        Sleep(200);
    }
    return 0;
}

DWORD WINAPI writer(LPVOID param) {
    for (int i = 0; i < 5; i++) {
        WaitForSingleObject(rwSem, INFINITE);
        data++;
        printf("Writer writes data = %d\n", data);
        Sleep(300);
        ReleaseSemaphore(rwSem, 1, NULL);
        Sleep(300);
    }
    return 0;
}

int main() {
    mutexSem = CreateSemaphore(NULL, 1, 1, NULL);
    rwSem = CreateSemaphore(NULL, 1, 1, NULL);

    writerThread = CreateThread(NULL, 0, writer, NULL, 0, NULL);
    for (int i = 0; i < 3; i++)
        readers[i] = CreateThread(NULL, 0, reader, (LPVOID)i, 0, NULL);

    WaitForSingleObject(writerThread, INFINITE);
    WaitForMultipleObjects(3, readers, TRUE, INFINITE);

    CloseHandle(writerThread);
    for (int i = 0; i < 3; i++)
        CloseHandle(readers[i]);
    CloseHandle(mutexSem);
    CloseHandle(rwSem);

    return 0;
}

