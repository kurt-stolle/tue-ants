#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "init.h"
#include "util.h"

// Initialization function
bool init(world_t *w) {
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
      readvar = (unsigned short)strToInt(split->args[0]);
      w->turns = readvar;

      fprintf(stderr, "- turns: %d\n", readvar);
    } else if (strEqual(split->cmd, "viewradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->viewRadius2 = readvar;

      fprintf(stderr, "- view radius: %d\n", readvar);
    } else if (strEqual(split->cmd, "attackradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->attackRadius2 = readvar;

      fprintf(stderr, "- attack radius: %d\n", readvar);
    } else if (strEqual(split->cmd, "spawnradius2") && split->argsLen == 1) {
      readvar = (unsigned int)strToInt(split->args[0]);
      w->spawnRadius2 = readvar;

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
  puts("go\n");

  // Debug print
  fprintf(stderr, "Finished initialization\n");
  printMap(w->map, stderr);

  return true;
}
