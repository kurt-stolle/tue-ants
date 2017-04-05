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

      fputc(cell->state, out);
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
