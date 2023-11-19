#include <stdio.h>
#include <stdlib.h>

extern int PrimeCount(int A, int B);
extern char* translation(long x);

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


int main(){
    int LibNum = 1;

    char* ans;
    int A, B, answer, q;
    long x;
    while(scanf("%d", &q)>0){
        if(q==1){
            printf("enter A, B\n");
            scanf("%d %d", &A, &B);
            answer = PrimeCount(A,B);
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
}