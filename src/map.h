#ifndef MAP_H
#define MAP_H

#include "cell.h"

// map_t is the worldmap
typedef struct {
  unsigned int width;
  unsigned int height;
  cell_t ***cells;
} map_t;

// map_t methods
map_t *newMap();
void printMap(map_t *m, FILE *out);
void destroyMap(map_t *m);
cell_t *getCellAt(map_t *m, long x, long y);

#endif