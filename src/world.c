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

  w->localPlayer = 0;

  w->hillCount = 0;
  w->antCount = 0;
  w->foodCount = 0;

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

  for (i = 0; i < w->hillCount; i++) {
    free(w->hills[i]);
  }
  for (i = 0; i < w->antCount; i++) {
    free(w->ants[i]);
  }
  for (i = 0; i < w->foodCount; i++) {
    free(w->foods[i]);
  }

  free(w->hills);
  free(w->ants);
  free(w->foods);

  // World
  free(w);
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

  if (c->state == stateAnt) {
    c->state = stateAntOnHill;
  } else {
    c->state = stateHill;
    c->content.hill = h;
  }
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

  if (c->state == stateHill) {
    c->state = stateAntOnHill;
  } else {
    c->state = stateAnt;
  }

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

// Remove a hill
void removeHill(world_t *w, hill_t *h) {
  // Clear cell
  cell_t *cell = w->map->cells[h->position.x][h->position.y];

  if (cell->state == stateAntOnHill) {
    cell->state = stateAnt;
  } else {
    cell->content.empty = NULL;
    cell->state = stateLand;
  }

  // Clean array
  unsigned int i;
  for (i = 0; i < w->hillCount; i++) {
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
}

// Remove an ant
void removeAnt(world_t *w, ant_t *a) {
  unsigned int i;

  // Clear cell
  cell_t *cell = w->map->cells[a->position.x][a->position.y];

  if (cell->state == stateAntOnHill) {
    hill_t *hill;

    for (i = 0; i < w->hillCount; i++) {
      hill = w->hills[i];

      if (hill->position.x == a->position.x &&
          hill->position.x == a->position.y) {
        cell->content.hill = hill;
        break;
      }
    }

    cell->state = stateHill;
  } else {
    cell->content.empty = NULL;
    cell->state = stateLand;
  }

  // Clean array
  for (i = 0; i < w->antCount; i++) {
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
}

// Remove a food
void removeFood(world_t *w, food_t *f) {
  // Clear cell
  cell_t *cell = w->map->cells[f->position.x][f->position.y];
  cell->content.empty = NULL;
  cell->state = stateLand;

  // Clean array
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
}
