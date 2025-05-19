#include "mylib.h"
#include <string.h>

#define ROWS 4
#define COLS 6


void encrypt(const char* input, char* output) {
    char temp[ROWS][COLS];
    int idx = 0;
    
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            char current = '_';
            
            if (input[idx] != '\0') {
                if (input[idx] == ' ') {
                    current = '_';
                } else {
                    current = input[idx];
                }
                idx++;
            }
            
            temp[row][col] = current;
        }
    }
    
    idx = 0;
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            output[idx] = temp[row][col];
            idx++;
        }
    }
    output[idx] = '\0';
}

void decrypt(const char* input, char* output) {
    char tmp[ROWS][COLS];
    int idx = 0;
    
    for (int col = 0; col < COLS; col++) {
        for (int row = 0; row < ROWS; row++) {
            if (input[idx] == '_') {
                tmp[row][col] = ' ';
            } else {
                tmp[row][col] = input[idx];
            }
            idx++;
        }
    }
    
    idx = 0;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            output[idx] = tmp[row][col];
            idx++;
        }
    }
    output[idx] = '\0';
}


int verify(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}