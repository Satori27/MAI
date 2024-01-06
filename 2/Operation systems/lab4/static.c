#include <stdio.h>
#include <stdlib.h>

extern int PrimeCount(int A, int B);
extern char* translation(long number);

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
void check1(int value, int wrong_value, char* message){
    if(value!=wrong_value){
        printf("%s\n", message);
    }
}


int main(){
    char* translation_answer;
    int A, B, prime_count_answer, query;
    long number;
    while(scanf("%d", &query)>0){
        if(query==1){
            printf("enter A, B\n");
            scanf("%d %d", &A, &B);
            prime_count_answer = PrimeCount(A,B);
            printf("Answer is: %d\n", prime_count_answer);
            continue;
        }
        if(query==2){
            printf("Enter number\n");
            scanf("%ld", &number);
            translation_answer = translation(number);
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
}