//
// Created by Daniel Al-Zgul on 08/09/2025.
//

#ifndef ADONIS_GUI_H
#define ADONIS_GUI_H

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

int init_gui();
int draw_gui();

#endif //ADONIS_GUI_H