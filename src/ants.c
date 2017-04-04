#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ants.h"

// World methods
world_t *newWorld() {
  world_t *w;

  // Allocate world
  w = malloc(sizeof *w);
  w->turns = 0;
  w->viewRadius = 0;
  w->attackRadius = 0;
  w->spawnRadius = 0;
  w->playerSeed = 0;
  w->loadTime = 0;
  w->turnTime = 0;
  w->map = NULL;

  // Return world pointer
  return w;
}

void destroyWorld(world_t *w) {
  // Destroy map
  if (w->map != NULL) {
    destroyMap(w->map);
  }

  // Deallocate world
  free(w);
}

// Map methods
map_t *newMap(unsigned int w, unsigned int h) {
  map_t *m;
  unsigned int x, y;

  m = malloc(sizeof *m);
  m->width = w;
  m->height = h;
  m->cells = malloc(w * sizeof(*(m->cells)));

  for (x = 0; x < w; x++) {
    m->cells[x] = malloc(h * sizeof(*(m->cells[x])));
    for (y = 0; y < h; y++) {
      m->cells[x][y] = newCell();
    }
  }

  return m;
}

void printMap(map_t *m, FILE *out) {
  unsigned int x, y;
  cell_t *cell;

  fprintf(out, "rows %d\n", m->width);
  fprintf(out, "cols %d\n", m->height);
  for (x = 0; x < m->width; x++) {
    fputs("m ", out);
    for (y = 0; y < m->height; y++) {
      cell = m->cells[x][y];

      fputc(cell->state, out);
    }
    fputc('\n', out);
  }
}

void destroyMap(map_t *m) {
  unsigned int x, y;

  // Deallocate cells
  for (x = 0; x < m->width; x++) {
    for (y = 0; y < m->height; y++) {
      destroyCell(m->cells[x][y]);
    }
    free(m->cells[x]);
  }
  free(m->cells);
  free(m);
}

// Cell methods
cell_t *newCell() {
  cell_t *c;

  // Allocate cell
  c = malloc(sizeof(*c));
  c->state = '*';
  c->lastSeen = 0;

  return c;
}
bool isCellVisible(cell_t *c, world_t *w) { return true; }
void destroyCell(cell_t *c) { free(c); }

// Game methods
game_t *newGame() {
  game_t *g = malloc(sizeof *g);

  // Return game pointer
  return g;
}

void destroyGame(game_t *g) {
  unsigned int i;

  // Deallocate players
  // We don't need to deallocate memory at the localPlayer pointer. This player
  // is also in the array
  for (i = 0; i < g->playerCount; i++) {
    free(g->players[i]);
  }

  // Deallocate world
  free(g);
}