
#include <windows.h>
#include <stdio.h>

#define N 5
HANDLE chopstick[N];
HANDLE threads[N];

DWORD WINAPI philosopher(LPVOID param) {
    int id = (int)(intptr_t)param;
    int left = id;
    int right = (id + 1) % N;

    for (int i = 0; i < 3; i++) {
        printf("Philosopher %d is thinking\n", id);
        Sleep(500);

        if (id == N - 1) {
            WaitForSingleObject(chopstick[right], INFINITE);
            WaitForSingleObject(chopstick[left], INFINITE);
        } else {
            WaitForSingleObject(chopstick[left], INFINITE);
            WaitForSingleObject(chopstick[right], INFINITE);
        }

        printf("Philosopher %d is eating\n", id);
        Sleep(500);

        ReleaseMutex(chopstick[left]);
        ReleaseMutex(chopstick[right]);
    }
    printf("Philosopher %d finished\n", id);
    return 0;
}

int main() {
    for (int i = 0; i < N; i++)
        chopstick[i] = CreateMutex(NULL, FALSE, NULL);

    for (int i = 0; i < N; i++)
        threads[i] = CreateThread(NULL, 0, philosopher, (LPVOID)i, 0, NULL);

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    for (int i = 0; i < N; i++) {
        CloseHandle(chopstick[i]);
        CloseHandle(threads[i]);
    }

    return 0;
}

