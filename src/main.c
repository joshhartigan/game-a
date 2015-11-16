#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "color.h"
#include "constants.h"
#include "controls.h"
#include "player.h"
#include "tile.h"

char *map[MAP_SIZE_X][MAP_SIZE_Y];
Player player;

WINDOW *window;

void generate_map() {
  for (int x = 0; x < MAP_SIZE_X; x++) {
    for (int y = 0; y < MAP_SIZE_Y; y++) {
      int chance = (rand() % 100) + 1;

      if (chance < TREE_PROBABILITY) {
        map[x][y] =
          tile_glyphs[(rand() % (HI_TREE_ID - LOW_TREE_ID)) + LOW_TREE_ID];
      }

      else if (chance < POND_PROBABILITY) {
        map[x][y] =
          tile_glyphs[POND_ID];
      }

      // else if (OTHER PROBABILITIES ETC)

      else {
        map[x][y] =
          tile_glyphs[(rand() % (HI_GRASS_ID - LOW_GRASS_ID)) + LOW_GRASS_ID];
      }
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

void draw_status() {
  int min_y = MAP_SIZE_Y + 1;

  // clear the line (to prevent overlapping previous text)
  move(min_y, 0);
  clrtoeol();

  char status_text[MAP_SIZE_X];
  char *floor_name = name_from_glyph(map[player.x_pos][player.y_pos]);
  sprintf(status_text, "You are standing on %s.", floor_name);

  color_set(WHITE, NULL);
  mvaddstr(min_y, 0, status_text);
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
  while (key != ESCAPE_KEY) {
    key = getch();
    loop(key);
  }

  quit(window);
}