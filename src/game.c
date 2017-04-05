#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

// Game methods
game_t *newGame() {
  game_t *g = malloc(sizeof *g);

  // Return game pointer
  return g;
}

void destroyGame(game_t *g) {
  unsigned int i;

  // Deallocate players
  // We don't need to deallocate memory at the localPlayer pointer. This player
  // is also in the array
  for (i = 0; i < g->playerCount; i++) {
    free(g->players[i]);
  }

  // Deallocate world
  free(g);
}