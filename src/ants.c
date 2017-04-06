#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "play.h"
#include "world.h"

// World information
static world_t* world;

// Wrapper for the game so that we can include this as a library when submitting
// the bot. Allows us to make our own optimizations to the library, as the
// library is submitted as a library, and not as .c files, like the main.c file.
void startGame() {
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
}