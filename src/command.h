#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
  char *cmd;       // the actual command
  char **args;     // args array
  size_t argsLen;  // length of the args array
} command_t

command_t* readCommand(const char* cmd);
void destroyCommand(command_t* c);

#endif