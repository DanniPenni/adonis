// The functions that facilitate drawing inside of the terminal.

#include "drawing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

// Clear the screen, sys-independent.
void clrscr() {
    system(CLEAR);
}

// Sleep for sec seconds.
int fsleep(float sec) {
    struct timespec ts;

    ts.tv_sec = (long) sec;
    ts.tv_nsec = (long) (sec * 1000000000L) % 1000000000L;
    return nanosleep(&ts, NULL);
}

void update_winsize(int sig) {
    ioctl(STDIN_FILENO, TIOCGWINSZ, &global_win);
    t_width = global_win.ws_col;
    t_height = global_win.ws_row;
    fsleep(0.15);
}

void draw_error(char * func) {
    clrscr();
    fprintf(stderr, "Drawing out of bounds at: %s. Cursor at: %d %d\n", func, Cursor.line, Cursor.col);
    exit(EXIT_FAILURE);
}

void cursor_to(int lines, int chars) {
    Cursor.line = lines;
    Cursor.col = chars;
    printf(ESC "[%d;%dH", lines, chars);
}

int move_cursor(int dlines, int dchars) {
    int newline = Cursor.line + dlines;
    int newcol = Cursor.col + dchars;
    if (newline < 0 || newline > global_win.ws_row || newcol < 0 || newcol > global_win.ws_col) {
        draw_error("move_cursor");
    }

    cursor_to(newline, newcol);
    return 0;
}

void horiz_border(int len) {
    Cursor.col += len;
    if (Cursor.col > global_win.ws_col) {
        draw_error("horiz_border");
    }

    char * border = malloc(len * sizeof(char));
    memset(border, HORIZ, len);
    printf("%s", border);
    free(border);
}

void vert_border(int len) {
    if (Cursor.line + len > global_win.ws_row) {
        draw_error("vert_border");
    }

    for(int i = 0; i < len; i++) {
        printf(VERTICAL "\n");
        Cursor.line += 1;
        cursor_to(Cursor.line, Cursor.col);
    }
}

int prints(char * str) {
    Cursor.col += strlen(str);

    if (Cursor.col > global_win.ws_col) {
        fprintf(stderr, "Drawing out of bounds\n.");
        exit(EXIT_FAILURE);
    }

    return printf("%s", str);
}

int printstr(char * str, int chars, int line) {
    cursor_to(line, chars);
    return prints(str);
}

int draw_window(gui_window w) {
    cursor_to(w.y_start, w.x_start);
    prints(CORNER);
    horiz_border(w.width-2);

    cursor_to(w.y_start+1, w.x_start);
    vert_border(w.height-2);
    prints(CORNER);

    horiz_border(w.width-2);
    cursor_to(w.y_start, w.x_start+w.width-1);
    prints(CORNER);

    move_cursor(1, -1);
    vert_border(w.height-2);
    prints(CORNER);

    return 0;
}

int init_gui() {
    clrscr();
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    update_winsize(SIGWINCH);

    struct sigaction act;
    act.sa_handler = &update_winsize;
    act.sa_flags = 0;
    if (sigaction(SIGWINCH, &act, NULL) == -1) {
        perror("sigaction");
    }
    return 0;
}