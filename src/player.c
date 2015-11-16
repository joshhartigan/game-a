#include "player.h"

#include "controls.h"
#include "constants.h"

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
