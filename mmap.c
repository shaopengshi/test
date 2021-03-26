
#include <signal.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAP_SIZE 128


void *thread_func(void *arg)
{
    pthread_t id = pthread_self();
    printf("I'm the new thread, and my id is %d \n", (int)id);

    return arg;
}

int main(int argc, char *argv[])
{
    void *addr = NULL;
    char strbuf[MAP_SIZE] = {0};
    int fd = open("./text", O_RDWR);
    if (fd < 0) {
        printf("Open file failed.....\n");
        return -1;
    }

    addr = mmap(NULL, MAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == addr) {
        printf("map failed... \n");
        close(fd);
        return -1;
    }

    memcpy(strbuf, addr, 5);
    printf("content is %s  \n", strbuf);
    strncpy(addr, "HHHHHH000", 5);

    munmap(addr, MAP_SIZE);
    close(fd);

    printf("over ............ \n");

    return 0;
 }
