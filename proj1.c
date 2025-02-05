#include <stdio.h> // printf
#include <string.h> // strcmp
#include <stdlib.h> // atoi
#include <stdbool.h>
#include "compress.h"
#include "decompress.h"

/*
 * The main function.
 */
int main(int argc, char * argv[]) {
    if (argc >= 3) {
        // compress
        if (strcmp("-c", argv[1]) == 0) {
            compress(strlen(argv[2]), argv[2]);
        } // if
        // decompress
        if (strcmp("-d", argv[1]) == 0) {
            // the total characters
            int charCountTotal = atoi(argv[2]);
            // characters in each group
            int charCountGroup = 4;
            for (int i = 3; i < argc; i++) {
                // when we just have the last remaining characters
                if (i == argc - 1) {
                    decompress(charCountTotal, argv[i]);
                } else {// normal 4-character string
                    decompress(charCountGroup, argv[i]);
                } // else
                // count the remaining characters
                charCountTotal = charCountTotal - 4;
            } // for
            printf("\n");
        } //if
    } // if
    return 0;
} // main
