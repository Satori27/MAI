#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <ctime>

#define ROWS 10
#define COLS 10

int main() {
    double matrix[ROWS][COLS];
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел

    // Заполнение матрицы случайными значениями
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;        
        }
    }
    // matrix[4][5] = 0;

    std::ofstream file("matrix.txt"); // Открытие файла для записи

    // Запись матрицы в файл
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            file << matrix[i][j] << " ";
        }
        file << std::endl;
    }

    file.close(); // Закрытие файла

    std::cout << "Матрица сохранена в файле matrix.txt" << std::endl;

    return 0;
}