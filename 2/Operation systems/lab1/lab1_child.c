#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <fcntl.h>


int main(int argc, char * argv[]) {
    int file = open(argv[1], O_WRONLY);

    if (file == -1) {
        printf("Err: opening file\n");
        exit(EXIT_FAILURE);
    }

    int size_of_line;
    char received_char;
    int number_of_line = 0;

    while (scanf("%d", &size_of_line)) {
        ++number_of_line;
        char line[size_of_line];

        for (int index_of_line = 0; index_of_line < size_of_line; ++index_of_line) {
            scanf("%c", &received_char);
            line[index_of_line] = received_char;
        }
        
        if ('A' <= line[1] && line[1] <= 'Z') {
            printf("Error in line number %d\n", number_of_line);
        } else {
            for (int index_of_line = 1; index_of_line < size_of_line; ++index_of_line) {
                dprintf(file, "%c", line[index_of_line]);
            }
            dprintf(file, "\n");
        }

    }
    close(file);
    return 0;
}