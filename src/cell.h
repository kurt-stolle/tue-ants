#ifndef CELL_H
#define CELL_H

#include "types.h"

// cell_t is a cell
typedef struct {
  enum {
    stateUnknown,
    stateLand,
    stateWater,
    stateAnt,
    stateHill,
    stateAntOnHill,
    stateFood
  } state;  // State of the cell

  union {
    ant_t* ant;
    hill_t* hill;
    food_t* food;
    void* empty;
  } content;

  unsigned short lastSeen;  // Turn in which this cell was last seen. Can be
                            // useful for strategy
} cell_t;

// cell_t methods
cell_t* newCell();
void destroyCell(cell_t* c);

#endif