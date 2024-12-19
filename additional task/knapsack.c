#include <stdio.h>
#include <stdlib.h>

void print_array(int n, int array[n]) {
    printf("mas: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void bubbleSort(int* num, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = (size - 1); j > i; j--) {
            if (num[j - 1] < num[j]) {
                int temp = num[j - 1];
                num[j - 1] = num[j];
                num[j] = temp;
            }
        }
    }
}


void ptr_index(int** ptr, int* index, int a, int b) {
    (*ptr)[*index] = a + b;
    (*index)++;
}


int check(int max_gold_kg, int* arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] <= max_gold_kg) { // Исправлено: считаем элементы <= max_gold_kg
            count++;
        }
    }
    return count; // Возвращаем количество элементов, которые <= max_gold_kg
}


int main() {
    int max_gold_kg;
    scanf("%d", &max_gold_kg);
    int counter;
    scanf("%d", &counter);
    int gold_bars[counter];
    for (int i = 0; i < counter; i++) {
        scanf("%d", &gold_bars[i]);
    }

    bubbleSort(gold_bars, counter);

    int index = check(max_gold_kg, gold_bars, counter);

    int size = index * index; // Размер массива для всех комбинаций
    int *ptr = malloc(size * sizeof(int));
    int ptr_index_counter = 0; // Используем отдельный счётчик для индексации массива ptr

    for (int i = 0; i < index; i++) {
        for (int j = 0; j < index; j++) {
            if (gold_bars[i] + gold_bars[j] <= max_gold_kg) { // Добавлено условие
                ptr_index(&ptr, &ptr_index_counter, gold_bars[i], gold_bars[j]);
            }
        }
    }

    print_array(counter, gold_bars);

    // Ищем максимальную сумму, которая не превышает max_gold_kg
    int max_sum = 0;
    for (int i = 0; i < ptr_index_counter; i++) {
        if (ptr[i] <= max_gold_kg && ptr[i] > max_sum) {
            max_sum = ptr[i];
        }
    }

    printf("%d\n", max_sum); // Выводим максимальную сумму

    free(ptr); // Освобождаем память
    return 0;
}