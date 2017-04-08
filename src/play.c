#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "play.h"
#include "util.h"
#include "world.h"

// Order builds a packet to order an ant that we own to move in a certain
// direction
static inline void order(ant_t *ant, direction_t dir) {
  printf("o %d %d %c\n", ant->position.x, ant->position.y, dir);
  fprintf(stderr, "Out: %d %d %c\n", ant->position.x, ant->position.y, dir);
}

// Play function. Plays the ants game
bool play(world_t *w) {
  unsigned int i;

  // Game ended flag
  bool end = false;

  // Line reading variables
  char *line = NULL;  // Line currently read. Must dealloc
  size_t len = 0;     // Length of the line read
  command_t *split;   // Split command

  // Generics
  ant_t *ant;
  hill_t *hill;
  food_t *food;
  cell_t *cell;

  // Clear the map
  if (w->ants) {
    for (i = 0; i < w->antCount; i++) {
      ant = w->ants[i];

      cell = w->map->cells[ant->position.x][ant->position.y];
      cell->content.empty = NULL;
      cell->state = stateLand;

      free(ant);
    }
    free(w->ants);
    w->antCount = 0;
  }

  if (w->foods) {
    for (i = 0; i < w->foodCount; i++) {
      food = w->foods[i];

      cell = w->map->cells[food->position.x][food->position.y];
      cell->content.empty = NULL;
      cell->state = stateLand;

      free(food);
    }
    free(w->foods);
    w->foodCount = 0;
  }

  if (w->hills) {
    for (i = 0; i < w->hillCount; i++) {
      hill = w->hills[i];

      cell = w->map->cells[hill->position.x][hill->position.y];
      cell->content.empty = NULL;
      cell->state = stateLand;

      free(hill);
    }
    free(w->hills);
    w->hillCount = 0;
  }

  // Read the current state of the world
  fputs("Reading turn information\n", stderr);
  while (getline(&line, &len, stdin) != 0) {
    // Skip empty lines
    if (strEqual(line, "\n")) {
      continue;
    }

    fprintf(stderr, "In: %s", line);

    // Fetch the command
    split = readCommand(line);

    // Switch by command
    if (strEqual(split->cmd, "go")) {
      // Go, end of info
      break;
    } else if (strEqual(split->cmd, "end")) {
      // End game
      end = true;
      break;
    } else if (strEqual(split->cmd, "turn") && split->argsLen == 1) {
      // Current turn
      w->turns = strToInt(split->args[0]);
    } else if (strEqual(split->cmd, "f") && split->argsLen == 2) {
      // Food at (x,y)
      food = (food_t *)malloc(sizeof(food_t));
      food->position.x = strToInt(split->args[0]);
      food->position.y = strToInt(split->args[1]);

      addFood(w, food);
    } else if (strEqual(split->cmd, "w") && split->argsLen == 2) {
      // Water at(x,y)

      cell_t *c =
          w->map->cells[strToInt(split->args[0])][strToInt(split->args[1])];
      c->content.ant = NULL;
      c->state = stateWater;
    } else if (strEqual(split->cmd, "a") && split->argsLen == 3) {
      // Ant at(x,y) owned by (owner)
      ant = (ant_t *)malloc(sizeof(ant_t));
      ant->position.x = strToInt(split->args[0]);
      ant->position.y = strToInt(split->args[1]);
      ant->alive = true;
      ant->task = taskIdle;
      ant->owner = (uint8_t)strToInt(split->args[2]);

      addAnt(w, ant);
    } else if (strEqual(split->cmd, "d") && split->argsLen == 3) {
      // Dead ant at(x,y) owned by (owner)
      // We don't care about this
    } else if (strEqual(split->cmd, "h") && split->argsLen == 3) {
      // Anthill at (x,y) owned by (owner OR 0)
      hill = (hill_t *)malloc(sizeof(hill_t));
      hill->position.x = strToInt(split->args[0]);
      hill->position.y = strToInt(split->args[1]);
      hill->owner = (uint8_t)strToInt(split->args[2]);

      addHill(w, hill);
    } else {
      fprintf(stderr, "Unknown command: '%s'\n", split->cmd);
    }

    // Dealloc
    destroyCommand(split);
  }

  // Perform our own turn
  if (!end) {
    fputs("Playing our turn\n", stderr);

    // Figure the general direction to the nearest food item or anthill
    // We need food to spawn new ants
    // Search for the nearest food, so that we can move towards it
    // Control the ants
    for (i = 0; i < w->antCount; i++) {
      ant = w->ants[i];

      if (!ant->alive || ant->owner != 0) {
        continue;
      }

      fprintf(stderr, "Computing move of ant %d\n", i);

      // Reset the task
      ant->task = taskExplore;

      // Values for looking around us
      long x, y;
      long xNul, yNul;
      long xRel, yRel;

      xNul = (long)ant->position.x;
      yNul = (long)ant->position.y;

      // Scan our surroundings
      for (x = xNul - w->viewRadius; x <= (xNul + w->viewRadius); x++) {
        for (y = yNul - w->viewRadius; y <= (yNul + w->viewRadius); y++) {
          xRel = x - xNul;
          yRel = y - yNul;

          // Check whether this cell is within this ant's viewradius
          if ((xRel == 0 && yRel == 0) ||
              (xRel * xRel) + (yRel * yRel) > w->viewRadius) {
            continue;
          }

          cell = getCellAt(w->map, x, y);
          switch (cell->state) {
            case stateAnt:

              break;
            case stateAntOnHill:

              break;
            case stateFood:
              fputs("Food is in radius. Immediately move towards it\n", stderr);

              break;
            case stateUnknown:
              // If we see something unknown, assume it's land
              cell->state = stateLand;
              break;
          }
          cell->lastSeen = w->turns + 1;
        }
      }

      // If we've got nothing from our viewradius, then start exploring
      fputs("Nothing to do. Start exploring\n", stderr);
      if (getCellAt(w->map, xNul - 1, yNul)->state != stateWater) {
        order(ant, dirNorth);
      } else if (getCellAt(w->map, xNul, yNul + 1)->state != stateWater) {
        order(ant, dirEast);
      } else if (getCellAt(w->map, xNul + 1, yNul)->state != stateWater) {
        order(ant, dirSouth);
      } else if (getCellAt(w->map, xNul, yNul - 1)->state != stateWater) {
        order(ant, dirWest);

      } else {
        fputs("Ant is stuck\n", stderr);
      }
    }

    // TODO
    puts("go\n");
  }

  // Dealloc
  free(line);

  return !end;
}