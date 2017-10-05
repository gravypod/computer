#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <memory.h>

/**
 * Check to see if a line only contains blank characters.
 * @param line - Line read from stream
 * @param len - Number of bytes in the line
 * @return - True if there is only whitespace in this line
 */
bool is_whitespace(const char *line, ssize_t len) {
    for (int i = 0; i < len; i++) {
        if (!isspace(line[i]))
            return false;
    }
    return true;
}

/**
 * Checks to see if the first non-blank character in this string is a "#" making it a comment line.
 * @param line
 * @param len
 * @return
 */
bool is_comment(const char *line, ssize_t len) {
    for (size_t i = 0; i < len; i++) {
        if (isspace(line[i]))
            continue;
        return line[i] == '#';
    }
    return false;
}

/**
 * Count the number of binary-like digits in a single line.
 * @param line
 * @return
 */
size_t number_of_ones_and_zeros_in(const char *line) {
    size_t total = 0;

    while (*line) {
        const char c = *(line++);

        if (c != '1' && c != '0')
            continue;

        total += 1;
    }
    return total;
}

/**
 * Turn a string of ones and zeros into an unsigned char.
 * @param line
 * @return
 */
unsigned char binary_decode(const char *line) {
    unsigned char byte = 0;

    for (size_t i = 0; i < CHAR_BIT; i++)
        byte = (byte << 1) + (line[i] == '1');

    return byte;
}

int main(int argc, char **argv) {

    char *line = NULL;
    size_t lin_len;
    ssize_t len = 0;
    char binary_string_buffer[CHAR_BIT + 1];

    FILE *out = fopen(argc < 2 ? "program.bin" : argv[1], "wb");

    while ((len = getline(&line, &lin_len, stdin)) > 0) {

        // Clear the buffer
        memset(binary_string_buffer, 0, CHAR_BIT + 1);

        // Check to see if this is a binary character
        if (is_whitespace(line, len) || is_comment(line, len))
            continue;

        if (number_of_ones_and_zeros_in(line) != CHAR_BIT) {
            fprintf(stderr, "ERROR: Line unrecognized ``%s''\n", line);
            exit(1);
        }

        size_t buffer_location = 0;
        for (size_t i = 0; i < len; i++) {
            if (line[i] != '0' && line[i] != '1')
                continue;
            binary_string_buffer[buffer_location++] = line[i];
        }

        const unsigned char byte = binary_decode(binary_string_buffer);
        fwrite(&byte, sizeof(char), 1, out);
    }
    fclose(out);
}
