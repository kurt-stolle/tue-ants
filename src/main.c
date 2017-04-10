// This file contains the program's main method, i.e. the starting point of the
// program
#include <stdio.h>
#include <stdlib.h>

#include "init.h"
#include "play.h"
#include "world.h"

// World information
static world_t* world;

// Main function
int main() {
  // Play the game
  // World and game initialization
  world = newWorld();

  // Initialize and play
  if (init(world)) {
    fflush(stdout);

    while (play(world)) {
      // Debug print
      fprintf(stderr, "Finished turn, %d turns passed\n", world->turns);
      printMap(world->map, stderr);
      fputc('\n', stderr);
      // fflush stdout
      fflush(stdout);
    };
  }

  // Deallocate memory
  destroyWorld(world);

  // We don't have any special exit codes
  return 0;
}