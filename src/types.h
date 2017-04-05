// Types for the ants bot
#ifndef TYPES_H
#define TYPES_H

#include "vector.h"

// ant_t is an ant
typedef struct
{
    int alive;
    vec2_t *position;
} ant_t;

// hill_t is a hill
typedef struct
{
    vec2_t *position;
} hill_t;

// food_t is food
typedef struct
{
    vec2_t *position;
} food_t;

// player_t is a player
typedef struct
{
    ant_t *ants;
    hill_t *hills;
} player_t;

#endif