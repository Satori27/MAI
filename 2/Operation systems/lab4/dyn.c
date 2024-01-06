#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void check(void* value, void* ok_value, char* message){
    if(value!=ok_value){
        printf("%s\n", message);
    }
}
void check_wrong(void* value, void* wrong_value, char* message){
    if(value==wrong_value){
        printf("%s\n", message);
    }
}
void check_int(int value, int wrong_value, char* message){
    if(value!=wrong_value){
        printf("%s\n", message);
    }
}

const char* DYN_LIB_ONE = "./libDyn1.so";
const char* DYN_LIB_TWO = "./libDyn2.so";

const char* PRIME_COUNT_NAME = "PrimeCount";
const char* TRANSLATION_NAME = "translation";

int main(){
    int library_number = 1;
    void* handle = dlopen(DYN_LIB_ONE, RTLD_LAZY);
    check_wrong(handle, NULL, "Can't open dynamic library");
    int (*PrimeCount)(int, int);
    char* (*translation)(long);

    PrimeCount = dlsym(handle, PRIME_COUNT_NAME);
    translation = dlsym(handle, TRANSLATION_NAME);
    char* error = dlerror();
    check(error, NULL, error);

    char* translation_answer;
    int A, B, prime_count_answer, query;
    long x;
    while(scanf("%d", &query)>0){
        if(query==0){
            check_int(dlclose(handle), 0, "Error in closing dynamic library");
            if (library_number) {
                handle = dlopen(DYN_LIB_TWO, RTLD_LAZY);
            } else {
                handle = dlopen(DYN_LIB_ONE, RTLD_LAZY);
            }
            check_wrong(handle, NULL, "Error opening dynamic library");
            PrimeCount = dlsym(handle, PRIME_COUNT_NAME);
            translation = dlsym(handle, TRANSLATION_NAME);
            error = dlerror();
            check(error, NULL, "Error");
            printf("Current library: %d\n", library_number+1);
            library_number = library_number ^ 1;
            continue;
        }
        if(query==1){
            printf("enter A, B\n");
            scanf("%d %d", &A, &B);
            prime_count_answer = PrimeCount(A,B);
            printf("1\n");
            printf("Answer is: %d\n", prime_count_answer);
            continue;
        }
        if(query==2){
            printf("Enter number\n");
            scanf("%ld", &x);
            translation_answer = translation(x);
            printf("Answer is: %s\n", translation_answer);
            free(translation_answer);
            translation_answer=NULL;
            continue;
        }
        if(query==-1){
            break;
        }
    }
    printf("End\n");
    check_int(dlclose(handle), 0, "Error closing dynamic library!\n");
}