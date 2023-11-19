#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 1000;

int PrimeCount(int A, int B){
        printf("Function from 2\n");
    // Создание вектора для отметки простых чисел
    char* isPrime = malloc(sizeof(char)*(B + 1));
    for(int i=0;i<B+1;++i){
        isPrime[i] = 1;
    }
    
    isPrime[0] = 0;
    isPrime[1] = 0;
    
    for (int i = 2; i * i <= B; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= B; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    int count = 0;
    for (int i = A; i <= B; i++) {
        if (isPrime[i]) {
            count++;
        }
    }
    
    return count;   
}



char* translation(long x){
    printf("Function from 2\n");
    int n = x;
    int length = 0;
    
    // Нахождение длины двоичного числа
    while (n > 0) {
        n = n / 3;
        length++;
    }
    
    // Выделение памяти для массива char
    char* binary = malloc((length + 1) * sizeof(char));
    
    // Заполнение массива char с конца
    int i = length - 1;
    while (x > 0) {
        binary[i] = (x % 3) + '0';
        x = x / 3;
        i--;
    }
    
    binary[length] = '\0';  // Добавление завершающего нуля
    
    return binary;
}

// int main(){
//     char* ans = translation(11);
//     printf("%s\n", ans);
//     free(ans);
// }