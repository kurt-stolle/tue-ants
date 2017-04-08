// This file contains some quick utility functions
#include <string.h>

static inline bool strEqual(const char *a, const char *b) {
  return strcmp(a, b) == 0;
}

static inline long strToInt(const char *str) { return strtol(str, NULL, 10); }
