#include <stdio.h>
#include <stdlib.h>

#include "ants.h"

/* World methods */
world_t* newWorld() {
    world_t* w = (world_t*) malloc(sizeof world_t);

    /* Initialize the map */

    /* Return world pointer */
    return w;
}

void destroyWorld(world_t* w){
    free(w);
}

/* Game methods */
game_t* newGame() {
    game_t g = (game_t*) malloc(sizeof game_t);

    /* Default values */

    /* Return game pointer */
    return g;
}

void destroyGame(game_t* g){
    free(g);
}