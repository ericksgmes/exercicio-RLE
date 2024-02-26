#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

void RLE(char *input, int length, FILE *outputFile) {
    int count;
    
    for (int i = 0; i < length; i++) {
        fputc(input[i], outputFile);
        count = 1;
        while (i + 1 < length && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        fprintf(outputFile, "%d", count);
    }
}

int TXTtoRLE(const char* TxtFileName) {
    FILE *inputFile = fopen(TxtFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 0;
    }

    FILE *outputFile = fopen("output.pdma", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, inputFile)) {
        RLE(buffer, strlen(buffer), outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 1;
}

int main() {
    const char *input_filename = "output.txt";

    if (TXTtoRLE(input_filename)) {
        printf("Conversion successful.\n");
    } else {
        printf("Conversion failed.\n");
    }

    return 0;
}
