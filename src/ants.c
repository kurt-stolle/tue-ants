#include <stdio.h>
#include <stdlib.h>

#include "ants.h"

/* World methods */
world_t* newWorld(unsigned int w, unsigned int h) {    
    unsigned int i;
    
    /* Allocate world */
    world_t* w = malloc(sizeof *w);

    /* Default values */
    w.turns = -1;

    /* Initialize the map */
    map_t* map = malloc(sizeof *w.map);
    map.width = w;
    map.height = h;
    map.cells = calloc(0, w * sizeof(*w.map.cells));

    for(i=0; i < h; i++){
        map.cells[i] = calloc(0, h * sizeof(*w.map.cells[i]));
    }

    w.map = map;

    /* Return world pointer */
    return w;
}

void destroyWorld(world_t* w){
    unsigned int i;

    /* Deallocate cells */
    for(i=0; i < w.map.height; i++){
        free(w.map.cells[i]);
    }
    free(w.map.cells); 

    /* Deallocate map */
    free(w.map);

    /* Deallocate world */
    free(w);
}

/* Game methods */
game_t* newGame() {
    game_t* g = malloc(sizeof *g);

    /* Return game pointer */
    return g;
}

void destroyGame(game_t* g){
    unsigned int i;
    
    /* Deallocate players */
    /* We don't need to deallocate memory at the localPlayer pointer. This player is also in the array */
    for(i=0; i<g.playerCount; i++){
        free(players[i]);
    }

    /* Deallocate world */
    free(g);
}