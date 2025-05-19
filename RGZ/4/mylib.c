#include "mylib.h"
#include <string.h>

void encrypt(const char* in, char* out, int rows, int cols) {
    int idx = 0;
    char tmp[rows][cols];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = '_';
            if (idx < strlen(in)) {
                c = in[idx];
                if (c == ' ') c = '_';
            }
            tmp[i][j] = c;
            idx++;
        }
    }
    
    idx = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            out[idx++] = tmp[i][j];
        }
    }
    out[idx] = '\0';
}

void decrypt(const char* in, char* out, int rows, int cols) {
    int idx = 0;
    char tmp[rows][cols];
    
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            char c = in[idx++];
            tmp[i][j] = (c == '_') ? ' ' : c;
        }
    }
    
    idx = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            out[idx++] = tmp[i][j];
        }
    }
    out[idx] = '\0';
}

int verify(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}


// #include "mylib.h"
// #include <stdlib.h>
// #include <string.h>

// void encrypt(const char* input, char* output, int rows, int cols) {
//     int len = strlen(input);
//     int total = rows * cols;
//     char *temp = (char*)malloc(total * sizeof(char));
//     if (!temp) return;

//     int idx = 0;
//     for (int row = 0; row < rows; row++) {
//         for (int col = 0; col < cols; col++) {
//             char current = (idx < len) ? input[idx] : '_';
//             if (current == ' ') current = '_';
//             temp[row * cols + col] = current;
//             idx++;
//         }
//     }

//     idx = 0;
//     for (int col = 0; col < cols; col++) {
//         for (int row = 0; row < rows; row++) {
//             output[idx++] = temp[row * cols + col];
//         }
//     }
//     output[idx] = '\0';
//     free(temp);
// }

// void decrypt(const char* input, char* output, int rows, int cols) {
//     int total = rows * cols;
//     char *temp = (char*)malloc(total * sizeof(char));
//     if (!temp) return;

//     int idx = 0;
//     for (int col = 0; col < cols; col++) {
//         for (int row = 0; row < rows; row++) {
//             char c = input[idx++];
//             temp[row * cols + col] = (c == '_') ? ' ' : c;
//         }
//     }

//     idx = 0;
//     for (int row = 0; row < rows; row++) {
//         for (int col = 0; col < cols; col++) {
//             output[idx++] = temp[row * cols + col];
//         }
//     }
//     output[idx] = '\0';
//     free(temp);
// }

// int verify(const char* a, const char* b) {
//     return strcmp(a, b) == 0;
// }