#include "includs.h"


int main(int argc, char *argv[]){
	int size1 = atoi(argv[4]);
	int size2 = atoi(argv[5]);
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int res;
	char **arr=malloc(1000 * sizeof(char*));
	FILE *fp = fopen(argv[2], "r");
	FILE *filePointer = fopen(argv[3], "w"); 

	if  (argc != 6){
		printf( "Invalid number of arguments\n");
		exit(1);
	}
	
	secondaryMemory = malloc(size1*sizeof(char*));
	for ( int i = 0 ; i < size1 ; i++ ){
		secondaryMemory[i] = (char*)malloc(1000);
		strcpy(secondaryMemory[i],"");
	}
	
	for ( int i = 0 ; i <size2 ; i++ )
		enqueueFunc(i,"");
	
	
	if ( strcmp(argv[1],"1") == 0)
		status = 1;
	
	else if (strcmp(argv[1],"0") == 0)
		status = 2;


	if (fp == NULL)
		exit(EXIT_FAILURE);
	int i = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		char *ptr = strtok(line, " ");
		do{
			arr[i] = malloc((strlen(ptr)+1)* sizeof(char));
			strcpy(arr[i],ptr);
			ptr = strtok(NULL, " ");
			i++;
		}while (ptr != NULL);
		if(strcmp(arr[0],"read")==0){
			if(strstr(arr[1],"\n")!=NULL){
				arr[1][strlen(arr[2])-2] = '\0';
			}
			readFunc(atoi(arr[1]));
		}
		if(strcmp(arr[0],"write")==0){
			if(strstr(arr[2],"\n")!=NULL){
				arr[2][strlen(arr[2])-2] = '\0';
			}

			writeFunc(atoi(arr[1]),arr[2]);
		}
		if(strstr(arr[0],"print")!=NULL){
			fprintf(filePointer,"SecondaryMemory = [");
			for(int j = 0 ; j<size1; j++){
				fprintf(filePointer,"%s, ",secondaryMemory[j]);
			}
			fprintf(filePointer,"] \n");
		}
		i=0;
	}
	fclose(fp);
	fclose(filePointer);
	if (line)
		free(line);

	
	for (i = 0; i < size1; i++)
        	free(secondaryMemory[i]);
    	free(secondaryMemory);

	for (i = 0; i <=2; i++)
        	free(arr[i]);
    	free(arr);
	memory* temp2=temp1;
	do{
		memory * tmp = temp2->next;
		free(temp2->data);
		free(temp2);
		temp2 = tmp;
	}while(temp2);
	return 0;
}

