#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"

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
        return NULL;
    }

    fprintf(outputFileName, "P8\n");
    fprintf(outputFileName, "%d ", image->numColumns);
    fprintf(outputFileName, "%d\n", image->numRows);
    fprintf(outputFileName, "%d\n", image->maxGray);
    int *line = (int*) malloc(sizeof(int*) * image->numColumns);
    if(line == NULL)
    {
        printf("Failed to allocate memory for line");
        fclose(outputFileName);
        return NULL;
    }
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
                    if (fprintf(outputFileName, "@%d%d", currentValue, count) < 0) {
                        printf("Failed to write to output file");
                        fclose(outputFileName);
                        free(line);
                        return NULL;
                    }
                    currentValue = image->mat[i][j];
                    count = 1;
                }
            }
            if (fprintf(outputFileName, "@%d%d",currentValue, count) < 0) {
                printf("Failed to write to output file");
                fclose(outputFileName);
                free(line);
                return NULL;
            }
            if (fprintf(outputFileName, "\n") < 0) {
                printf("Failed to write to output file");
                fclose(outputFileName);
                free(line);
                return NULL;
            }
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
    if (image_info == NULL)
    {
        printf("Failed to allocate memory for image_info");
        fclose(inputFileName);
        return 0;
    }

    if (fscanf(inputFileName, "%2s", image_info->type) != 1 ||
        fscanf(inputFileName, "%d", &image_info->numColumns) != 1 ||
        fscanf(inputFileName, "%d", &image_info->numRows) != 1 ||
        fscanf(inputFileName, "%d", &image_info->maxGray) != 1)
    {
        printf("Failed to read image information");
        fclose(inputFileName);
        free(image_info);
        return 0;
    }

    image_info->mat = allocMatrix(image_info->numRows, image_info->numColumns, sizeof(int));
    if (image_info->mat == NULL)
    {
        printf("Failed to allocate memory for image matrix");
        fclose(inputFileName);
        free(image_info);
        return 0;
    }

    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            if (fscanf(inputFileName, "%d", &image_info->mat[i][j]) != 1)
            {
                printf("Failed to read pixel value at row %d, column %d", i, j);
                fclose(inputFileName);
                freeMatrix((void **)image_info->mat, image_info->numRows);
                free(image_info);
                return 0;
            }
        }
    }

    RLE_encoding(output_RLE_file, image_info);
    fclose(inputFileName);
    freeMatrix((void **)image_info->mat, image_info->numRows);
    free(image_info);
    return 1;
}

int file_decompression(const char *to_PGM_file, const char* output_PGM_file)
{
    FILE * inputFileName = fopen(to_PGM_file, "r+");
    if(inputFileName == NULL)
    {
        printf("Failed to load input file");
        return 0;
    }

    t_pgmImage *image_info = (t_pgmImage *) malloc(sizeof(t_pgmImage));
    if (image_info == NULL)
    {
        printf("Failed to allocate memory for image_info");
        fclose(inputFileName);
        return 0;
    }

    fscanf(inputFileName, "%2s", image_info->type);
    fscanf(inputFileName, "%d", &image_info->numColumns);
    fscanf(inputFileName, "%d", &image_info->numRows);
    fscanf(inputFileName, "%d", &image_info->maxGray);

    image_info->mat = allocMatrix(image_info->numRows, image_info->numColumns, sizeof(int));
    if (image_info->mat == NULL)
    {
        printf("Failed to allocate memory for image matrix");
        fclose(inputFileName);
        free(image_info);
        return 0;
    }
    
    char line[100];
    fgets(line, sizeof(line), inputFileName); 
    for (int i = 0; i < image_info->numRows; i++) {
        fgets(line, sizeof(line), inputFileName); 
        char *token = strtok(line, "@"); 
        int j = 0;
        while (token != NULL && j < image_info->numColumns) {
            if (strcmp(token, "") != 0) {
                image_info->mat[i][j++] = atoi(token); 
               //printf("%d ", image_info->mat[i][j - 1]);
            }
            token = strtok(NULL, "@"); 
        }
        //printf("\n");
    }

    for(int i = 0; i < image_info->numRows ; i++) {
        for(int j = 0; j < image_info->numColumns; j++) {
            printf("%d ", image_info->mat[i][j]);
        }
        printf("\n");
    }

   // RLE_decoding(output_PGM_file, image_info);
    fclose(inputFileName);
    freeMatrix((void **)image_info->mat, image_info->numRows);
    free(image_info);
    return 1;
}


int ** RLE_decoding(const char *output_file, t_pgmImage * image) 
{ 
    FILE * outputFileName = fopen(output_file, "w");
    if(outputFileName == NULL)
    {
        printf("Failed to load output file");
        return NULL;
    }

    fprintf(outputFileName, "P2\n");
    fprintf(outputFileName, "%d ", image->numColumns);
    fprintf(outputFileName, "%d\n", image->numRows);
    fprintf(outputFileName, "%d\n", image->maxGray);
    int *line = (int*) malloc(sizeof(int*) * image->numColumns);
    if(line == NULL)
    {
        printf("Failed to allocate memory for line");
        fclose(outputFileName);
        return NULL;
    }
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
                    for (int k = 0; k < count; k++) {
                        fprintf(outputFileName, "%d ", currentValue);
                    }
                    currentValue = image->mat[i][j];
                    count = 1;
                }
            }
            for (int k = 0; k < count; k++) {
                fprintf(outputFileName, "%d ", currentValue);
            }
            fprintf(outputFileName, "\n");
        }
    fclose(outputFileName);
    free(line);
    return image->mat;
}
