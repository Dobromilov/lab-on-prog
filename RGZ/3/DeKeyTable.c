#include <stdio.h>
#include <string.h>
#include "mylib.h"

int main() {
    char cipher[100], text[100], check[100];
    
    printf("Введите шифр: ");
    fgets(cipher, 100, stdin);
    cipher[strcspn(cipher, "\n")] = 0;
    
    decrypt(cipher, text);
    printf("Текст: %s\n", text);
    
    printf("Введите оригинал: ");
    fgets(check, 100, stdin);
    check[strcspn(check, "\n")] = 0; // Удаляем \n
    
    if(verify(text, check)) {
        printf("Тексты совпадают!\n");
    } else {
        printf("Тексты не совпадают!\n");
    }

    return 0;
}