#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

// Cell methods
cell_t *newCell() {
  cell_t *c;

  // Allocate cell
  c = malloc(sizeof(*c));
  c->state = stateUnknown;
  c->lastSeen = 0;
  c->content.empty = NULL;

  return c;
}

void destroyCell(cell_t *c) { free(c); }
