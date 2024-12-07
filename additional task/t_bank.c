// #include <stdio.h>
// #include <math.h>


// int is_prime(int x) {
//     if (x < 2) return 0; 
//     for (int i = 2; i <= sqrt(x); i++) {
//         if (x % i == 0) {
//             return 0; // Найден делитель, число не простое
//         }
//     }
//     return 1; // Простое число
// }


// int search_for_composite_with_prime_divisors(int x) {
//     int count = 0;
//     for (int i = 1; i <= x; i++) { // Подсчёт делителей числа x
//         if (x % i == 0) {
//             count++;
//         }
//     }
//     if (count > 2 && is_prime(count)) { // Проверяем, что число составное и количество делителей простое
//         return 1;
//     }
//     return 0;
// }

// int main() {
//     int start, end;
//     scanf("%d %d", &start, &end);

//     int count = 0; 
//     for (int i = start; i <= end; i++) { 
//         if (search_for_composite_with_prime_divisors(i)) {
//             count++;
//             printf("%d \n",i);
//         }
//     }

//     printf("%d\n", count); 
//     return 0;
// }


//-------------------------------------------------------------------------------



//Теория 
    //Создание строки
    // char str[100];
    // char *ptr="Hello, World!";
    // printf("%s",ptr);
    //-------------------------------
    //Ввод строки (считывает строку без пробелов)
    //1)
    // char str[100];
    // scanf("%s",&str);
    // printf("%s",str);
    //-------------------------------
    //2) (считывает строку с пробелами fgets)
    // char str[100];
    // fgets(str,sizeof(str),stdin); //(указатель на массив символов, максимальное кол-во символов, поток из которого считывается строка(stdin-стандарт))
    // printf("%s",str);
    //-------------------------------
    // Длина строки
    // char str[]="Hello";
    // printf("%d",strlen(str));
    //-------------------------------
    // Копирование строки (strcpy)
    // char str1[]="Hello";
    // char str2[100];
    // strcpy(str2,str1);
    // printf("%s",str2);
    //-------------------------------
    // Сравнение строк (strcmp)
    //Возвращает 0, если строки равны.
    //Отрицательное значение, если первая строка меньше второй.
    //Положительное значение, если первая строка больше второй.
    // char str1[]="Hello";
    // char str2[]="World";
    // if (strcmp(str1,str2)==0){
    //     printf("равны\n");
    // } else {
    //     printf("не равны\n");
    // }
    //-------------------------------
    // Разделение строки (strtok - токены(возвращает указатели на подстроки, разделенные символом разделителем))
        //char *strtok(char *str, const char *delim);
    //Как работает strtok
    //На первом вызове функция принимает строку и ищет первый токен — часть строки до первого символа-разделителя.
    //Она заменяет разделитель (delim) на нулевой символ ('\0'), чтобы токен стал отдельной строкой.
    //Для продолжения разбиения строки вызывайте strtok с NULL вместо строки.
    // char str[]="1-5,7-8,10";
    // char *token=strtok(str,",");
    // while (token != 0){
    //     printf("%s\n",token);
    //     token = strtok(NULL, ",");
    //}
    //-------------------------------
    // sprintf - форматирование строки
    // char buffer[100];
    // int num = 42;

    // sprintf(buffer, "Число: %d", num);
    // printf("%s\n", buffer);
    //-------------------------------
    // Объединение строк strcat
    // char str1[100]="hello, ";
    // char str2[]="world";
    // strcat (str1,str2); //сохраняем в str1 сумму строк str1+str2
    // printf("%s",str1);
    //-------------------------------
    // Поиск первого вхождения символа в строку strchr
    
    //char *strchr(const char *str, int c);
    
    //str — указатель на строку, в которой нужно искать символ.
    //c — символ, который нужно найти. Передаётся как int, но интерпретируется как символ (обычно передаётся в виде символьной константы.
    //-------------------------------
    // Считывание строки в определенном формате sscanf(). пример sscanf(range, "%d-%d", &start, &end)


// ------------------------------------
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>



// void print_array(int count,int array[count]){
//     for (int i=0; i<count; i++){
//         printf("%d ",array[i]);
//     }
// }



// int main(){
//     char str[100];
//     fgets(str,sizeof(str),stdin);
    
//     int *array = (int *)malloc(strlen(str) * sizeof(int));
//     str[strcspn(str, "\n")] = '\0'; //удаление символа конца строки
    
//     int count=0;
//     char *token=strtok(str,",");
    
//     while (token != NULL){
//         if (strchr(token,'-')!=0){
//             int start,end;
//             sscanf(token,"%d-%d",&start,&end);
//             for (int i=start;i<=end;i++){
//                 array[count]=i;
//                 count++;
//             }
//         } else {
//             array[count]=atoi(token); //char -> int
//             count++;
//         }
//         token = strtok(NULL, ",");
//     }
//     print_array(count,array);
//     free(array);
// }
