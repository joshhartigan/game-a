#include <curses.h>

#include "color.h"

void init_colors() {
  init_pair(WHITE,  COLOR_WHITE,  COLOR_BLACK);
  init_pair(GREEN,  COLOR_GREEN,  COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(RED,    COLOR_RED,    COLOR_BLACK);
  init_pair(BLUE,    COLOR_BLUE,    COLOR_BLACK);
}
