#ifndef PANTALLA_H
#define PANTALLA_H

#include <U8g2lib.h>
#include <U8x8lib.h>

void displyInit();
void displayClear();
void displayPrint(char *str);
void displayPrintXY(int x, int y, char *str);
void displaySetFont(const uint8_t *font);

#endif
