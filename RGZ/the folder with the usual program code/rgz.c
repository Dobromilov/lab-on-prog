#include <stdio.h>
#include <string.h>

#define ROWS 4
#define COLS 6

void replace(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = '_';
        }
    }
}

void print_cipher(const char matrix[ROWS][COLS]) {
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            printf("%c", matrix[row][col]);
        }
    }
    printf("\n");
}

int main() {
    char input[ROWS * COLS + 1];
    fgets(input, sizeof(input), stdin);

    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
        length--;
    }

    replace(input);

    char table[ROWS][COLS];
    int index = 0;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (index < length) {
                table[row][col] = input[index++];
            } else {
                table[row][col] = '_';
            }
        }
    }

    print_cipher(table);

    return 0;
}