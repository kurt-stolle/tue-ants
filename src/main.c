/* This file contains the program's main method, i.e. the starting point of the program */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ants.h"


/* Main function. Returns 0 if there was no error */
int main(){
    /* World and game */
    world_t* world = newWorld();
    game_t* game = newGame();

    /* Initialize the game */
   

    /* Keep reading until the game has finished */


    /* Deallocate memory */
    destroyWorld(world);
    destroyGame(game);

    /* Return code 0 - no error */
    return 0;
}