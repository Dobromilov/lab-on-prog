#ifndef MYLIB_H
#define MYLIB_H

void encrypt(const char* input, char* output, int rows, int cols);
void decrypt(const char* input, char* output, int rows, int cols);
int verify(const char* a, const char* b);

#endif