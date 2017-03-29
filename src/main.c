/* This file contains the program's main method, i.e. the starting point of the program */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ants.h"

/* Constants */
const char delim[] = " \n"

/* Command splitting utility. Returns the amount of arguments found (incl the actual command) */
int splitCommand(char* cmd, char*** arr){
    char* token;
    size_t size = 0;
    for (;;){
        token = strtok_r(cmd, delim, &cmd);

        /* If the token equals null, then there is nothing more to read */
        if( token == NULL) {
            break;
        }

        /* Increase the size of the array */
        size++;
        if (size == 1){
            *arr = malloc(size * sizeof(**arr));
        } else {
            *arr = realloc(*arr, size * sizeof(**arr));
        }

        /* Store the location of the token in the array */
        *arr[size-1] = token;                
    }

    /* Handle the case where strtok doesn't return anything */
    if (size == 0){
        *arr = malloc(size * sizeof(**arr));
        *arr[size-1] = cmd;
    }

    return size;
}

/* Macro functions, so that the library functions can easily be replaced */
inline bool strEqual(const char* a, const char* b){
    return strcmp(a,b) == 0;
}

inline long strToInt(const char* str) {
    return strtol(str,NULL,10);
}

/* Initialization function */
bool init(world_t* w) {
    // Logic variables
    char *line;
    size_t len;
    char *saveptr;
    char *token;
    char** split;

    // Data received
    unsigned int width, height;

    while(getline(&line, &linelength, stdin) != 0) {
        /* Skip empty lines */
        if (strcmp(line, "\n") == 0) {
            continue;
        }

        /* Fetch the command */
        int args = splitCommand(line,&split)

        if (args <= 0){ 
            free(line); /* Something went wrong */
            return false; 
        }

        // Switch by command (first arg)
        const char* cmd = split[0];
        if (strEqual(cmd, "ready")){
            break; // Initialization is done
        } else if (strEqual(cmd, "rows" && args == 2)){
            height = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "cols" && args == 2)){
            width = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "turns" && args == 2)){
            w.turns = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "viewradius2" && args == 2)){
            w.viewRadius = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "attackradius2" && args == 2)){
            w.attackRadius = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "spawnradius2" && args == 2)){
            w.spawnRadius = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "player_seed" && args == 2)){
            w.playerSeed = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "loadtime" && args == 2)){
            w.loadTime = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "turntime" && args == 2)){         
            w.turnTime = (unsigned int) strToInt(split[1]);
        } else if (strEqual(cmd, "player_seed" && args == 2)){         
            w.turnTime = (unsigned int) strToInt(split[1]);
        } else {
            continue; // Unknown command;
        }
    }

    /* Set remaining values */
    w.map = newMap(width, height);

    /* Dealloc line */
    free(line);

    return true;
}

/* Play function. Plays the ants game */
bool play(world_t* w, game_t* g) {


    return true;
}

/* Main function. Returns 0 if there was no error */
int main(){
    int exitCode = 0;

    /* World and game */
    world_t* world = newWorld();
    game_t* game = newGame();

    /* Initialize and play */
    if (!init(world)){
        exitCode = 3;
    } else if (!play(world,game)){
        exitCode = 4;
    }

    /* Deallocate memory */
    destroyWorld(world);
    destroyGame(game);

    return exitCode;
}