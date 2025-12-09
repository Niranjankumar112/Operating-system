/* 1. Create new process, display PID and PPID */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, mypid, myppid;

    pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0) { 
        mypid = getpid();
        myppid = getppid();
        printf("Child Process:\n");
        printf("PID  = %d\n", mypid);
        printf("PPID = %d\n", myppid);
    } else { 
        wait(NULL);
        mypid = getpid();
        myppid = getppid();
        printf("Parent Process:\n");
        printf("PID  = %d\n", mypid);
        printf("PPID = %d\n", myppid);
    }

    return 0;
}

