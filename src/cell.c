#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

// Cell methods
cell_t *newCell() {
  cell_t *c;

  // Allocate cell
  c = malloc(sizeof(*c));
  c->state = cell_t.stateEmpty;
  c->lastSeen = 0;

  return c;
}
void clearCell(cell_t *c) {
  c->state = cell_t.stateEmpty;
  c->content = NULL;
}
void destroyCell(cell_t *c) { free(c); }
