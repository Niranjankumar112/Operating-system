#include <stdio.h>
#include <windows.h>
DWORD WINAPI myThread(LPVOID arg) {
    printf("Inside thread... Thread Handle = %u\n", GetCurrentThreadId());
    ExitThread(1);  
}
int main() {
    HANDLE t1, t2;
    DWORD threadID1, threadID2;
    printf("Creating thread t1...\n");
    t1 = CreateThread(NULL, 0, myThread, NULL, 0, &threadID1);
    printf("Creating thread t2...\n");
    t2 = CreateThread(NULL, 0, myThread, NULL, 0, &threadID2);
    if (t1 == NULL || t2 == NULL) {
        printf("Error creating thread(s)!\n");
        return 1;
    }
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);
    printf("Thread t1 finished execution.\n");
    printf("Thread t2 finished execution.\n");
    if (threadID1 == threadID2)
        printf("t1 and t2 are EQUAL threads.\n");
    else
        printf("t1 and t2 are NOT equal threads.\n");
    CloseHandle(t1);
    CloseHandle(t2);
    printf("\nMain thread exiting...\n");
    return 0;
}
