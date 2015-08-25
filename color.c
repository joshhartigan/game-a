#include <curses.h>

#include "color.h"

void init_colors() {
  init_pair(WHITE,  COLOR_WHITE,  COLOR_BLACK);
  init_pair(GREEN,  COLOR_GREEN,  COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(ERROR_COLOR, COLOR_WHITE, COLOR_RED);
}
