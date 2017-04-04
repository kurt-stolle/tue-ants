#ifndef ANTS_H
#define ANTS_H

#include <stdbool.h>
#include "types.h"

// world_t methods
world_t *newWorld();
void destroyWorld(world_t *w);

// map_t methods
map_t *newMap();
void printMap(map_t *m, FILE *out);
void destroyMap(map_t *m);

// cell_t methods
cell_t *newCell();                          // TODO
bool isCellVisible(cell_t *c, world_t *w);  // TODO
void destroyCell(cell_t *c);                // TODO

// game_t methods
game_t *newGame();
void destroyGame(game_t *g);

#endif