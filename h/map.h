#ifndef MAP_H
#define MAP_H

#include "player.h"

#define MAX_PUDDLE_SIZE 50
#define MIN_PUDDLE_SIZE 4

void generate_map();

// this will generate a puddle with
// its center at (x, y):
void generate_puddle(int x, int y);

void drain_water(Player player);

#endif
