//
// Created by Daniel Al-Zgul on 08/09/2025.
//

#include "GUI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

#define ESC "\033"
#define CORNER "+"
#define HORIZ '-'
#define VERTICAL "|"

void clrscr();
int fsleep(float sec);

struct cursor {
    int line;
    int col;
};

struct cursor Cursor;

struct winsize global_win;

void update_winsize() {
    ioctl(STDIN_FILENO, TIOCGWINSZ, &global_win);
    fsleep(0.1);
}

void window_resize(int sig) {
    update_winsize();
}

struct gui_window {
    int x_start;
    int y_start;
    int width;
    int length;
};
typedef struct gui_window gui_window;

int MAXLINES = 300;
int MAXCOLS = 100;

// Clear the screen, sys-independent.
void clrscr() {
    system(CLEAR);
}

// Sleep for sec seconds.
int fsleep(float sec) {
    struct timespec ts;
    int res;

    ts.tv_sec = (long) sec;
    ts.tv_nsec = (long) (sec * 1000000000L) % 1000000000L;
    res = nanosleep(&ts, NULL);
    return res;
}

void cursor_to(int lines, int chars) {
    Cursor.line = lines;
    Cursor.col = chars;
    printf(ESC "[%d;%dH", lines, chars);
}

void move_cursor(int dlines, int dchars) {
    int newline = Cursor.line + dlines;
    if (newline < 0) newline = 0; else if (newline > MAXLINES) newline = MAXLINES;
    int newcol = Cursor.col + dchars;
    if (newcol < 0) newcol = 0; else if (newcol > MAXCOLS) newcol = MAXCOLS;

    cursor_to(newline, newcol);
}

void horiz_border(int len) {
    char * border = malloc(len * sizeof(char));
    memset(border, HORIZ, len);
    printf("%s", border);
    free(border);

    Cursor.col += len;
}

void vert_border(int len) {
    for(int i = 0; i < len; i++) {
        printf(VERTICAL "\n");
        Cursor.line += 1;
        cursor_to(Cursor.line, Cursor.col);
    }
}

int prints(char * str) {
    Cursor.col += strlen(str);
    return printf("%s", str);
}

void draw_window(gui_window w) {
    cursor_to(w.y_start, w.x_start);
    prints(CORNER);
    horiz_border(w.width-2);

    cursor_to(w.y_start+1, w.x_start);
    vert_border(w.length-2);
    prints(CORNER);

    horiz_border(w.width-2);
    cursor_to(w.y_start, w.x_start+w.width-1);
    prints(CORNER);

    move_cursor(1, -1);
    vert_border(w.length-2);
    prints(CORNER);
}

int init_gui() {
    clrscr();
    setbuf(stdout, NULL);

    struct sigaction act;
    act.sa_handler = &window_resize;
    act.sa_flags = 0;
    if (sigaction(SIGWINCH, &act, NULL) == -1) {
        perror("sigaction");
    }
    return 0;
}

int draw_gui() {
    gui_window w = {20, 20, 5, 5};
    draw_window(w);
    fsleep(100);
    clrscr();
    return 0;
}