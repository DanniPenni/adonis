//
// Created by Daniel Al-Zgul on 08/09/2025.
//
#include <sys/ioctl.h>

#ifndef ADONIS_DRAWING_H
#define ADONIS_DRAWING_H

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#define ESC "\033"
#define CORNER "+"
#define HORIZ '-'
#define VERTICAL "|"

struct cursor {
    int line;
    int col;
};

struct gui_window {
    int x_start;
    int y_start;
    int width;
    int height;
};
typedef struct gui_window gui_window;

struct cursor Cursor;
struct winsize global_win;
int t_width;
int t_height;

int fsleep(float sec);
void clrscr();
int init_gui();
int draw_window(gui_window w);
int printstr(char * str, int chars, int line);
int prints(char * str);
void cursor_to(int lines, int chars);

#endif //ADONIS_DRAWING_H