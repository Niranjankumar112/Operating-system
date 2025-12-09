/* 25. Demonstrate fcntl, lseek, stat, opendir, readdir */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd;
    struct stat st;
    char buf[21];
    DIR *dp;
    struct dirent *de;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
    } else {
        if (fstat(fd, &st) == 0) {
            printf("File size (stat): %ld bytes\n", (long)st.st_size);
        }

        if (lseek(fd, 5, SEEK_SET) == -1) {
            perror("lseek");
        } else {
            ssize_t n = read(fd, buf, 20);
            if (n > 0) {
                buf[n] = '\0';
                printf("Data after lseek: %s\n", buf);
            }
        }

        int flags = fcntl(fd, F_GETFL);
        if (flags != -1) {
            printf("File flags (F_GETFL): %d\n", flags);
        }
        close(fd);
    }

    dp = opendir(".");
    if (dp == NULL) {
        perror("opendir");
        return 0;
    }
    printf("Directory entries using readdir:\n");
    while ((de = readdir(dp)) != NULL) {
        printf("%s\n", de->d_name);
    }
    closedir(dp);
    return 0;
}

