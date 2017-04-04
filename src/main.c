// This file contains the program's main method, i.e. the starting point of the
// program
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ants.h"

// Constants
const char delim[] = " \n";

// Command splitting
typedef struct {
  char *cmd;       // the actual command
  char **args;     // args array
  size_t argsLen;  // length of the args array
} command_t;

command_t *readCommand(char *cmd) {
  command_t *res;

  // Allocate memory for the result
  res = malloc(sizeof(*res));
  res->argsLen = 0;
  res->cmd = NULL;
  res->args = NULL;

  // Read using strtok
  char *token;
  for (;;) {
    token = strtok_r(cmd, delim, &cmd);

    // If the token equals null, then there is nothing more to read
    if (token == NULL) {
      break;
    }

    if (!(res->cmd)) {
      res->cmd = token;
    } else {
      res->argsLen++;

      // Allocate memory to store the argument
      if (res->argsLen == 1) {
        res->args = malloc(res->argsLen * sizeof(*(res->args)));
      } else {
        res->args = realloc(res->args, res->argsLen * sizeof(*(res->args)));
      }

      // Store the location of the token in the array
      res->args[res->argsLen - 1] = token;
    }
  }

  return res;
}

void destroyCommand(command_t *c) {
  free(c->args);
  free(c);
}

// Helper functions for string comparison functions, so that the std library
// functions can easily be replaced if Computation II decides we can't
// use them again
inline bool strEqual(const char *a, const char *b) { return strcmp(a, b) == 0; }

inline long strToInt(const char *str) { return strtol(str, NULL, 10); }

// Initialization function
int init(world_t *w) {
  char *line = NULL;
  size_t len = 0;
  command_t *split;
  unsigned int width = 1;
  unsigned int height = 1;
  unsigned int readvar;

  fprintf(stderr, "Starting initialization\n");

  // Keep reading lines
  while (getline(&line, &len, stdin) != 0) {
    // Skip empty lines
    if (strEqual(line, "\n")) {
      continue;
    }

    // Fetch the command
    split = readCommand(line);

    // Switch by command
    if (strEqual(split->cmd, "ready")) {
      break;
    } else if (strEqual(split->cmd, "rows") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      height = readvar;

      fprintf(stderr, "- map height: %d\n", readvar);
    } else if (strEqual(split->cmd, "cols") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      width = readvar;

      fprintf(stderr, "- map width: %d\n", readvar);
    } else if (strEqual(split->cmd, "turns") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->turns = readvar;

      fprintf(stderr, "- turns: %d\n", readvar);
    } else if (strEqual(split->cmd, "viewradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->viewRadius = readvar;

      fprintf(stderr, "- view radius: %d\n", readvar);
    } else if (strEqual(split->cmd, "attackradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->attackRadius = readvar;

      fprintf(stderr, "- attack radius: %d\n", readvar);
    } else if (strEqual(split->cmd, "spawnradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->spawnRadius = readvar;

      fprintf(stderr, "- spawn radius: %d\n", readvar);
    } else if (strEqual(split->cmd, "player_seed") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->playerSeed = readvar;

      fprintf(stderr, "- player seed: %d\n", readvar);
    } else if (strEqual(split->cmd, "loadtime") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->loadTime = readvar;

      fprintf(stderr, "- load time: %d\n", readvar);
    } else if (strEqual(split->cmd, "turntime") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->turnTime = readvar;

      fprintf(stderr, "- turn time: %d\n", readvar);
    } else {
      fprintf(stderr, "Unknown command: '%s'\n", split->cmd);
    }

    // Dealloc
    destroyCommand(split);
  }

  // Set remaining values
  fprintf(stderr, "Allocating map");
  w->map = newMap(width, height);

  // Dealloc line
  free(line);

  // Send 'go' to stdout and flush
  printf("go\n");
  fflush(stdout);

  // Debug print
  fprintf(stderr, "Finished initialization\n");
  printMap(w->map, stderr);

  return true;
}

// Play function. Plays the ants game
bool play(world_t *w, game_t *g) {
  bool end = false;
  char *line = NULL;
  size_t len = 0;
  command_t *split;
  vec2_t pos;

  // Read information
  while (getline(&line, &len, stdin) != 0) {
    // Skip empty lines
    if (strEqual(line, "\n")) {
      continue;
    }

    // Fetch the command
    split = readCommand(line);

    // Switch by command
    if (strEqual(split->cmd, "go")) {
      // Go, end of info
      break;
    } else if (strEqual(split->cmd, "end")) {
      // End game
      end = true;
    } else if (strEqual(split->cmd, "turn") && split->argsLen == 1) {
      // Current turn
      w->turns = strToInt(split->args[0]);
    } else if (strEqual(split->cmd, "f") && split->argsLen == 2) {
      // Food at (x,y)
      pos.x = strToInt(split->args[0]);
      pos.y = strToInt(split->args[1]);
    } else if (strEqual(split->cmd, "w") && split->argsLen == 2) {
      // Water at(x,y)
      pos.x = strToInt(split->args[0]);
      pos.y = strToInt(split->args[1]);
    } else if (strEqual(split->cmd, "a") && split->argsLen == 3) {
      // Ant at(x,y) owned by (owner)
      pos.x = strToInt(split->args[0]);
      pos.y = strToInt(split->args[1]);
    } else if (strEqual(split->cmd, "h") && split->argsLen == 3) {
      // Anthill at (x,y) owned by (owner OR 0)
      pos.x = strToInt(split->args[0]);
      pos.y = strToInt(split->args[1]);
    } else {
      fprintf(stderr, "Unknown command: '%s'\n", split->cmd);
    }

    // Dealloc
    destroyCommand(split);
  }

  // Perform our own turn
  if (!end) {
  }

  // Dealloc
  free(line);

  return !end;
}

// Main function. Returns 0 if there was no error
int main() {
  // World and game
  world_t *world = newWorld();
  game_t *game = newGame();

  // Initialize and play
  if (init(world)) {
    while (play(world, game)) {
      // Debug print
      fprintf(stderr, "Finished turn, %d turns passed\n", world->turns);
      printMap(world->map, stderr);
    };
  }

  // Deallocate memory
  destroyWorld(world);
  destroyGame(game);

  // We don't have any special exit codes
  return 0;
}