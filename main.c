#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"

int main(int argc, char *argv[]) {
    (void)argc;
    char *arg = malloc(strlen(argv[1]) + 1);
    if (arg == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    strcpy(arg, argv[1]);
    char *token = strtok(arg, ".");
    if (token == NULL) {
        printf("Invalid file name format\n");
        return 1;
    }
    token = strtok(NULL, ".");
    if (token == NULL) {
        printf("Invalid file name format\n");
        return 1;
    }

    if (strcmp(token, "pgm") == 0) {
        
        file_compression(argv[1], argv[2]);
    } else if (strcmp(token, "pgmc") == 0) {
        file_decompression(argv[1], argv[2]);
    } else {
        printf("Invalid file type\n");
        return 1; // Exit the program with an error code
    }

    return 0;
}