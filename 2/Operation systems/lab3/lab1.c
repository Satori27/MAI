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



int main(int argc, char, char const * argv[]) {

    char filename[MAX_SIZE];
    fgets(filename, MAX_SIZE, stdin);

    int myfile = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
    throw_error(myfile, -1, "Error in open file");
    close(myfile);
    char* parent_child = "parent_child";
    sem_unlink(parent_child);
    sem_t* semaphore = sem_open(parent_child, O_CREAT, 0666, 2);
    int state = 2;

    pid_t process_id = fork();
    throw_error(process_id, -1, "fork");
    if (process_id == 0) {
        sem_close(semaphore);
        int execl_error = execl("./child", "./child", filename, parent_child, NULL);
        throw_error(execl_error, 0, "execl");
    } else {
        char line[MAX_SIZE];
        int size;
        int flag = 1;
        while (flag) {
            int getvalue_error = sem_getvalue(semaphore, & state);
            throw_error(getvalue_error, -1, "sem_getvalue");
            if (state == 2) {
                fgets(line, MAX_SIZE, stdin);
                size = sizeof(line);
                int file = shm_open(parent_child, O_RDWR | O_CREAT, 0666);
                throw_error(file, -1, "shm_open");
                ftruncate(file, size);
                char * mapped = (char * ) mmap(NULL,
                    size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    file,
                    0);
                memset(mapped, '\0', size);
                sprintf(mapped, "%s", line);
                getvalue_error = sem_getvalue(semaphore, &state);
                throw_error(getvalue_error, -1, "sem_getvalue");
                close(file);
                set_semaphore(semaphore, &state, 1);
            }
            if (state == 0) {
                int file = shm_open(parent_child, O_RDWR | O_CREAT, 0666);
                throw_error(file, -1, "shm_open");
                struct stat stat_buffer;
                fstat(file, & stat_buffer);
                int size = stat_buffer.st_size;
                char * mapped = (char*) mmap(NULL,
                    size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    file,
                    0);
                printf("%s\n", mapped);
                close(file);
                munmap(mapped, size);
                set_semaphore(semaphore, &state, 2);

            }
            if (feof(stdin)) {
                set_semaphore(semaphore, &state, 2);

                size = 1;
                int file = shm_open(parent_child, O_RDWR | O_CREAT, 0666);
                throw_error(file, -1, "shm_open");
                ftruncate(file, size);
                char * mapped = (char*) mmap(NULL,
                    size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    file,
                    0);
                memset(mapped, '\0', size);
                sprintf(mapped, "%c", '\0');
                close(file);
                set_semaphore(semaphore, & state, 1);
                flag = 0;
            }
        }
    }
    sem_close(semaphore);
    sem_destroy(semaphore);
    return 0;
}