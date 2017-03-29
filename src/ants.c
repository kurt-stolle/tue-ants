#include <stdio.h>
#include <stdlib.h>

#include "ants.h"

/* World methods */
world_t* newWorld() {    
    unsigned int i;
    
    /* Allocate world */
    world_t* w = malloc(sizeof *w);

    /* Default values */
    w.turns = 0;
    w.viewRadius = 0;
    w.attackRadius = 0;
    w.spawnRadius = 0;
    w.playerSeed = 0;
    w.loadTime = 0;
    w.turnTime = 0;

    w.map = NULL;

    /* Return world pointer */
    return w;
}

void destroyWorld(world_t* w){
    /* Destroy map */
    if (w.Map != NULL){
        destroyMap(w.map);
    }

    /* Deallocate world */
    free(w);
}

/* Map methods */
map_t* newMap(unsigned int w, unsigned int h) {
    map_t* map = malloc(sizeof *w.map);
    map.width = w;
    map.height = h;
    map.cells = calloc(0, w * sizeof(*w.map.cells));

    for(i=0; i < h; i++){
        map.cells[i] = calloc(0, h * sizeof(*w.map.cells[i]));
    }
}

void destroyMap(map_t* m){
    unsigned int i;

    /* Deallocate cells */
    for(i=0; i < m.height; i++){
        free(m.cells[i]);
    }
    free(m.cells); 
    free(m);
}

/* Cell methods */
cell_t newCell(){

}
bool isCellVisible(cell_t* c, world_t* w){
    
}
void destroyCell(cell_t* c){
    
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