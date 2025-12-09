/* 24. Demonstrate basic UNIX file system calls: open, read, write, close */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd_src, fd_dest;
    char buf[1024];
    ssize_t n;

    fd_src = open("input.txt", O_RDONLY);
    if (fd_src < 0) {
        perror("open source");
        return 1;
    }

    fd_dest = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0) {
        perror("open dest");
        close(fd_src);
        return 1;
    }

    while ((n = read(fd_src, buf, sizeof(buf))) > 0) {
        if (write(fd_dest, buf, n) != n) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    if (n < 0)
        perror("read");

    close(fd_src);
    close(fd_dest);
    printf("File copied using UNIX system calls.\n");
    return 0;
}

