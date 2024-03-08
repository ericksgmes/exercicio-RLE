#ifndef RLE_H
#define RLE_H

typedef struct 
{
    char type[2];
    int numColumns;
    int numRows;
    int maxGray;
    int **mat;
} t_pgmImage;

int **allocMatrix(int rows, int columns, size_t sizeOfType);
void freeMatrix(void **mat, int columns);
int **RLE_encoding(const char *output_file, t_pgmImage *image);
int file_compression(const char *to_RLE_file, const char* output_RLE_file);
int file_decompression(const char *to_PGM_file, const char* output_PGM_file);

#endif