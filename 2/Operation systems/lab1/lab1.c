#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <fcntl.h>


const int MAX_SIZE = 200;


void throw_error(int func, char * error_line) {
    if (func == -1) {
        fprintf(stderr, "%s\n", error_line);
        exit(EXIT_FAILURE);
    }
}


int main() {
    char filename[MAX_SIZE];
    fgets(filename, MAX_SIZE, stdin);

    int myfile = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
    throw_error(myfile, "Error in open file");
    close(myfile);

    int fd1[2], fd2[2];

    throw_error(pipe(fd1), "Error in pipe");
    throw_error(pipe(fd2), "Error in pipe");

    int write_first = fd1[1], read_first = fd1[0];
    int write_second = fd2[1], read_second = fd2[0];

    pid_t process_id = fork();
    throw_error(process_id, "Error in fork");

    if (process_id == 0) {
        close(read_second);
        close(write_first);

        throw_error(dup2(read_first, fileno(stdin)), "Error in dup2");
        close(read_first);

        throw_error(dup2(write_second, fileno(stdout)), "Error in dup2");
        close(write_second);

        throw_error(execl("child", "child", filename, NULL), "Error in execl");
    }

    if (process_id > 0) {
        close(write_second);
        close(read_first);

        char line[MAX_SIZE];
        char received_char;
        int index_of_line = 0;

        while (scanf("%c", &received_char) > 0) {
            line[index_of_line] = received_char;

            if (received_char == '\n') {
                int size_of_line = index_of_line + 1;
                dprintf(write_first, "%d ", size_of_line);
                for (int index_of_line = 0; index_of_line < size_of_line; ++index_of_line) {
                    dprintf(write_first, "%c", line[index_of_line]);
                }
                index_of_line = 0;
                continue;
            }

            ++index_of_line;
        }
        write(write_first, "c\0", sizeof(char));
        close(write_first);

        char output_char;
        while (read(read_second, &output_char, sizeof(char)) > 0) {
            putchar(output_char);
        }

        close(read_second);
    }
    return 0;
}