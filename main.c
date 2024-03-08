#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"

int main(int argc, char *argv[]) {
    (void)argc;
    //file_compression(argv[1], argv[2]);
    file_decompression(argv[1], argv[2]);
    return 0;
}