#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"

static const char delim[] = " \n";

// Command splitting
command_t *readCommand(char *cmd) {
  command_t *res = malloc(sizeof(*res));
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