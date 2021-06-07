#ifndef DECLARATION_H
#define DECLARATION_H
typedef struct memory{
	int key;
	char* data;
	struct memory *next;
	struct memory *prev;
}memory;

char **secondaryMemory;
memory *temp1=NULL;
memory* currentNode = NULL;
memory *table = NULL;
int status = -1;
void enqueueFunc(int,char*);
void dequeueFunc(int key);
void lruSwapFunc(memory*);
char *readFunc(int key);
void writeFunc(int key, char* data);
#endif

