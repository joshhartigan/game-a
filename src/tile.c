#include <string.h>
#include <stdbool.h>

#include "tile.h"

#include "color.h"

char *tile_names[] = {
  // grasses: [0] -> [3]
  "wheatgrass",
  "bluegrass",
  "ryegrass",
  "dead grass",
  // trees: [4] -> [11]
  "an apple tree",
  "a birch tree",
  "an oak tree",
  "a small maple tree",
  "an old maple tree",
  "a dying pear tree",
  "a pecan tree",
  "a willow tree",
  // pond: [4]
  "a pond",
};

char *tile_glyphs[] = {
  // grasses: [0] -> [3]
  ".",
  "`",
  "'",
  "\"",
  // trees: [4] -> [11]
  "y",
  "y",
  "Y",
  "y",
  "Y",
  "y",
  "y",
  "Y",
  // pond: [4]
  "o",
};

/*
char *glyph_from_name(char *name) {
  for (int i = 0; i < TILE_COUNT; i++) {
    if (strcmp(tile_names[i], name) == 0) {
      return tile_glyphs[i];
    }
  }

  return "?";
}
*/

char *name_from_glyph(char *glyph) {
  for (int i = 0; i < TILE_COUNT; i++) {
    if (strcmp(tile_glyphs[i], glyph) == 0) {
      return tile_names[i];
    }
  }

  return "ERROR! Unrecognised glyph.";
}

bool glyph_is_id(char *glyph, int ID) {
  return strcmp(glyph, tile_glyphs[ID]) == 0;
}

bool glyph_is_valid(char *glyph, int LOW_ID, int HI_ID) {
  for (int i = LOW_ID; i < HI_ID; i++) {
    if (strcmp(glyph, tile_glyphs[i]) == 0) {
      return true;
    }
  }

  return false;
}

int get_glyph_color(char *glyph) {
  if (glyph_is_id(glyph, POND_ID)) {
    return BLUE;
  }

  if (glyph_is_valid(glyph, LOW_TREE_ID, HI_TREE_ID)) {
    return YELLOW;
  }

  if (glyph_is_valid(glyph, LOW_GRASS_ID, HI_GRASS_ID)) {
    return GREEN;
  }

  return -1;
}
