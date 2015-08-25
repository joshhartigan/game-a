#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "color.h"
#include "player.h"
#include "controls.h"

#define MAP_SIZE_X 40
#define MAP_SIZE_Y 20

char *map[MAP_SIZE_X][MAP_SIZE_Y];
Player player;

WINDOW *window;

void generate_map() {
  for (int x = 0; x < MAP_SIZE_X; x++) {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
      map[x][y] =
        tile_glyphs[rand() % HI_GRASS_ID] + LOW_GRASS_ID;
    }
  }
}

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
void draw_status() {}
void draw_inventory() {}

void draw() {
  draw_map();
  draw_player();
  draw_status();
  draw_inventory();
}

// -- game / graphics logic functions -- //

void handle_keypress(char key) {
  move_player(key, &player);
  // (if it isn't a movement key,
  //  this will just do nothing)
}

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

  loop(' ');

  char key = ' ';
  while (key != ESCAPE_KEY) {
    key = getch();
    loop(key);
  }

  quit(window);
}
