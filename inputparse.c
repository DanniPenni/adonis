#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "drawing.h"
#include "inputparse.h"

// Non-blocking input inspiration:
// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html


char * read_input() {
    static char input_line[200]; // Change later for more flexibility.
    static int len = 0;

    if (len != 0 && input_line[len - 1] == '\0') {
        len = 0;
    }
    if (len >= INLEN) {
        // Fix later
        fprintf(stderr, "Input longer than %d characters.", INLEN);
        exit(EXIT_FAILURE);
    }

    int ch = getchar();
    if (ch != EOF) {
        input_line[len++] = (char) ch;
    }

    return input_line;
}
