#include "../headers/globals.h"



boolean isBuiltIn(char *command){

    char b_commands[AMOUNT_OF_COMMANDS][LEN];
    strcpy(b_commands[0],"pwd");
    strcpy(b_commands[1],"cd");
    strcpy(b_commands[2],"exit");
    

    for(int i=0; i<AMOUNT_OF_COMMANDS; i++){
        if(strcmp(b_commands[i],command)==0)
            return true;
    }

    return false;

}


boolean isValidCommand(char **command,int size){
    /* Validate syntax of the command entered */
    boolean isValid = false;
    if(strcmp(command[0],"cat")==0){
        isValid = checkCat(command,size);
    }
    else if(strcmp(command[0],"wc")==0){
        if(size == 2 || size==3 && (strcmp(command[1],"-l")==0 || strcmp(command[1],"-c")==0 || strcmp(command[1],"-w")==0))
            isValid=true;
    }
    else if(strcmp(command[0],"cp")==0){
        if(size==3)
            isValid=true;
    }

    else if(strcmp(command[0],"sort")==0){
        if(size==2 || strcmp("-r",command[1])==0 && size==3)
            isValid=true;
    }

    else if(strcmp(command[0],"grep")==0){
        if(size==1 || strcmp("-c",command[1])==0 || command[1][0]!='-')
            isValid=true;
    }

    else if(strcmp(command[0],"man")==0){
        if(size==2 && (strcmp("exit",command[1])==0 || strcmp("man",command[1])==0 || strcmp("grep",command[1])==0 || strcmp("sort",command[1])==0 ||strcmp("cp",command[1])==0 || strcmp("wc",command[1])==0 || strcmp("cat",command[1])==0 || strcmp("cd",command[1])==0 || strcmp("pwd",command[1])==0 ))
            isValid=true;
    }
    else if(strcmp(command[0],"nano")==0){
        isValid=true;
    }

    return isValid;
}


boolean checkCat(char **args,int size){

    if(size<=1 || size > 3){
        perror("Cat");
        exit(EXIT_FAILURE);
    }

    if(strcmp(">",args[1])==0){
        if(size==3)
            return true;
        else
        {
            return false;
        }
    }

    if(size!=2)
        return false;

    return true;

}

int amountOfArgs(char **args){
    /*Count amount of arguments in command*/
    int amount=0;
    while(*args){
        amount++;
        args++;
    }
    return amount;
}


void printArgs(char **args){
    while(*args){
        printf("%s\n",*args);
        args++;
    }

}

char* ScanFromUser(){
    char *buffer=NULL;
    size_t size=0;
    int string_len;
    string_len=getline(&buffer,&size,stdin);
    if(string_len!=1)
        buffer[string_len-1]='\0';
    else 
        buffer[1]='\0';

    return buffer;
}



