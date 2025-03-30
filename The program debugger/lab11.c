// #include <stdio.h>
// #include <stdlib.h>

// void init(int** arr, int n){
//     int i;
//     *arr=malloc(n * sizeof(int));
//     for (int i = 0; i < n; i++) {
//         (*arr)[i] = i;
//     }
// }

// int main(){
//     int *arr=NULL;
//     int n = 10;
//     init(&arr, n);
//     for (int i = 0; i < n; i++) {
//         printf("%d\n", arr[i]);
//     }
//     printf("%ls",arr);
//     return 0;
// }

// #include <stdio.h>
// typedef struct{
//     char str[5];
//     int num;
// } NumberRepr;

// void format(NumberRepr* number){
//     sprintf(number->str, "%d", number->num);
// }


// int main(){
//     NumberRepr number = { .num = 1025 };
//     format(&number);
//     printf("str: %s\n", number.str);
//     printf("num: %d\n", number.num);
//     return 0;
// }

// #include <stdio.h>
// #define SQR(x) ((x) * (x))

// int main() {
//     int y = 5;
//     int z = SQR(y + 1);
//     printf("z = %d\n", z);
//     return 0;
// }

// #include <stdio.h>
// void swap(int* a, int* b){
//     int tmp = *a;
//     *a = *b;
//     *b = tmp;
// }
// void bubble_sort(int* array, int size){
//     int i, j;
//     for (i = 0; i < size - 1; i++) { 
//         for (j = 0; j < size - i - 1; j++) { //
//             if (array[j] > array[j + 1]) {
//                 swap(&array[j], &array[j + 1]);
//             }
//         }
//     }
// }
// int main() {
//     int array[100] = {10, 15, 5, 4, 21, 7};
//     bubble_sort(array, 6);
//     int i;
//     for (i = 0; i < 6 ; ++i) {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
//     return 0;
// }