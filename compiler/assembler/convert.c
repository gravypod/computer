//
// Created by gravypod on 10/5/17.
//

#include <memory.h>
#include <limits.h>

#include "convert.h"

char *make_binary_string_for(unsigned char c) {
    static const char one = '1';
    static const char zero = '0';
    static char binary[CHAR_BIT + 1];

    // Clear
    memset(binary, 0, CHAR_BIT + 1);

    char mask = 1;
    for (size_t i = 1; i <= CHAR_BIT; i++) {
        binary[CHAR_BIT - i] = (c & mask) ? one : zero;
        mask <<= 1;
    }

    return binary;
}