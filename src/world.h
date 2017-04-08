#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>

#include "map.h"
#include "types.h"

// world_t holds general information about the game
typedef struct {
  map_t *map;  // Pointer to a 2D array

  uint16_t turns : 16;
  uint16_t viewRadius2 : 16;
  uint16_t viewRadius : 16;
  uint16_t attackRadius2 : 16;
  uint16_t spawnRadius2 : 16;
  uint32_t playerSeed : 16;
  uint32_t loadTime : 16;
  uint32_t turnTime : 16;

  uint8_t localPlayer : 8;

  uint32_t hillCount : 32;
  uint32_t foodCount : 32;
  uint16_t antCount : 16;

  ant_t **ants;
  hill_t **hills;
  food_t **foods;
} world_t;

// world_t methods
world_t *newWorld();
void destroyWorld(world_t *w);

void addHill(world_t *w, hill_t *h);
void addAnt(world_t *w, ant_t *a);
void addFood(world_t *w, food_t *f);

#endif