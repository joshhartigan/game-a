#ifndef GAME_H
#define GAME_H

#include <curses.h>

#include "player.h"

#define MAP_SIZE_X 80
#define MAP_SIZE_Y 20

char *map[MAP_SIZE_X][MAP_SIZE_Y];
Player player;
WINDOW *window;

#endif
