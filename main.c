#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char type[2];
    int numColumns;
    int numRows;
    int maxGray;
    int **mat;
} t_pgmImage;

int **allocMatrix( int rows, int columns)
{
    int **mat = (int**) malloc(sizeof(int*) * rows);
    for (int i=0; i<rows; ++i)
    {
    mat[i] = (int*)malloc(sizeof(int) * columns);
    }
    return mat;
}

void freeMatrix(int **mat, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

int **RLE_encoding(int **mat, int columns, int rows, const char *output_file, int maxGray) 
{ 
    FILE * outputFileName = fopen(output_file, "w");
    if(outputFileName == NULL)
    {
        printf("Failed to load output file");
        return 0;
    }

    fprintf(outputFileName, "P8\n");
    fprintf(outputFileName, "%d ", columns);
    fprintf(outputFileName, "%d\n", rows);
    fprintf(outputFileName, "%d\n", maxGray);
    int *line = (int*) malloc(sizeof(int*) * columns);
    memset(line, 0, sizeof(int) * columns);
    int currentValue, count;
    int j=0;
    for (int i = 0; i < rows; i++) {
            currentValue = mat[i][j]; 
            count = 1; 
            for (j = 1; j < columns; j++) {
                if (mat[i][j] == currentValue) {
                    count++;
                } else {
                    fprintf(outputFileName, "@%d %d", currentValue, count);
                    currentValue = mat[i][j];
                    count = 1;
                }
            }
            fprintf(outputFileName, "@%d %d",currentValue, count);
            fprintf(outputFileName, "\n");
        }
    fclose(outputFileName);
    free(line);
    return mat;
}

int file_compression(const char *to_RLE_file, const char* output_RLE_file)
 {
    FILE * inputFileName = fopen(to_RLE_file, "r+");
    if(inputFileName == NULL)
    {
        printf("Failed to load input file");
        return 0;
    }

    t_pgmImage *image_info = (t_pgmImage *) malloc(sizeof(t_pgmImage));
    fscanf(inputFileName, "%c", &image_info[0].type[0]);
    fscanf(inputFileName, "%c", &image_info[0].type[1]);
    fscanf(inputFileName, "%d", &image_info[0].numColumns);
    fscanf(inputFileName, "%d", &image_info[0].numRows);
    fscanf(inputFileName, "%d", &image_info[0].maxGray);

    image_info->mat = allocMatrix(image_info->numRows, image_info->numColumns);

    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            fscanf(inputFileName, "%d", &image_info->mat[i][j]);
        }
    }
    RLE_encoding(image_info->mat, image_info->numColumns, image_info->numRows, output_RLE_file, image_info->maxGray);
    fclose(inputFileName);
    freeMatrix(image_info->mat, image_info->numRows);
    return 1;
 }

void RLE_decoding(int **mat, int columns, int rows, const char * output_file) {
    //add **RLE_decoding
}

void file_decompression(const char *to_PGM_file, const char* output_PGM_file) {

}

int main() {
// int argc, char *argv[]

    //file_compression(argv[1], argv[2]);
    file_compression("ex1.pgm", "outputTest.pgmc");
    //file_decompression("outputv2.pgmc", "out21.pgm");

    return 0;
}