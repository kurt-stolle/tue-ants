#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

// Cell methods
cell_t *newCell() {
  cell_t *c;

  // Allocate cell
  c = malloc(sizeof(*c));
  c->state = stateEmpty;
  c->lastSeen = 0;

  return c;
}

void destroyCell(cell_t *c) {
  if (c->content.ant) {
    fputs("Removed cell without clearing contents first", stderr);
  }
  free(c);
}
