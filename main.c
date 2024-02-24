#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

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

int main() {
    const char *input_filename = "ex1.pgm";
    const char *output_filename = "output.txt";

    PDMtoTXT(input_filename, output_filename);

    printf("Conversion successful.\n");

    return 0;
}
