#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <encrypted_file> <original_file>\n", argv[0]);
        return 1;
    }

    int rows, cols;
    printf("Rows: ");
    scanf("%d", &rows);
    printf("Cols: ");
    scanf("%d", &cols);

    FILE *encryptedFile = fopen(argv[1], "r");
    fseek(encryptedFile, 0, SEEK_END);
    long encSize = ftell(encryptedFile);
    fseek(encryptedFile, 0, SEEK_SET);

    char *encrypted = (char*)malloc(encSize + 1);
    fread(encrypted, 1, encSize, encryptedFile);
    encrypted[encSize] = '\0';
    fclose(encryptedFile);

    FILE *originalFile = fopen(argv[2], "r");
    fseek(originalFile, 0, SEEK_END);
    long origSize = ftell(originalFile);
    fseek(originalFile, 0, SEEK_SET);

    char *original = (char*)malloc(origSize + 1);
    fread(original, 1, origSize, originalFile);
    original[origSize] = '\0';
    fclose(originalFile);

    char *decrypted = (char*)malloc(rows * cols + 1);
    decrypt(encrypted, decrypted, rows, cols);

    printf("Decrypted: %s\n", decrypted);
    printf("Original:  %s\n", original);
    printf("Match: %s\n", verify(decrypted, original) ? "Yes" : "No");

    free(encrypted);
    free(original);
    free(decrypted);
    return 0;
}