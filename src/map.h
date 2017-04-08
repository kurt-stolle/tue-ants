#ifndef MAP_H
#define MAP_H

#include <stdio.h>

#include "cell.h"

// direction_t is any direction we want to move towards
typedef enum {
  dirNorth = 'N',
  dirSouth = 'S',
  dirWest = 'W',
  dirEast = 'E'
} direction_t;

// map_t is the worldmap
typedef struct {
  uint16_t width : 16;
  uint16_t height : 16;
  cell_t ***cells;
} map_t;

// map_t methods
map_t *newMap();
void printMap(map_t *m, FILE *out);
void destroyMap(map_t *m);
cell_t *getCellAt(map_t *m, long x, long y);

#endif