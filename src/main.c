/* This file contains the program's main method, i.e. the starting point of the program */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ants.h"

/* Constants */
const char delim[] = " \n"

/* Command splitting utility. Returns the amount of arguments found (incl the actual command) */
typedef struct{
    char* cmd       /* the actual command */
    char** args     /* args array */
    size_t argsLen  /* length of the args array */
} command_t;

command_t* readCommand(char* cmd){
    /* Allocate memory for the result */
    command_t* res = malloc(sizeof(*res));
    res->argsLen = 0;

    /* Read using strtok */
    char* token;
    for (;;){
        token = strtok_r(cmd, delim, &cmd);

        /* If the token equals null, then there is nothing more to read */
        if( token == NULL) {
            break;
        }

        if (!(res->cmd)){
            cmd=token;
        else {
            res->argsLen++;

            /* Allocate memory to store the argument */
            if (res->argsLen == 1){
                res->args = malloc(res->argsLen * sizeof(*(res->args)));
            } else {
                res->args = realloc(res->args, res->argsLen * sizeof(*(res->args));
            }

            /* Store the location of the token in the array */
            res->args[res->argsLen-1] = token;
        }               
    }

    return res;
}

void destroyCommand(command_t* c){
    free(c->args);
    free(c);
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
    /* Logic variables */
    int i;
    char *line;
    size_t len;

    /* Data */
    unsigned int width, height;

    fprintf(stderr, "Starting initialization\n");

    /* Keep reading lines */
    while(getline(&line, &len, stdin) != 0) {
        /* Skip empty lines */
        if (strcmp(line, "\n") == 0) {
            continue;
        }

        /* Fetch the command */
        command_t* split = splitCommand(line,&split)
        char* cmd = split->cmd;
        char** args = split->args;
        size_t argsLen = split->argsLen;

        /* Switch by command */
        if (strEqual(cmd, "ready")){
            break
        } else if (strEqual(cmd, "rows" && argsLen == 1)){
            height = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- map height: %d\n", args[0]);
        } else if (strEqual(cmd, "cols" && argsLen == 1)){
            width = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- map width: %d\n", args[0]);
        } else if (strEqual(cmd, "turns" && argsLen == 1)){
            w->turns = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- turns: %d\n", args[0]);
        } else if (strEqual(cmd, "viewradius2" && argsLen == 1)){
            w->viewRadius = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- view radius: %d\n", args[0]);
        } else if (strEqual(cmd, "attackradius2" && argsLen == 1)){
            w->attackRadius = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- attack radius: %d\n", args[0]);
        } else if (strEqual(cmd, "spawnradius2" && argsLen == 1)){
            w->spawnRadius = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- spawn radius: %d\n", args[0]);
        } else if (strEqual(cmd, "player_seed" && argsLen == 1)){
            w->playerSeed = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- player seed: %d\n", args[0]);
        } else if (strEqual(cmd, "loadtime" && argsLen == 1)){
            w->loadTime = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- load time: %d\n", args[0]);
        } else if (strEqual(cmd, "turntime" && argsLen == 1)){         
            w->urnTime = (unsigned int) strToInt(args[0]);
            fprintf(stderr, "- turn time: %d\n", args[0]);
        } else {
            fprintf(stderr, "Unknown command: %s\n", cmd);
            continue; /* Unknown command */
        }
    }

    /* Set remaining values */
    w->map = newMap(width, height);

    /* Dealloc */
    free(line);
    free(saveptr);
    free(token);
    free(split);

    printf("go\n");
    fflush(stdout);
    fprintf(stderr, "Finished initialization\n");

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