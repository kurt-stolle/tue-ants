#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "world.h"

// World methods
world_t *newWorld() {
  world_t *w;

  // Allocate world
  w = malloc(sizeof *w);

  w->turns = 0;
  w->viewRadius2 = 0;
  w->attackRadius2 = 0;
  w->spawnRadius2 = 0;
  w->playerSeed = 0;
  w->loadTime = 0;
  w->turnTime = 0;

  w->map = NULL;

  w->localPlayer = NULL;

  w->playerCount = 0;
  w->hillCount = 0;
  w->antCount = 0;
  w->foodCount = 0;

  w->players = NULL;
  w->hills = NULL;
  w->ants = NULL;
  w->foods = NULL;

  // Return world pointer
  return w;
}

void destroyWorld(world_t *w) {
  // Map
  if (w->map != NULL) {
    destroyMap(w->map);
  }

  // Arrays
  unsigned int i;
  for (i = 0; i < w->playerCount; i++) {
    free(w->players[i]);
  }
  for (i = 0; i < w->hillCount; i++) {
    free(w->hills[i]);
  }
  for (i = 0; i < w->antCount; i++) {
    free(w->ants[i]);
  }
  for (i = 0; i < w->foodCount; i++) {
    free(w->foods[i]);
  }

  free(w->players);
  free(w->hills);
  free(w->ants);
  free(w->foods);

  // World
  free(w);
}

// Add a player
void addPlayer(world_t *w, player_t *p) {
  // Increment counter and (re)allocate array
  w->playerCount++;
  w->players = realloc(w->players, w->playerCount * sizeof(*w->players));

  // Add a new entry at the end of the array
  w->players[w->playerCount - 1] = p;
}

// Add a hill
void addHill(world_t *w, hill_t *h) {
  // Increment counter and (re)allocate array
  w->hillCount++;
  w->hills = realloc(w->hills, w->hillCount * sizeof(*w->hills));

  // Add a new entry at the end of the array
  w->hills[w->hillCount - 1] = h;

  // Add to the map
  cell_t *c = w->map->cells[h->position.x][h->position.y];
  c->state = stateHill;
  c->content.hill = h;
}

// Add an ant
void addAnt(world_t *w, ant_t *a) {
  // Increment counter and (re)allocate array
  w->antCount++;
  w->ants = realloc(w->ants, w->antCount * sizeof(*w->ants));

  // Add a new entry at the end of the array
  w->ants[w->antCount - 1] = a;

  // Add to the map
  cell_t *c = w->map->cells[a->position.x][a->position.y];
  c->state = stateAnt;
  c->content.ant = a;
}

// Add a food
void addFood(world_t *w, food_t *f) {
  // Increment counter and (re)allocate array
  w->foodCount++;
  w->foods = realloc(w->foods, w->foodCount * sizeof(*w->foods));

  // Add a new entry at the end of the array
  w->foods[w->foodCount - 1] = f;

  // Add to the map
  cell_t *c = w->map->cells[f->position.x][f->position.y];
  c->state = stateFood;
  c->content.food = f;
}

// Remove a player
void removePlayer(world_t *w, player_t *p) {
  for (unsigned int i = 0; i < w->playerCount; i++) {
    if (w->players[i] == p) {
      if (w->playerCount > 1) {
        // Move all future entries one back
        for (; i < (unsigned int)(w->playerCount - 1); i++) {
          w->players[i] = w->players[i + 1];
        }
      }

      // Reallocate the array
      w->playerCount--;
      w->players = realloc(w->players, w->playerCount * sizeof(*w->players));

      // Free memory
      free(p);

      // Stop the loop
      break;
    }
  }
}

// Remove a hill
void removeHill(world_t *w, hill_t *h) {
  for (unsigned int i = 0; i < w->hillCount; i++) {
    if (w->hills[i] == h) {
      if (w->hillCount > 1) {
        // Move all future entries one back
        for (; i < (unsigned int)(w->hillCount - 1); i++) {
          w->hills[i] = w->hills[i + 1];
        }
      }

      // Reallocate the array
      w->hillCount--;
      w->hills = realloc(w->hills, w->hillCount * sizeof(*w->hills));

      // Free memory
      free(h);

      // Stop the loop
      break;
    }
  }

  // Clear cell
  cell_t *cell = w->map->cells[h->position.x][h->position.y];
  cell->state = stateEmpty;
  cell->content.ant = NULL;
}

// Remove an ant
void removeAnt(world_t *w, ant_t *a) {
  for (unsigned int i = 0; i < w->antCount; i++) {
    if (w->ants[i] == a) {
      if (w->antCount > 1) {
        // Move all future entries one back
        for (; i < (unsigned int)(w->antCount - 1); i++) {
          w->ants[i] = w->ants[i + 1];
        }
      }

      // Reallocate the array
      w->antCount--;
      w->ants = realloc(w->ants, w->antCount * sizeof(*w->ants));

      // Free memory
      free(a);

      // Stop the loop
      break;
    }
  }

  // Clear cell
  cell_t *cell = w->map->cells[a->position.x][a->position.y];
  cell->state = stateEmpty;
  cell->content.ant = NULL;
}

// Remove a food
void removeFood(world_t *w, food_t *f) {
  for (unsigned int i = 0; i < w->foodCount; i++) {
    if (w->foods[i] == f) {
      if (w->foodCount > 1) {
        // Move all future entries one back
        for (; i < (unsigned int)(w->foodCount - 1); i++) {
          w->foods[i] = w->foods[i + 1];
        }
      }

      // Reallocate the array
      w->foodCount--;
      w->foods = realloc(w->foods, w->foodCount * sizeof(*w->foods));

      // Free memory
      free(f);

      // Stop the loop
      break;
    }
  }

  // Clear cell
  cell_t *cell = w->map->cells[f->position.x][f->position.y];
  cell->state = stateEmpty;
  cell->content.ant = NULL;
}

// Clear a cell
void clearCell(world_t *w, cell_t *c) {
  // How we clear the cell depends on what's in it. Some types of cells must be
  // cleared from the world entirely.
  switch (c->state) {
    case stateAnt:
      removeAnt(w, c->content.ant);
      break;
    case stateHill:
      removeHill(w, c->content.hill);
      break;
    case stateFood:
      removeFood(w, c->content.food);
      break;
    default:
      c->state = stateEmpty;
      c->content.ant = NULL;
  }
}