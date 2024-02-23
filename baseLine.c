#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int p2parap8(const char * inputfile, const char * outputfile)
{
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

    int height, width, maxval;
    char buffer[MAX_LINE_LENGTH];

    while (fgets(buffer, MAX_LINE_LENGTH, inputFileName))
    {
        fprintf(outputfile, "%s", buffer);
    }

    fclose(inputFileName);
    fclose(outputFileName);
}