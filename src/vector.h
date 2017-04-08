#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>

// vec2_t is a cartesian coordinate
typedef struct {
  uint16_t x : 16;
  uint16_t y : 16;
} vec2_t;

#endif