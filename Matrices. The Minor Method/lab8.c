#include <stdio.h>
#include <math.h>

void print_matrix(int n, double matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}


void getMinor(int len, int j, double matr[len][len], double newMatr[len-1][len-1]){
    for (int x = 1; x < len; x++) {
        int new_y = 0;
        for (int y = 0; y < len; y++) {
            if (y != j) {
                newMatr[x-1][new_y] = matr[x][y];
                new_y++;
            }
        }
    }
}

double decision_matrix(int n, double matrix[n][n]){
    if (n == 1) {
        return matrix[0][0];
    }

    double sum = 0;

    for (int i = 0; i < n; i++) {
        int size = n - 1;
        double newMatr[size][size]; 
        
        getMinor(n, i, matrix, newMatr);
        sum += pow(-1, i) * matrix[0][i] * decision_matrix(size, newMatr);
    }
    return sum;
}

void copyMatrix(int len, double src[len][len], double dest[len][len]){
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            dest[i][j] = src[i][j];
        }
    }
}



int main() {
    int n;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);

    double matrix[n][n],array_answer[n];
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    printf("Исходная матрица:\n");
    print_matrix(n, matrix);

    double determinant = decision_matrix(n, matrix);
    printf("Определитель матрицы: %f\n", determinant);
    
    printf("Столбец свободных членов: ");
    for (int i = 0; i < n; i++) {
        scanf("%lf", &array_answer[i]);
    }
    
    double matrix_answer[n][n], answer;
    for (int j=0; j<n; j++){
        copyMatrix(n, matrix, matrix_answer);
        for (int i = 0; i < n; i++) {
            matrix_answer[i][j] = array_answer[i];
        }

        answer=decision_matrix(n, matrix_answer)/determinant;
        printf("x = %lf; ", answer);
    }
}
