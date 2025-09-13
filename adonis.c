//
// Created by Dania Al-Zgul on 08/09/2025.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include "drawing.h"

// Code taken from: https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


struct Window {
    int width, height;
} typedef Window;

struct RowNode {
    struct RowNode *parent, *left, *right;
    struct Window* windows;
    int top, bottom, start, end, middle;

} typedef RowNode;

#define INLEN 200
char command[INLEN] = "";
int len = 0;
pthread_mutex_t lock;

void * read_input(void * _) {

    char bufc;
    while (1) {
        read(STDIN_FILENO, &bufc, 1);
        pthread_mutex_lock(&lock);
        if (iscntrl(bufc) && bufc != '\n') {
            if (bufc == 0x03) {
                // Ctrl-C
                pthread_mutex_unlock(&lock);
                pthread_exit(NULL);
            } else if (bufc == 127) {
                // Backspace
                if (len > 0) {
                    command[len-1] = '\0';
                    len--;
                }
            }
        } else {
            command[len] = bufc;
            len++;
        }
        pthread_mutex_unlock(&lock);
    }
}

void * draw_gui(void * _) {
    char last_msg[INLEN] = "";
    char printmsg[INLEN + 2] = "";

    while (1) {
        gui_window logo = {1, 1, t_width-1, 3};
        draw_window(logo);
        printstr("ADONIS", t_width/2-3, 2);

        gui_window input = {1, t_height-2, t_width-1, 3};
        draw_window(input);

        pthread_mutex_lock(&lock);
        if (command[len-1] == '\n') {
            strcpy(last_msg, command);
            memset(command, 0, len);
            len = 0;
        }

        printstr("$ ", 3, 10);
        prints(last_msg);
        printstr("$ ", 3, t_height - 1);
        prints(command);
        pthread_mutex_unlock(&lock);

        fsleep(0.01);
        clrscr();
    }
}

pthread_t io_t, gui_t;

int main() {
    enableRawMode();
    init_gui();
    pthread_mutex_init(&lock, NULL);

    pthread_create(&io_t, NULL, read_input, NULL);
    pthread_create(&gui_t, NULL, draw_gui, NULL);

    pthread_join(io_t, NULL);
    disableRawMode();
    return 0;
}