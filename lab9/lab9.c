#include <stdio.h>
#include <stdlib.h>

void print_matrix(int x, int y, int **matrix) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

//Получение матрицы D[m,n]
void the_product_of_matrices(int **matrix_B, int **matrix_E, int m, int n, int k, int **matrix_D) {
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            matrix_D[x][y] = 0; 
            for (int z = 0; z < k; z++) {
                matrix_D[x][y] += matrix_B[x][z] * matrix_E[z][y];
            }
        }
    }
}

//Поиск максимальной отрицательной суммы в столбцах и вычисление индекса этого столбца
int find_column_with_max_negative_sum(int **matrix, int m, int n) {
    int max_sum = 1000000; 
    int column_index = -1; 
    
    for (int j = 0; j < n; j++) { 
        int sum = 0;
        int has_negative = 0; 
        for (int i = 0; i < m; i++) {
            if (matrix[i][j] < 0) { 
                sum += matrix[i][j];
                has_negative = 1; 
            }
        }
        if (has_negative && sum < max_sum) {
            max_sum = sum;
            column_index = j;
        }
    }
    if (column_index != -1) {
        printf("Столбец с максимальной суммой отрицательных элементов: %d\n", column_index + 1);
        printf("Сумма отрицательных элементов этого столбца: %d\n", max_sum);
    } else {
        printf("В матрице нет отрицательных элементов.\n");
    }

    return column_index;
}


//Сортировка bubble_sort по полученному столбцу
void bubble_sort(int **matrix_D, int m, int column_index) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - i - 1; j++) {
            if (matrix_D[j][column_index] < matrix_D[j + 1][column_index]) {
                int temp = matrix_D[j][column_index];
                matrix_D[j][column_index] = matrix_D[j + 1][column_index];
                matrix_D[j + 1][column_index] = temp;
            }
        }
    }
}

int main() {
    int m, n, k, option, min, max;
    printf("Введите размеры матриц m, n, k: ");
    scanf("%d %d %d", &m, &n, &k);
    if (n<=0 || m<=0 || k<=0 || n>15 || m>15 || k>15){
        printf("error..");
        return 1;
    }
    printf("Заполняешь сам или рандомно? (0 V 1): ");
    if (scanf("%d", &option) != 1) {
            printf("error..\n");
            return 1;
    }
    if (option == 1) {
    printf("Введите диапазон рандома(min max): ");
    if (scanf("%d %d", &min, &max) != 2) {
        printf("error..\n");
        return 1;
    }
    if (min > max) {
        printf("Ошибка: min не может быть больше max.\n");
        return 1;
    }
}
    
    
    int **matrix_B = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix_B[i] = (int *)malloc(k * sizeof(int));
    }
    printf("Введите элементы матрицы B (размер %dx%d):\n", m, k);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            if (option==0){
                scanf("%d", &matrix_B[i][j]);
            } else {
                matrix_B[i][j]=min + rand() % (max - min + 1);
            }
        }
    }
    if (option==1){
        print_matrix(m, k, matrix_B);
    }
    
    int **matrix_E = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++) {
        matrix_E[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Введите элементы матрицы E (размер %dx%d):\n", k, n);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            if (option==0){
                scanf("%d", &matrix_E[i][j]);
            } else {
                matrix_E[i][j]=min + rand() % (max - min + 1);
            }
        }
    }
    if (option==1){
        print_matrix(k, n, matrix_E);
    }
    
    int **matrix_D = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix_D[i] = (int *)malloc(n * sizeof(int));
    }
    
    
    the_product_of_matrices(matrix_B, matrix_E, m, n, k, matrix_D);
    printf("Результирующая матрица D (размер %dx%d):\n", m, n);
    print_matrix(m, n, matrix_D);
    
    int index=find_column_with_max_negative_sum(matrix_D, m, n);
    bubble_sort(matrix_D,m,index);
    print_matrix(m, n, matrix_D);
    
    // Освобождаем память
    for (int i = 0; i < m; i++) free(matrix_B[i]);
    free(matrix_B);

    for (int i = 0; i < k; i++) free(matrix_E[i]);
    free(matrix_E);

    for (int i = 0; i < m; i++) free(matrix_D[i]);
    free(matrix_D);
    return 0;
}