// how to compile gcc -pthread race_cond_with_mutex.cpp

#include <stdio.h>

#include <pthread.h>

#include <time.h>


#include <unistd.h>

#include <stdlib.h>

#include <sys/wait.h>

#include <fcntl.h>


struct ThreadArgs {
    double(*result_matrix)[];
    double(*original_matrix)[];
    int* num1;
    int* num2;
    int* columns;
};

const double MAXIMUM_NUMBER = 1.79769e+308;
const double MINIMUM_NUMBER = -1.79769e+308;
const int MAX_SIZE = 100;

int step;
pthread_mutex_t mutex;

double overlay_matrix[3][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1}
};


void error_th(int func, char * error_line) {
    if (func != 0) {
        fprintf(stderr, "%s\n", error_line);
        exit(EXIT_FAILURE);
    }
}

void prepare_th(struct ThreadArgs * thread_object, int row_index, int column_index, int columns, double( * result_matrix)[], double( * matrix1)[]) {
    thread_object -> num1 = malloc(sizeof(int));
    thread_object -> num2 = malloc(sizeof(int));
    thread_object -> columns = malloc(sizeof(int));
    *thread_object -> num1 = row_index;
    *thread_object -> num2 = column_index;
    *thread_object -> columns = columns;
    thread_object -> result_matrix = result_matrix;
    thread_object -> original_matrix = matrix1;
}


void* erosion(void * args) {

    pthread_mutex_lock( & mutex);
    struct ThreadArgs * argument = (struct ThreadArgs * ) args;

    int columns = * (argument -> columns);
    int row_index = * (argument -> num1);
    int column_index = * (argument -> num2);
    double(*erosion_matrix)[columns + 2] = argument -> result_matrix;
    double(*erosion_copy)[columns + 2] = argument -> original_matrix;

    for (int left_row_index = row_index; left_row_index <= row_index + step; ++left_row_index) {
        for (int left_column_index = column_index; left_column_index <= column_index + step; ++left_column_index) {
            double minimum = MAXIMUM_NUMBER;
            for (int overlay_row = 0; overlay_row < 3; overlay_row++) {
                for (int overlay_column = 0; overlay_column < 3; overlay_column++) {

                    if (overlay_matrix[overlay_row][overlay_column] == 0) {
                        continue;
                    }

                    if (minimum > erosion_copy[left_row_index + overlay_row][left_column_index + overlay_column]) {
                        minimum = erosion_copy[left_row_index + overlay_row][left_column_index + overlay_column];
                    }

                }
            }

            erosion_matrix[left_row_index + 1][left_column_index + 1] = minimum;
        }
    }

    free(args);
    pthread_mutex_unlock( & mutex);
    pthread_exit(0);
}



void* dilate(void * args) {
    pthread_mutex_lock( & mutex);
    struct ThreadArgs * argument = (struct ThreadArgs * ) args;

    int row_index = * (argument -> num1);
    int column_index = * (argument -> num2);
    int columns = * (argument -> columns);
    double(*dilate_matrix)[columns + 2] = argument -> result_matrix;
    double(*dilate_copy)[columns + 2] = argument -> original_matrix;

    for (int left_row_index = row_index; left_row_index <= row_index + step; ++left_row_index) {
        for (int left_column_index = column_index; left_column_index <= column_index + step; ++left_column_index) {
            double maximum = MINIMUM_NUMBER;
            for (int overlay_row = 0; overlay_row < 3; overlay_row++) {
                for (int overlay_column = 0; overlay_column < 3; overlay_column++) {

                    if (overlay_matrix[overlay_row][overlay_column] == 0) {
                        continue;
                    }

                    if (maximum < dilate_copy[left_row_index + overlay_row][left_column_index + overlay_column]) {
                        maximum = dilate_copy[left_row_index + overlay_row][left_column_index + overlay_column];
                    }

                }
            }

            dilate_matrix[left_row_index + 1][left_column_index + 1] = maximum;
        }
    }
    free(args);
    pthread_mutex_unlock( & mutex);
    pthread_exit(0);
}




