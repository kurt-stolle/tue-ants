#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "play.h"
#include "util.h"
#include "world.h"

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
  ant_t *ant;
  long maxRadius = (long)sqrt(w->viewRadius2);

  // Iterate over all ants
  fputs("Searching for our own ants\n", stderr);
  for (unsigned int i = 0; i < w->antCount; i++) {
    ant = w->ants[i];

    if (ant->owner == w->localPlayer) {
      fputs("Found an ant, scanning area\n", stderr);
      // This ant is owned by us
      cell_t *cell;
      long x, y;
      long xNul, yNul;
      long xRel, yRel;

      xNul = (long)ant->position.x;
      yNul = (long)ant->position.y;

      for (x = xNul - maxRadius; x <= (xNul + maxRadius); x++) {
        for (y = yNul - maxRadius; y <= (yNul + maxRadius); y++) {
          xRel = x - xNul;
          yRel = y - yNul;

          // Check whether this cell is within this ant's viewradius
          if ((xRel == 0 && yRel == 0) ||
              (xRel * xRel) + (yRel * yRel) > w->viewRadius2) {
            continue;
          }

          cell = getCellAt(w->map, x, y);
          switch (cell->state) {
            case stateAnt:
              removeAnt(w, cell->content.ant);
              break;
            case stateAntOnHill:
              removeAnt(w, cell->content.ant);
              break;
            case stateFood:
              removeFood(w, cell->content.food);
              break;
            case stateUnknown:
              cell->state = stateLand;
              break;
          }
          cell->lastSeen = w->turns + 1;
        }
      }
    }
  }

  // Read information
  fputs("Reading turn information\n", stderr);
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
      itemptr.food->position.x = strToInt(split->args[0]);
      itemptr.food->position.y = strToInt(split->args[1]);

      addFood(w, itemptr.food);
    } else if (strEqual(split->cmd, "w") && split->argsLen == 2) {
      // Water at(x,y)

      cell_t *c =
          w->map->cells[strToInt(split->args[0])][strToInt(split->args[1])];
      c->content.ant = NULL;
      c->state = stateWater;
    } else if (strEqual(split->cmd, "a") && split->argsLen == 3) {
      // Ant at(x,y) owned by (owner)
      itemptr.ant = (ant_t *)malloc(sizeof(ant_t));
      itemptr.ant->position.x = strToInt(split->args[0]);
      itemptr.ant->position.y = strToInt(split->args[1]);
      itemptr.ant->alive = true;
      itemptr.ant->owner = (uint8_t)strToInt(split->args[2]);

      addAnt(w, itemptr.ant);
    } else if (strEqual(split->cmd, "d") && split->argsLen == 3) {
      // Dead ant at(x,y) owned by (owner)
      itemptr.ant = (ant_t *)malloc(sizeof(ant_t));
      itemptr.ant->position.x = strToInt(split->args[0]);
      itemptr.ant->position.y = strToInt(split->args[1]);
      itemptr.ant->alive = false;
      itemptr.ant->owner = (uint8_t)strToInt(split->args[2]);

      addAnt(w, itemptr.ant);
    } else if (strEqual(split->cmd, "h") && split->argsLen == 3) {
      // Anthill at (x,y) owned by (owner OR 0)
      itemptr.hill = (hill_t *)malloc(sizeof(hill_t));
      itemptr.hill->position.x = strToInt(split->args[0]);
      itemptr.hill->position.y = strToInt(split->args[1]);
      itemptr.hill->owner = (uint8_t)strToInt(split->args[2]);

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