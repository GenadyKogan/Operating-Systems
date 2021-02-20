#ifndef SINGLE_COMM
#define SINGLE_COMM

#include "globals.h"

void execute_single_command(char**,int);
void execute_builtIn(char**);
void execute_not_builtIn(char **,int);
void printMan(char **);
void signal_handler(int signum);

#endif