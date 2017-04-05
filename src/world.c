#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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