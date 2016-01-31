#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

#include "color.h"
#include "player.h"
#include "tile.h"
#include "map.h"
#include "input.h"

// -- drawing functions -- //

void draw_map() {
  for (int x = 0; x < MAP_SIZE_X; x++) {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
      color_set(get_glyph_color(map[x][y]), NULL);
      mvaddstr(y, x, map[x][y]);
    }
  }

  refresh();
}

void draw_player() {
  color_set(WHITE, NULL);
  mvaddstr(player.y_pos, player.x_pos, PLAYER_CHAR);
  refresh();
}

void draw_status() {
  int min_y = MAP_SIZE_Y + 1;
  color_set(WHITE, NULL);

  // clear the line (to prevent overlapping previous text)
  move(min_y, 0);
  clrtoeol();

  // what am I standing on?
  char floor_text[MAP_SIZE_X];
  char *floor_name = name_from_glyph(map[player.x_pos][player.y_pos]);
  sprintf(floor_text, "You are standing on %s.", floor_name);
  mvaddstr(min_y, 0, floor_text);
  min_y++;

  // what do I have in my possession?
  char inv_text[MAP_SIZE_X];
  int water_count = player.inventory[get_inventory_index("water")].count;
  sprintf(inv_text, "You have %d water.", water_count);
  mvaddstr(min_y, 0, inv_text);

  refresh();
}

void draw_inventory() {}

void draw() {
  draw_map();
  draw_player();
  draw_status();
  draw_inventory();
}

// -- game / graphics logic functions -- //

void loop(char key) {
  handle_keypress(key);
  draw();
}

void quit(WINDOW *window) {
  delwin(window);
  endwin();
  refresh();
}

int main() {
  srand(time(NULL));

  window = initscr();

  if (window == NULL) {
    fprintf(stderr, "error initialising curses.\n");
    return 1;
  }

  start_color();
  if (has_colors() && COLOR_PAIRS >= 13) {
    init_colors();
  }
  curs_set(0); // hide the cursor
  noecho(); // do not show characters when they've been typed

  generate_map();
  player = (Player) {
    .x_pos = 5,
    .y_pos = 5,
    .inventory = { (Item) { "", 0 } }
  };

  loop('\0');

  char key = '\0';
  while (key != 27) { // 27 = escape key
    key = getch();
    loop(key);
  }

  quit(window);
}
