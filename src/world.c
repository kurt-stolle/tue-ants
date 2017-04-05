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
  c.state = stateHill;
  c.content.hill = h;
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
  c.state = stateAnt;
  c.content.ant = a;
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
  c.state = stateFood;
  c.content.food = f;
}