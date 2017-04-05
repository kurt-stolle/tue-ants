#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "play.h"
#include "world.h"

static const char delim[] = " \n";

// Play function. Plays the ants game
bool play(world_t *w) {
  // Game ended flag
  bool end = false;

  // Line reading variables
  char *line = NULL;  // Line currently read. Must dealloc
  size_t len = 0;     // Length of the line read
  command_t *split;   // Split command

  // When reading commands, we'll occupy one of these, but never multiple
  // Optimize memory by using a union
  union {
    ant_t *ant;
    hill_t *hill;
    food_t *food;
  } itemptr;

  // Clean the map around our viewradius
  // Because we're about to receive new information about it
  // We need to perform a circle iteration at each ant we own
  // TODO - for now just clear the whole map
  fputs("Reloading map", stderr);
  destroyMap(w->map);
  w->map = newMap();

  // Read information
  fputs("Reading turn information", stderr);
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
      itemptr.food = (food_t *)malloc(sizeof(food_t));
      itemptr.food.x = strToInt(split->args[0]);
      itemptr.food.y = strToInt(split->args[1]);

      addFood(w, itemptr.food);
    } else if (strEqual(split->cmd, "w") && split->argsLen == 2) {
      // Water at(x,y)

      cell_t *c = w->map->cells[split->args[0]][split->args[1]];
      c.content = NULL;
      c.state = stateWater;
    } else if (strEqual(split->cmd, "a") && split->argsLen == 3) {
      // Ant at(x,y) owned by (owner)
      itemptr.ant = (ant_t *)malloc(sizeof(ant_t));
      itemptr.ant.x = strToInt(split->args[0]);
      itemptr.ant.y = strToInt(split->args[1]);
      itemptr.ant.owner = strToInt(split->args[2]);

      addAnt(w, itemptr.ant);
    } else if (strEqual(split->cmd, "h") && split->argsLen == 3) {
      // Anthill at (x,y) owned by (owner OR 0)
      itemptr.hill = (hill_t *)malloc(sizeof(hill_t));
      itemptr.hill.x = strToInt(split->args[0]);
      itemptr.hill.y = strToInt(split->args[1]);
      itemptr.hill.owner = strToInt(split->args[2]);

      addHill(w, itemptr.hill);
    } else {
      fprintf(stderr, "Unknown command: '%s'\n", split->cmd);
    }

    // Dealloc
    destroyCommand(split);
  }

  // Perform our own turn
  if (!end) {
    fputs("Playing our turn", stderr);

    // TODO

    puts("go\n");
  }

  // Dealloc
  free(line);

  return !end;
}