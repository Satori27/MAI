#include <stdio.h>
#include <stdlib.h>


int PrimeCount(int A, int B){
    printf("Function from 2\n");
    char* is_prime = malloc(sizeof(char)*(B + 1));
    for(int is_prime_index=0;is_prime_index<B+1;++is_prime_index){
        is_prime[is_prime_index] = 1;
    }
    
    is_prime[0] = 0;
    is_prime[1] = 0;
    
    for (int is_prime_index = 2; is_prime_index * is_prime_index <= B; is_prime_index++) {
        if (is_prime[is_prime_index]) {
            for (int second_index = is_prime_index * is_prime_index; second_index <= B; second_index += is_prime_index) {
                is_prime[second_index] = 0;
            }
        }
    }
    int count = 0;
    for (int check_prime = A; check_prime <= B; check_prime++) {
        if (is_prime[check_prime]) {
            count++;
        }
    }
    
    return count;   
}


char* translation(long number){
    printf("Function from 2\n");
    int number_one = number;
    int length = 0;
    
    while (number_one > 0) {
        number_one = number_one / 3;
        length++;
    }
    
    char* binary = malloc((length + 1) * sizeof(char));
    
    int binary_index = length - 1;
    while (number > 0) {
        binary[binary_index] = (number % 3) + '0';
        number = number / 3;
        binary_index--;
    }
    
    binary[length] = '\0'; 
    
    return binary;
}