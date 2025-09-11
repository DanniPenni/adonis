//
// Created by Dania Al-Zgul on 08/09/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "drawing.h"
#include "gui.h"

struct Window {
    int width, height;
} typedef Window;

struct RowNode {
    struct RowNode *parent, *left, *right;
    struct Window* windows;
    int top, bottom, start, end, middle;

} typedef RowNode;


int main() {
    init_gui();

    while (1) {
        draw_gui();
    }

    return 0;
}