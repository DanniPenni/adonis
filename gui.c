// The functions that draw the GUI of ADONIS.
#include <stdio.h>
#include <stdlib.h>
#include "drawing.h"
#include "gui.h"

#include <string.h>

#include "inputparse.h"

int draw_gui() {
    static char last_msg[INLEN];
    static int i = 0;

    gui_window logo = {1, 1, t_width-1, 3};
    draw_window(logo);
    char msg[300];
    snprintf(msg, 299, "ADON%dS", i);
    printstr(msg, t_width / 2 - 3, 2);

    gui_window input = {1, t_height-2, t_width-1, 3};
    draw_window(input);

    cursor_to(t_height-1, 3);

    char * command = read_input();
    int len = strlen(command);

    if (command[len - 1] == '\n') {
        strcpy(last_msg, command);
        memset(command, '\0', len);
        len = 0;
    }

    printstr(command, 3, 10);

    fsleep(0.1);
    clrscr();
    i++;
    return 0;
}