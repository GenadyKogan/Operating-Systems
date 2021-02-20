#ifndef PIPED_COMM
#define PIPED_COMM

#include "globals.h"

void execute_piped(char**,int);
char **getCommand(char**,int);
boolean isPiped(char**,int);
void addInput(char***,char[BUFF_SIZE],int*);
boolean isSupported(char **,int);
int pipeCount(char**,int);

#endif