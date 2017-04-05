#ifndef WORLD_H
#define WORLD_H

#include "map.h"

// world_t holds general information about the game
typedef struct
{
    map_t *map; // Pointer to a 2D array
    unsigned short turns;
    unsigned int viewRadius2;
    unsigned int attackRadius2;
    unsigned int spawnRadius2;
    unsigned int playerSeed;
    unsigned int loadTime;
    unsigned int turnTime;
} world_t;

// world_t methods
world_t *newWorld();
void destroyWorld(world_t *w);



#endif