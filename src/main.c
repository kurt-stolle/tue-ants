// This file contains the program's main method, i.e. the starting point of the
// program
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ants.h"


// Main function
int main() {
  // World and game
  world_t *world = newWorld();
  game_t *game = newGame();

  // Initialize and play
  if (init(world)) {
    while (play(world, game)) {
      // Debug print
      fprintf(stderr, "Finished turn, %d turns passed\n", world->turns);
      printMap(world->map, stderr);
    };
  }

  // Deallocate memory
  destroyWorld(world);
  destroyGame(game);

  // We don't have any special exit codes
  return 0;
}