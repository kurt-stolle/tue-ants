#ifndef WORLD_H
#define WORLD_H

#include "map.h"
#include "types.h"

// world_t holds general information about the game
typedef struct {
  map_t *map;  // Pointer to a 2D array

  unsigned short turns;
  unsigned short viewRadius2;
  unsigned short attackRadius2;
  unsigned short spawnRadius2;
  unsigned int playerSeed;
  unsigned int loadTime;
  unsigned int turnTime;

  uint8_t localPlayer;

  unsigned short hillCount;
  unsigned short foodCount;
  unsigned int antCount;

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

void removeHill(world_t *w, hill_t *h);
void removeAnt(world_t *w, ant_t *a);
void removeFood(world_t *w, food_t *f);

#endif