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


int main() {
    int two_dimensional_array_len,array_len;
    scanf("%d %d",&two_dimensional_array_len,&array_len);
    int **matrix = (int **)malloc(two_dimensional_array_len * sizeof(int *));
    for (int i = 0; i < two_dimensional_array_len; i++) {
        matrix[i] = (int *)malloc(array_len * sizeof(int));
    }
    
    
    int top=0, bottom=two_dimensional_array_len-1, left=0, right=array_len-1;
    matrix[0][0]=1;
    int count=1;
    while (count <= two_dimensional_array_len * array_len){
        
    // Вправо    
        for (int x = left; x <= right; x++) {
            matrix[top][x] = count;
            count++;
        }
        top++;

    // Вниз
        for (int y = top; y <= bottom; y++) {
            matrix[y][right] = count;
            count++;
        }
        right--;

    // Влево
        if (top <= bottom) {
            for (int x = right; x >= left; x--) {
                matrix[bottom][x] = count;
                count++;
            }
            bottom--;
        }

    // Вверх
        if (left <= right) {
            for (int y = bottom; y >= top; y--) {
                matrix[y][left] = count;
                count++;
            }
            left++;
        }
        
    }
    
    print_matrix(two_dimensional_array_len,array_len,matrix);
    
    for (int i = 0; i < two_dimensional_array_len; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
