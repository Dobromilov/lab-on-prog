#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str){
    int len = strlen(str);
    int x = 0, y = len - 1;
    while (x < y){
        char temp = str[x];
        str[x] = str[y];
        str[y] = temp;
        x++;
        y--;
    }
}

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("Usage: ./a.out file.txt out.txt\n");
        exit(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        perror("Error opening out file");
        fclose(file);
        exit(1);
    }
    
    char line[1000]; 
    while (fgets(line, sizeof(line), file)) {
        reverse(line); // Изменение с file на line
        fprintf(out, "%s", line); // Запись в выходной файл
    }

    fclose(file);
    fclose(out);
    return 0;
}
