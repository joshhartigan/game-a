#include <stdbool.h>
#include <string.h>

#include "input.h"

#include "game.h"
#include "player.h"
#include "map.h"
#include "controls.h"

bool key_of_type(char key, char *group) {
  for (int i = 0; i < (int) strlen(group); i++) {
    if (group[i] == key) return true;
  }

  return false;
}

void handle_keypress(char key) {
  if (key_of_type(key, MOVEMENT_KEYS)) {
    move_player(key, &player);
  }

  if (key_of_type(key, DRAIN_KEYS)) {
    drain_water(player);
  }
}
