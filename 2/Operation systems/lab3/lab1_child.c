#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <sys/mman.h>

#include <string.h>

#include <semaphore.h>

#include <fcntl.h>

#include <sys/stat.h>

const int MAX_SIZE = 200;



void set_semaphore(sem_t * semaphore, int * state, int value) {
    while (++( * state) < value + 1) {
        sem_post(semaphore);
    }
    while (--( * state) > value) {
        sem_wait(semaphore);
    }
}

void throw_error(int func, int error_number, char * error_line) {
    if (func == error_number) {
        fprintf(stderr, "%s\n", error_line);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char const * argv[]) {
    int file = open(argv[1], O_WRONLY);
    throw_error(file, -1, "Error in file");
    sem_t * semaphore = sem_open(argv[2], O_RDWR | O_CREAT, 0666);
    int state = 0;
    int flag = 1;
    while (flag) {
        int getvalue_error = sem_getvalue(semaphore, & state);
        throw_error(getvalue_error, -1, "sem_getvalue");
        if (state == 1) {
            int file = shm_open(argv[2], O_RDWR | O_CREAT, 0666);
            throw_error(file, -1, "shm_open");
            struct stat stat_buffer;
            fstat(file, & stat_buffer);
            int size = stat_buffer.st_size;
            char * mapped = (char * ) mmap(NULL,
                size,
                PROT_READ | PROT_WRITE,
                MAP_SHARED,
                file,
                0);
            if (mapped[0] == '\0') {
                set_semaphore(semaphore, &state, 1);
                usleep(25000);
                munmap(mapped, size);
                close(file);
                flag = 0;
            }
            char line[MAX_SIZE];
            strcpy(line, mapped);
            if ('A' <= line[0] && line[0] <= 'Z') {
                dprintf(file, "%s", line);
                set_semaphore(semaphore, &state, 2);
                usleep(25000);
            } else {
                memset(mapped, '\0', size);
                sprintf(mapped, "%s", line);
                munmap(mapped, size);
                close(file);
                set_semaphore(semaphore, &state, 0);
                usleep(25000);
            }
        }
    }
    return 0;
}