#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "play.h"
#include "command.h"

static const char delim[] = " \n";

// Play function. Plays the ants game
bool play(world_t *w, game_t *g) {
  bool end = false;
  char *line = NULL;
  size_t len = 0;
  command_t *split;
  vec2_t pos;

  // Clean the map around our viewradius
  // Because we're about to receive new information about it

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