#include <stdio.h>
#include <string.h>
#include "mylib.h"

int main() {
    char text[100], s[100];
    
    printf("Введите текст: ");
    fgets(text, 100, stdin);
    text[strcspn(text, "\n")] = 0; // Удаляем \n
    
    encrypt(text, s);
    printf("Шифр: %s\n", s);
    return 0;
}