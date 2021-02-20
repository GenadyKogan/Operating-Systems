#ifndef GLOBAL_SHELL_DEF
#define GLOBAL_SHELL_DEF


/*Shell imports*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>


/*Shell Definitions*/
#define BUFF_SIZE 1000
typedef enum { false , true } boolean;
#define AMOUNT_OF_COMMANDS 3
#define LEN 5

static volatile boolean keepScanning = true;


/*Global functions*/
boolean isBuiltIn(char*);
boolean isValidCommand(char**,int);
boolean checkCat(char**,int);
int amountOfArgs(char**);
void printArgs(char **);
char* ScanFromUser();

#endif