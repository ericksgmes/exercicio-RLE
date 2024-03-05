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

int **allocMatrix( int rows, int columns, size_t sizeOfType)
{
    int **mat = malloc(sizeof(void *) * rows);
    for (int i=0; i<rows; ++i)
    {
    mat[i] = malloc(sizeOfType * columns);
    }
    return mat;
}

void freeMatrix(void **mat, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        free(mat[i]);
    }
    free(mat);
}

int **RLE_encoding(const char *output_file, t_pgmImage * image) 
{ 
    FILE * outputFileName = fopen(output_file, "w");
    if(outputFileName == NULL)
    {
        printf("Failed to load output file");
        return 0;
    }

    fprintf(outputFileName, "P8\n");
    fprintf(outputFileName, "%d ", image->numColumns);
    fprintf(outputFileName, "%d\n", image->numRows);
    fprintf(outputFileName, "%d\n", image->maxGray);
    int *line = (int*) malloc(sizeof(int*) * image->numColumns);
    memset(line, 0, sizeof(int) * image->numColumns);
    int currentValue, count;
    int j=0;
    for (int i = 0; i < image->numRows; i++) {
            currentValue = image->mat[i][j]; 
            count = 1; 
            for (j = 1; j < image->numColumns; j++) {
                if (image->mat[i][j] == currentValue) {
                    count++;
                } else {
                    fprintf(outputFileName, "@%d %d", currentValue, count);
                    currentValue = image->mat[i][j];
                    count = 1;
                }
            }
            fprintf(outputFileName, "@%d %d",currentValue, count);
            fprintf(outputFileName, "\n");
        }
    fclose(outputFileName);
    free(line);
    return image->mat;
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
    fscanf(inputFileName, "%2s", image_info->type);
    fscanf(inputFileName, "%d", &image_info->numColumns);
    fscanf(inputFileName, "%d", &image_info->numRows);
    fscanf(inputFileName, "%d", &image_info->maxGray);

    image_info->mat = allocMatrix(image_info->numRows, image_info->numColumns, sizeof(int));

    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            fscanf(inputFileName, "%d", &image_info->mat[i][j]);
        }
    }
    RLE_encoding(output_RLE_file, image_info);
    fclose(inputFileName);
    freeMatrix((void **)image_info->mat, image_info->numRows);
    return 1;
 }

int file_decompression(const char *to_PGM_file, const char* output_PGM_file) {
    FILE * inputFileName = fopen(to_PGM_file, "r+");
    if(inputFileName == NULL)
    {
        printf("Failed to load input file");
        return 0;
    }

    t_pgmImage *image_info = (t_pgmImage *) malloc(sizeof(t_pgmImage));
    fscanf(inputFileName, "%2s", image_info->type);
    fscanf(inputFileName, "%d", &image_info->numColumns);
    fscanf(inputFileName, "%d", &image_info->numRows);
    fscanf(inputFileName, "%d", &image_info->maxGray);

    image_info->mat = allocMatrix(image_info->numRows, image_info->numColumns, sizeof(int));
    
    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            char pixel;
            fscanf(inputFileName, " %c", &pixel);
            if(pixel == '@') fscanf(inputFileName, "%d", &image_info->mat[i][j]);
        }
    }
    
    printf("%s\n", image_info->type);
    printf("%d\n", image_info->numColumns);
    printf("%d ", image_info->numRows);
    printf("%d\n", image_info->maxGray);

    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            int d = image_info->mat[i][j];
            printf("%d", d);
        }
    }

    //RLE_encoding(output_PGM_file, image_info);
    fclose(inputFileName);
    freeMatrix((void **)image_info->mat, image_info->numRows);
    return 1;
}

int main() {
// int argc, char *argv[]

    //file_compression(argv[1], argv[2]);
    file_compression("ex2.pgm", "TEST.pgmc");
    //file_decompression("TEST.pgmc", "out21.pgm");

    return 0;
}