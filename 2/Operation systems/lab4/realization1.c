#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 1000;

int PrimeCount(int A, int B){
            printf("Function from 1\n");
    const int MAX_COUNT = 100;
    int count = 0;
    if(B-A>MAX_COUNT){
        return -1;
    }
    for(int i=A;i<=B;++i){
        char is_prime=1;
        for(int j=2;j<i;++j){
            if(i%j==0){
                is_prime = 0;
                break;
            }
        }
        if(is_prime){
            ++count;
        }
    }
    return count;
}


// char* translation(long x){
//     printf("Hello from 1\n");
//     if(x==0){
//         char* ans = malloc(sizeof(char));
//         ans[0] = '0';
//         return ans;
//     }
//     const int bits = sizeof(long)*MAX_SIZE;
//     char* ans = malloc(sizeof(char)*bits);
//     int i = bits-1;
//     while(i>=0){
//         char remainder = x%2;
//         ans[i]= remainder+'0';
//         x/=2;
//         --i;
//     }
//     int start = 0;
//     int end = bits-i;
//     i=0;
//     while(ans[i]=='0'){
//         ++i;
//     }
//     char* real_ans = malloc(sizeof(char)*(bits-i+1));
//     int j=0;
//     // ++real_ans;
//     while(i<bits){
//         real_ans[j] = ans[i];
//         ++j;
//         ++i;
//     }
//     free(ans);
//     ans=NULL;
//     return real_ans;
// }


char* translation(long x) {
            printf("Function from 1\n");

    int n = x;
    int length = 0;
    
    // Нахождение длины двоичного числа
    while (n > 0) {
        n = n / 2;
        length++;
    }
    
    // Выделение памяти для массива char
    char* binary = malloc((length + 1) * sizeof(char));
    
    // Заполнение массива char с конца
    int i = length - 1;
    while (x > 0) {
        binary[i] = (x % 2) + '0';
        x = x / 2;
        i--;
    }
    
    binary[length] = '\0';  // Добавление завершающего нуля
    
    return binary;
}