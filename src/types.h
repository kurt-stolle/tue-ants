// Types for the ants bot
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include "vector.h"

// player_t is a player
typedef struct { unsigned short id : 8; } player_t;

// ant_t is an ant
typedef struct {
  bool alive : 1;
  vec2_t position;
  player_t *owner;
} ant_t;

// hill_t is a hill
typedef struct {
  vec2_t position;
  player_t *owner;
} hill_t;

// food_t is food
typedef struct { vec2_t position; } food_t;

#endif