#ifndef PLAYER_H
#define PLAYER_H

#define FULL_INVENTORY 64
#define PLAYER_CHAR "@"

typedef struct {
  char *name;
  int count;
} Item;

typedef struct {
  int x_pos;
  int y_pos;
  Item inventory[FULL_INVENTORY];
} Player;

void move_player(char key, Player *player);

int get_inventory_index(char *name);
int next_free_inventory_slot();

#endif
