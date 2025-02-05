#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "decompress.h"

// decompress
void decompress(int remainingChar, char str[]);

/*
 * Decompress.
 */
void decompress(int remainingChar, char str[]) {
    // new binary string
    char biStr[9];

    int quotient = atoi(str);
    // convert base-10 number into binary string
    for (int i = 7; i >= 0; i--) {
        if (quotient > 0) {
            biStr[i] = quotient % 2 + '0'; // input the string
            quotient = quotient >> 1; // right shift to divide 2
        } else {
            biStr[i] = '0'; // add leading 0's
        } // else
    } // for
    // end string
    biStr[8] = '\0';
    //convert 2 binary chars into a alphabetical char
    //print the characters based on the remaining characters
    for (int i = 0; i < remainingChar; i++) {
        if (biStr[i * 2] == '0' && biStr[i * 2 + 1] == '0') { // when it's 00
            printf("%s", "A");
        } else if (biStr[i * 2] == '0' && biStr[i * 2 + 1] == '1') { // when it's 01
            printf("%s", "T");
        } else if (biStr[i * 2] == '1' && biStr[i * 2 + 1] == '0') { // when it's 10
            printf("%s", "C");
        } else { // when it's 11
            printf("G");
        } // else
    } // for
} // decompress
