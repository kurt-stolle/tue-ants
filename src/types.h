// Types for the ants bot
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include "vector.h"

// ant_t is an ant
typedef struct ant_s {
  enum { taskIdle = 0, taskExplore = 1, taskGatherFood = 3 } task;

  bool alive : 1;
  vec2_t target;
  vec2_t position;
  uint8_t owner : 8;
} ant_t;

// hill_t is a hill
typedef struct {
  vec2_t position;
  uint8_t owner;
} hill_t;

// food_t is food
typedef struct { vec2_t position; } food_t;

#endif