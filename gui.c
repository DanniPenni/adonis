// The functions that draw the GUI of ADONIS.
#include <stdio.h>
#include <stdlib.h>
#include "drawing.h"
#include "gui.h"

int draw_gui() {
    // Draw Logo
    int t_width = global_win.ws_col;
    int t_height = global_win.ws_row;

    gui_window w = {1, 1, t_width-1, 3};
    draw_window(w);
    printstr("ADONIS", t_width / 2 - 3, 2);
    fsleep(1);
    clrscr();
    return 0;
}