int main() {
    char filename[MAX_SIZE];
    fgets(filename, MAX_SIZE, stdin);
    int myfile = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
    
    if(myfile==-1)
        printf("Can't open file");


    int thread_count;
    scanf("%d\n", &thread_count);
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread[thread_count];

    int rows, columns, k;
    double number;
    scanf("%d\n", &k);

    scanf("%d %d", &rows, &columns);

    if (rows < 5 || columns < 5) {
        printf("Can't be less 5\n");
        return 0;
    }

    step = 1;

    if (rows/thread_count > 2 && columns /thread_count > 2) {
        step = rows/thread_count;
    }

    double matrix[rows][columns];

    for (int row_index = 0; row_index < rows; row_index++) {
        for (int column_index = 0; column_index < columns; column_index++) {
            scanf("%lf", &matrix[row_index][column_index]);
        }
    }

    double erosion_matrix[rows + 2][columns + 2];
    for (int row_index = 0; row_index < rows+2; row_index++) {
        for (int column_index = 0; column_index < columns+2; column_index++) {
            if (row_index == 0 || row_index == rows + 1 || column_index == 0 || column_index == columns + 1) {
                erosion_matrix[row_index][column_index] = MAXIMUM_NUMBER;
            } else {
                erosion_matrix[row_index][column_index] = matrix[row_index-1][column_index-1];
            }
        }
    }


    double dilate_matrix[rows + 2][columns + 2];
    for (int row_index = 0; row_index < rows+2; row_index++) {
        for (int column_index = 0; column_index < columns+2; column_index++) {
            if (row_index == 0 || row_index == rows + 1 || column_index == 0 || column_index == columns + 1) {
                dilate_matrix[row_index][column_index] = MINIMUM_NUMBER;
            } else {
                dilate_matrix[row_index][column_index] = matrix[row_index-1][column_index-1];
            }
        }
    }


    double erosion_copy[rows + 2][columns + 2];
    for (int row_index = 0; row_index < rows + 2; ++row_index) {
        for (int column_index = 0; column_index < columns + 2; ++column_index) {
            erosion_copy[row_index][column_index] = erosion_matrix[row_index][column_index];
        }
    }


    
    double dilate_copy[rows + 2][columns + 2];
    for (int row_index = 0; row_index < rows + 2; ++row_index) {
        for (int column_index = 0; column_index < columns + 2; ++column_index) {
            dilate_copy[row_index][column_index] = dilate_matrix[row_index][column_index];
        }
    }

    clock_t start = clock();

    int current_thread = 0;
    for (int index_k = 0; index_k < k; ++index_k) {

        for (int row_index = 0; row_index < rows - step; row_index += step) {
            for (int column_index = 0; column_index < columns - step; column_index += step) {

                struct ThreadArgs * erosion_object = malloc(sizeof(struct ThreadArgs));
                prepare_th(erosion_object, row_index, column_index, columns, erosion_matrix, erosion_copy);
                error_th(pthread_create(&thread[current_thread], NULL, &erosion, (void* ) erosion_object), "Error in create");
                ++current_thread;

                if (current_thread-1 == thread_count) {
                    for (int thread_index = 0; thread_index <= thread_count; ++thread_index) {
                        error_th(pthread_join(thread[thread_index], NULL), "Error in first join");
                    }
                    current_thread = 0;
                }

                struct ThreadArgs * dilate_object = malloc(sizeof(struct ThreadArgs));;
                prepare_th(dilate_object, row_index, column_index, columns, dilate_matrix, dilate_copy);
                error_th(pthread_create(&thread[current_thread], NULL, &dilate, (void* ) dilate_object), "Error in create");
                ++current_thread;

                if (current_thread-1 == thread_count) {
                    for (int thread_index = 0; thread_index <= thread_count; ++thread_index) {
                        error_th(pthread_join(thread[thread_index], NULL), "Error in first join");
                    }
                    current_thread = 0;
                }

            }
        }

        for (int thread_index = 0; thread_index < current_thread-2; ++thread_index) {
            error_th(pthread_join(thread[thread_index], NULL), "Error in second join");
        }
        current_thread = 0;

        for (int row_index = 0; row_index < rows + 2; ++row_index) {
            for (int column_index = 1; column_index < columns + 2; ++column_index) {
                erosion_copy[row_index][column_index] = erosion_matrix[row_index][column_index];
            }
        }
        
        for (int row_index = 0; row_index < rows + 2; ++row_index) {
            for (int column_index = 1; column_index < columns + 1; ++column_index) {
                dilate_copy[row_index][column_index] = dilate_matrix[row_index][column_index];
            }
        }

    }
    clock_t end = clock();
    double result = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time: %lf\n\n", result);


    for (int row_index = 1; row_index < rows +1; ++row_index) {
        for (int column_index = 1; column_index < columns + 1; ++column_index) {
            dprintf(myfile, "%lf ", erosion_matrix[row_index][column_index]);
        }
        dprintf(myfile, "\n");
    }
    dprintf(myfile, "\n\n");


    for (int row_index = 1; row_index < rows +1; ++row_index) {
        for (int column_index = 1; column_index < columns + 1; ++column_index) {
            dprintf(myfile, "%lf ", dilate_matrix[row_index][column_index]);
        }
        dprintf(myfile, "\n");
    }
    return 0;
}