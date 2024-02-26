#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

void RLE(char *input, int length, FILE *outputFile) {
}

int PDMtoTXT(const char *inputfile, const char *outputfile) {
    FILE * inputFileName = fopen(inputfile, "r");
    if (inputFileName == NULL) {
        printf("Error opening input file");
        return 0;
    }

    FILE *outputFileName = fopen(outputfile, "wb");
    if (outputFileName == NULL) {
        printf("Error opening output file");
        return 0;
    }

    int height, width, maxval, aux;
    char buffer[MAX_LINE_LENGTH];
    aux=0;
    while (fgets(buffer, MAX_LINE_LENGTH, inputFileName))
    { 
        aux++;
        if(aux > 3){
            fprintf(outputFileName, "%s", buffer);
        }
    }

    fclose(inputFileName);
    fclose(outputFileName);
    return 1;
}

int TXTtoRLE(const char* TxtFileName) {
        FILE *inputFile = fopen(TxtFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 0;
    }

    FILE *outputFile = fopen("output23.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 0;
    }

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, inputFile)) {
        int actual_lenght = strlen(buffer);
        RLE(buffer, actual_lenght, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 1;
}

int main() {
    const char *input_filename = "ex1.pgm";
    const char *output_filename = "output.txt";

    PDMtoTXT(input_filename, output_filename);
    TXTtoRLE(output_filename);
    printf("Conversion successful.\n");

    return 0;
}
