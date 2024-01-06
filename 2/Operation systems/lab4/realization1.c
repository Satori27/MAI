#include <stdio.h>
#include <stdlib.h>


int PrimeCount(int A, int B){
    printf("Function from 1\n");
    const int MAX_COUNT = 100;
    int count = 0;
    if(B-A>MAX_COUNT){
        return -1;
    }
    for(int interval_index=A;interval_index<=B;++interval_index){
        char is_prime=1;
        for(int second_index=2;second_index<interval_index;++second_index){
            if(interval_index%second_index==0){
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


char* translation(long number) {
    printf("Function from 1\n");

    int number_one = number;
    int length = 0;
    
    while (number_one > 0) {
        number_one = number_one / 2;
        length++;
    }
    
    char* binary = malloc((length + 1) * sizeof(char));
    
    int binary_index = length - 1;
    while (number > 0) {
        binary[binary_index] = (number % 2) + '0';
        number = number / 2;
        binary_index--;
    }
    
    binary[length] = '\0'; 
    
    return binary;
}