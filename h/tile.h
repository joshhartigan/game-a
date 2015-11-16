#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

#define TILE_COUNT 13

#define LOW_GRASS_ID  0
#define HI_GRASS_ID   3
#define LOW_TREE_ID   4
#define HI_TREE_ID   11
#define POND_ID      12

#define TREE_PROBABILITY 2
#define POND_PROBABILITY 3

char *tile_names[TILE_COUNT];
char *tile_glyphs[TILE_COUNT];

char *glyph_from_name(char *name);
char *name_from_glyph(char *glyph);

bool glyph_is_valid(char *str, int LOW_ID, int HI_ID);

int get_glyph_color(char *glyph);

#endif
