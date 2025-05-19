#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int rows, cols;
    printf("Rows: ");
    scanf("%d", &rows);
    printf("Cols: ");
    scanf("%d", &cols);

    FILE *input = fopen(argv[1], "r");
    fseek(input, 0, SEEK_END); //перешли в конец
    long size = ftell(input);  //узнали размер
    fseek(input, 0, SEEK_SET); //вернулись в начало

    char *text = (char*)malloc(size + 1);
    fread(text, 1, size, input);
    text[size] = '\0';
    fclose(input);

    char *encrypted = (char*)malloc(rows * cols + 1);
    encrypt(text, encrypted, rows, cols);

    FILE *output = fopen(argv[2], "w");
    fputs(encrypted, output);
    fclose(output);

    free(text);
    free(encrypted);
    return 0;
}