#include <stdlib.h>

#include "map.h"

#include "game.h"
#include "tile.h"
#include "player.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

void generate_map() {
  for (int x = 0; x < MAP_SIZE_X; x++) {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
      int chance = (rand() % 100) + 1;

      if (chance < TREE_PROBABILITY) {
        map[x][y] =
          tile_glyphs[(rand() % (HI_TREE_ID - LOW_TREE_ID)) + LOW_TREE_ID];
      }

      else if (chance < PUDDLE_PROBABILITY) {
        generate_puddle(x, y);
      }

      // else if (OTHER PROBABILITIES ETC)

      else {
        map[x][y] =
          tile_glyphs[(rand() % (HI_GRASS_ID - LOW_GRASS_ID)) + LOW_GRASS_ID];
      }
    }
  }
}

void generate_puddle(int x, int y){
  map[x][y] = tile_glyphs[LOW_PUDDLE_ID];

  int upward_size = 0;
  int downward_size = 0;
  int rightward_size = 0;
  int leftward_size = 0;

  int puddle_size = (rand() % (MAX_PUDDLE_SIZE - MIN_PUDDLE_SIZE)) + MAX_PUDDLE_SIZE;

  for (int i = 0; i < puddle_size; i++) {
    int direction = (rand() % (4 - 0)) + 4;

    if (direction == UP && upward_size < 2) {
      upward_size++;
      map[x][y - 1] = tile_glyphs[LOW_PUDDLE_ID];
    }

    else if (direction == DOWN && downward_size < 2) {
      downward_size++;
      map[x][y + 1] = tile_glyphs[LOW_PUDDLE_ID];
    }

    else if (direction == RIGHT && rightward_size < 2) {
      rightward_size++;
      map[x + 1][y] = tile_glyphs[LOW_PUDDLE_ID];
    }

    else if (direction == LEFT && leftward_size < 2) {
      leftward_size++;
      map[x - 1][y] = tile_glyphs[LOW_PUDDLE_ID];
    }
  }
}

void drain_water(Player player) {
  if (!glyph_is_valid(map[player.x_pos][player.y_pos],
        LOW_PUDDLE_ID, HI_PUDDLE_ID)) {
    return; // we can not drain things that aren't puddles
  }

  map[player.x_pos][player.y_pos] = tile_glyphs[HI_PUDDLE_ID];

  if (get_inventory_index("water") != -1) {
    player.inventory[get_inventory_index("water")].count++;
  } else {
    player.inventory[next_free_inventory_slot()] =
      (Item) { .name = "water", .count = 1 };
  }
}
