#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

static const char delim[] = " \n";  // Array of characters,
                                    // used to split the command

command_t *readCommand(char *cmd) {
  command_t *res = malloc(sizeof(*res));  // Allocate memory for
                                          // the resulting command

  // Explicitly set defaults
  res->argsLen = 0;
  res->cmd = NULL;
  res->args = NULL;

  // Token read by the strtok_r function
  char *token;

  // Keep looping until we break the loop manually
  for (;;) {
    // Read cmd until a delimiting char is found
    // The address of the character in the array after the character
    // where the cut has happened will be saved in cmd, so
    // cmd serves essentially as a 'cursor' over the line
    token = strtok_r(cmd, delim, &cmd);

    // If the token equals null, then there is nothing more to read
    if (token == NULL) {
      break;
    }

    // Check whether the cmd field was already filled out, this is
    // always the first thing we'll read.
    if (!(res->cmd)) {
      res->cmd = token;
    } else {
      res->argsLen++;  // Add 1 to the argsLen field

      // Allocate memory to store the argument.
      // This will dynamically make a large enough
      // array to hold all arguments
      res->args = realloc(res->args, res->argsLen * sizeof(*(res->args)));

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