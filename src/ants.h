#ifndef ANTS_H
#define ANTS_H

/* world_t holds general information about the game */
typedef struct {
    map_t* map; /* Pointer to a 2D array */
    int turns;  /* -1 for no turns */
} world_t;

world_t* newWorld();
void destroyWorld(world_t* w);

/* map_t is the worldmap */
typedef struct {
    unsigned int width;
    unsigned int height;
    char* cells;
} map_t;

/* game_t is the current state of the game (as it progresses) */
typedef struct {
    player_t* localPlayer;
    
    unsigned int playerCount;
    player_t* players;
} game_t;

game_t* newGame();
void destroyGame(game_t* g);

/* player_t is a player */
typedef struct {
    ant_t* ants;
    hill_t* hills;

} player_t;

/* vec2_t is a cartesian coordinate */
typedef struct {
    unsigned int x;
    unsigned int y;
} vec2_t;

/* ant_t is an ant */
typedef struct {
    int alive;
    vec2_t* position;
} ant_t;

/* hill_t is a hill */
typedef struct {
    vec2_t* position;
} hill_t;

/* food_t is food */
typedef struct {
    vec2_t* position;
} food_t;

#endif