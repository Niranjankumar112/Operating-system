#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
HANDLE mutex;
HANDLE empty;
HANDLE full;
DWORD WINAPI producer(LPVOID arg) {
    int item = 1;
    while (1) {
        WaitForSingleObject(empty, INFINITE); 
        WaitForSingleObject(mutex, INFINITE); 
        buffer[in] = item;
        printf("Producer produced item %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        ReleaseMutex(mutex);       
        ReleaseSemaphore(full, 1, NULL); 
        Sleep(500);
    }
}
DWORD WINAPI consumer(LPVOID arg) {
    int item;
    while (1) {
        WaitForSingleObject(full, INFINITE);  
        WaitForSingleObject(mutex, INFINITE); 
        item = buffer[out];
        printf("Consumer consumed item %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        ReleaseMutex(mutex);       
        ReleaseSemaphore(empty, 1, NULL); 
        Sleep(700);
    }
}
int main() {
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);
    HANDLE tProducer = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    HANDLE tConsumer = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    if (tProducer == NULL || tConsumer == NULL) {
        printf("Error creating threads.\n");
        return 1;
    }
    WaitForSingleObject(tProducer, INFINITE);
    WaitForSingleObject(tConsumer, INFINITE);
    return 0;
}
