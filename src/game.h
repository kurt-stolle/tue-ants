#ifndef GAME_H
#define GAME_H

#include "types.h"

// game_t is the current state of the game (as it progresses)
typedef struct
{
    player_t *localPlayer;

    unsigned short playerCount;
    player_t **players;
} game_t;

// game_t methods
game_t *newGame();
void destroyGame(game_t *g);

#endif