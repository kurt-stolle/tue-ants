// Play function, which plays one turn
#ifndef PLAY_H
#define PLAY_H

#include "world.h"
#include "game.h"

bool init(world_t* w);
bool play(world_t* w, game_t* g);