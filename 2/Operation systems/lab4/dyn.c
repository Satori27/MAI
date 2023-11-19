#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void check(void* value, void* ok_val, char* msg){
    if(value!=ok_val){
        printf("%s\n", msg);
    }
}
void check_wrong(void* value, void* wrong_val, char* msg){
    if(value==wrong_val){
        printf("%s\n", msg);
    }
}
void check1(int value, int wrong_val, char* msg){
    if(value!=wrong_val){
        printf("%s\n", msg);
    }
}

const char* DYN_LIB_ONE = "./libDyn1.so";
const char* DYN_LIB_TWO = "./libDyn2.so";

const char* PRIME_COUNT_NAME = "PrimeCount";
const char* TRANSLATION_NAME = "translation";

int main(){
    int LibNum = 1;
    void* handle = dlopen(DYN_LIB_ONE, RTLD_LAZY);
    check_wrong(handle, NULL, "Can't open dynamic library");
    int (*PrimeCount)(int, int);
    char* (*translation)(long);

    PrimeCount = dlsym(handle, PRIME_COUNT_NAME);
    translation = dlsym(handle, TRANSLATION_NAME);
    char* error = dlerror();
    check(error, NULL, error);

    char* ans;
    int A, B, answer, q;
    long x;
    while(scanf("%d", &q)>0){
        if(q==0){
            check1(dlclose(handle), 0, "Error in closing dynamic library");
            if (LibNum) {
                handle = dlopen(DYN_LIB_TWO, RTLD_LAZY);
            } else {
                handle = dlopen(DYN_LIB_ONE, RTLD_LAZY);
            }
            check_wrong(handle, NULL, "Error opening dynamic library");
            PrimeCount = dlsym(handle, PRIME_COUNT_NAME);
            translation = dlsym(handle, TRANSLATION_NAME);
            error = dlerror();
            check(error, NULL, "Error");
            printf("Current library: %d\n", LibNum+1);
            LibNum = LibNum ^ 1;
            continue;
        }
        if(q==1){
            printf("enter A, B\n");
            scanf("%d %d", &A, &B);
            answer = PrimeCount(A,B);
            printf("1\n");
            printf("Answer is: %d\n", answer);
            continue;
        }
        if(q==2){
            printf("Enter number\n");
            scanf("%ld", &x);
            ans = translation(x);
            printf("Answer is: %s\n", ans);
            free(ans);
            ans=NULL;
            continue;
        }
        if(q==-1){
            break;
        }
    }
    printf("End\n");
    check1(dlclose(handle), 0, "Error closing dynamic library!\n");
}