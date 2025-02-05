#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "compress.h"


// compress function
void compress(int len, char str[]);
// turn binary string into base 10 numbers and print the result
void baseTen(int len, char biStr[]);

/*
 * Compress.
 */
void compress(int len, char str[]) {
    int biStrLen = 0;
    // make the length for the binary string
    if (len % 4 == 0) {// when the length is the factor of 4
        biStrLen = len * 2;
    } else { // when the length is not the factor of 4
        biStrLen = (len - (len % 4) + 4) * 2;
    } // else
    // bi
    char biStr[biStrLen + 1];
    // turn an alphabetical char into 2 binary chars
    // add binary inputs from the index 0
    for (int i = 0; i < biStrLen / 2; i++) {
        if (i < len) {
            if (str[i] == 'T') {// case it's T
                biStr[i * 2] = '0';
                biStr[i * 2 + 1] = '1';
            } else if (str[i] == 'C') { // case it's C
                biStr[i * 2] = '1';
                biStr[i * 2 + 1] = '0';
            } else if (str[i] == 'G') { // case it's G
                biStr[i * 2] = '1';
                biStr[i * 2 + 1] = '1';
            } else { // case it's A
                biStr[i * 2] = '0';
                biStr[i * 2 + 1] = '0';
            } // else
        } else { // add trailing 0's
            biStr[i * 2] = '0';
            biStr[i * 2 + 1] = '0';
        } // else

    } // for
    biStr[biStrLen] = '\0';
    // call function to do summation and print results
    baseTen(len, biStr);
} // compress

void baseTen(int len, char biStr[]) {
    int group = strlen(biStr) >> 3;// right shift 3 to divide 8
    // print the len of the original character-based string
    printf("%d ", len);
    // loop through all the number of groups
    for (int i = 0; i < group; i++) {
        int sum = 0;
        // summation of each 8-bit group; loop  to sum all 8 elements of the group
        for (int index = i * 8; index < i * 8 + 8; index++) {
            sum = (sum << 1) | (biStr[index] - '0'); // left shifting to mutiply by 2 and OR to add the bit
        } // for
        // print summation of each 8-bit group
        printf("%d ", sum);
    } // for
    printf("\n");
} // baseTen
