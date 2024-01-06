#include <stdio.h>
#include <stdlib.h>

void PrintTable(int mas[][2], int count) {
    for (int i = 0; i < count; ++i) {
        printf("%d ", mas[i][0]);
    }
    printf("\n");
    for (int i = 0; i < count; ++i) {
        printf("%d ", mas[i][1]);
    }
}

void QuickSort(int mas[][2], int left, int right) {
    int pivotkey, pivotvalue;
    int leftborder = left;
    int rightborder = right;
    pivotkey = mas[left][0];
    pivotvalue = mas[left][1];
    while (left < right) {
        while ((mas[right][0] >= pivotkey) && (left < right)) {
            --right;
        }
        if (left != right) {
            mas[left][0] = mas[right][0];
            mas[left][1] = mas[right][1];
            ++left;
        }
        while ((mas[left][0] <= pivotkey) && (left < right)) {
            ++left;
        }
        if (left != right) {
            mas[right][0] = mas[left][0];
            mas[right][1] = mas[left][1];
            --right;
        }
    }
    mas[left][0] = pivotkey;
    mas[left][1] = pivotvalue;
    pivotkey = left;
    left = leftborder;
    right = rightborder;
    if (left < pivotkey) {
        QuickSort(mas, left, pivotkey - 1);
    }
    if (right > pivotkey) {
        QuickSort(mas, pivotkey + 1, right);
    }
}

void BinarySearch(int mas[][2], int count, int key) {
    int left = 0;
    int right = count - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (key == mas[mid][0]) {
            printf("The value is: %d\n", mas[mid][1]);
            return;
        }
        if (key < mas[mid][0]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    printf("There is no such key!\n");
    return;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int mas[n][2];
    printf("Enter the keys and numbers\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &mas[i][0], &mas[i][1]);
    }
    printf("\n");
    PrintTable(mas, n);
    printf("\n");
    QuickSort(mas, 0, n - 1);
    printf("\n");
    PrintTable(mas, n);
    printf("\n");
    int flag = 1;
    printf("1. Find value by key, 2. Quit\n");
    while (flag) {
        int variant, key;
        printf("Enter the variant: ");
        scanf("%d", &variant);
        if (variant == 1) {
            printf("Enter the key value: ");
            scanf("%d", &key);
            BinarySearch(mas, n, key);
        } else if (variant == 2) {
            printf("Work finished\n");
            flag = 0; 
        }
    }
    return 0;
}