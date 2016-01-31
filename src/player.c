#include "player.h"

#include "controls.h"
#include "game.h"

#include <string.h>

void move_player(char key, Player *player) {
  if (key == UP_KEY && player->y_pos > 0) {
    player->y_pos--;
  }

  else if (key == DOWN_KEY && player->y_pos < MAP_SIZE_Y - 1) {
    player->y_pos++;
  }

  else if (key == LEFT_KEY && player->x_pos > 0) {
    player->x_pos--;
  }

  else if (key == RIGHT_KEY && player->x_pos < MAP_SIZE_X - 1) {
    player->x_pos++;
  }
}

int get_inventory_index(char *name) {
  for (int i = 0; i < FULL_INVENTORY - 1; i++) {
    if (player.inventory[i].name &&
        strcmp(player.inventory[i].name, name) == 0) {
      return i;
    }
  }

  return -1;
}

int next_free_inventory_slot() {
  for (int i = 0; i < FULL_INVENTORY; i++) {
    if (player.inventory[i].name == NULL) return i;
  }

  return -1;
}
