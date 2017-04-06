#include <stdio.h>
#include <stdlib.h>

#include "map.h"

// Map methods
map_t *newMap(unsigned int w, unsigned int h) {
  map_t *m;
  unsigned int x, y;

  m = malloc(sizeof *m);
  m->width = w;
  m->height = h;
  m->cells = malloc(w * sizeof(*(m->cells)));

  for (x = 0; x < w; x++) {
    m->cells[x] = malloc(h * sizeof(*(m->cells[x])));
    for (y = 0; y < h; y++) {
      m->cells[x][y] = newCell();
    }
  }

  return m;
}

void printMap(map_t *m, FILE *out) {
  unsigned int x, y;
  cell_t *cell;

  fprintf(out, "rows %d\n", m->width);
  fprintf(out, "cols %d\n", m->height);
  for (x = 0; x < m->width; x++) {
    fputs("m ", out);
    for (y = 0; y < m->height; y++) {
      cell = m->cells[x][y];

      switch (cell->state) {
        case stateLand:
          fputc('.', out);
          break;
        case stateWater:
          fputc('%', out);
          break;
        case stateAnt:
          fputc((char)(65 + cell->content.ant->owner), out);
          break;
        case stateHill:
          fputc((char)(48 + cell->content.ant->owner), out);
          break;
        case stateAntOnHill:
          fputc((char)(97 + cell->content.ant->owner), out);
          break;
        case stateFood:
          fputc('*', out);
          break;
        default:
          fputc('?', out);
      }
    }
    fputc('\n', out);
  }
}

void destroyMap(map_t *m) {
  unsigned int x, y;

  // Deallocate cells
  for (x = 0; x < m->width; x++) {
    for (y = 0; y < m->height; y++) {
      destroyCell(m->cells[x][y]);
    }
    free(m->cells[x]);
  }
  free(m->cells);
  free(m);
}

cell_t *getCellAt(map_t *m, long x, long y) {
  // Wrapping for sides
  if (x < 0) {
    while (x < 0) {
      x = m->width + x;
    }
  } else {
    x = x % m->width;
  }

  if (y < 0) {
    while (y < 0) {
      y = m->height + y;
    }
  } else {
    y = y % m->height;
  }

  // Return cell at coord
  return m->cells[x][y];
}