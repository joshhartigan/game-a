#include "player.h"

#include "controls.h"

void move_player(char key, Player *player) {
  switch (key) {
    case UP_KEY:
      player->y_pos--;
      break;
    case DOWN_KEY:
      player->y_pos++;
      break;
    case LEFT_KEY:
      player->x_pos--;
      break;
    case RIGHT_KEY:
      player->x_pos++;
      break;
  }
}
