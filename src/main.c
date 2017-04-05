// This file contains the program's main method, i.e. the starting point of the
// program
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ants.h"

// World information
static world_t* world;

// Main function
int main() {
  // World and game initialization
  world = newWorld();

  // Initialize and play
  if (init(world)) {
    fflush(stdout);

    while (play(world)) {
      // Debug print
      fprintf(stderr, "Finished turn, %d turns passed\n", world->turns);
      printMap(world->map, stderr);

      // fflush stdout
      fflush(stdout);
    };
  }

  // Deallocate memory
  destroyWorld(world);
  destroyGame(game);

  // We don't have any special exit codes
  return 0;
}