#ifndef TYPES_H
#define TYPES_H

// vec2_t is a cartesian coordinate
typedef struct
{
    unsigned int x;
    unsigned int y;
} vec2_t;

// ant_t is an ant
typedef struct
{
    int alive;
    vec2_t *position;
} ant_t;

// hill_t is a hill
typedef struct
{
    vec2_t *position;
} hill_t;

// food_t is food
typedef struct
{
    vec2_t *position;
} food_t;

// player_t is a player
typedef struct
{
    ant_t *ants;
    hill_t *hills;

} player_t;

// cell_t is a cell
typedef struct
{
    char state;
    unsigned int lastSeen;
} cell_t;

// map_t is the worldmap
typedef struct
{
    unsigned int width;
    unsigned int height;
    cell_t ***cells;
} map_t;

// world_t holds general information about the game
typedef struct
{
    map_t *map; // Pointer to a 2D array
    unsigned int turns;
    unsigned int viewRadius;
    unsigned int attackRadius;
    unsigned int spawnRadius;
    unsigned int playerSeed;
    unsigned int loadTime;
    unsigned int turnTime;
} world_t;

// game_t is the current state of the game (as it progresses)
typedef struct
{
    player_t *localPlayer;

    unsigned int playerCount;
    player_t **players;
} game_t;

#endif