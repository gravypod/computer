//
// Created by gravypod on 10/5/17.
//

#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "convert.h"

#include "arguments.h"

bool is_number(const char *token) {
    while (*token)
        if (!isdigit(*(token++)))
            return false;
    return true;
}

bool is_register(const char *token) {
    if (token[0] != 'r')
        return false;
    return is_number(token + 1);
}

char *convert_literal(const char *c) {

    if (!is_number(c))
        return NULL;

    int value = atoi(c);

    if (value < CHAR_MIN || value > UCHAR_MAX)
        return NULL;

    return make_binary_string_for((unsigned char) value);
}

char *convert_register(const char *c) {
    if (!is_register(c))
        return NULL;

    int value = atoi(c + 1);

    if (value < CHAR_MIN || value > UCHAR_MAX)
        return NULL;

    return make_binary_string_for((unsigned char) value);
}

char *convert_argument(const char *c, size_t argument_type) {
    char *(*binary_converters[])(const char *) ={
            &convert_literal,
            &convert_register
    };
    size_t num_binary_converters = sizeof(binary_converters) / sizeof(char *(*)(const char *));
    if (argument_type > num_binary_converters) {
        return NULL;
    }
    return binary_converters[argument_type](c);
}
