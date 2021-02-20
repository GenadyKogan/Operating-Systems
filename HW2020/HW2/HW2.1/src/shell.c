
/*Global Includes and definitions*/
#include "../headers/globals.h"

/*Dev Created headers*/
#include "../headers/single_commands.h"
#include "../headers/piped_commands.h"


/*Shell functions*/
char* ScanFromUser();
int Tokenize(char*,char***);
boolean hasPipeCall(char**,int);


int main(){
//Shell Main 
    char **command;
    char *buffer;
    pid_t  fork_value;
    int status;
    char *usr =getenv("USER");
    char cwd[1024]; 
    int size=0;
    
    printf("---Starting Custom Shell---\n");
    printf("---------------------------\n");


    while(true)
    {
        /*
            Shell Main Loop
        */
       while(wait(NULL) > 0);
       getcwd(cwd, sizeof(cwd)); 
       printf("%s:%s >> ",usr,cwd);
       buffer = ScanFromUser();
       size=Tokenize(buffer,&command);

        char *script = command[0];

        boolean pipecall=hasPipeCall(command,size);

        if(pipecall){ //Has multiple commands with pipecall

            fork_value=fork();
            if(fork_value) //Parent Process
            {
                waitpid(fork_value,&status, WUNTRACED || WNOHANG );
                if(status == -1){
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }

            }
            else //Child Process
            {
                execute_piped(command,size);
                perror("Command Error");
                exit(EXIT_FAILURE);
            }
        }

        else {// Execute Single Command
            if(strcmp(command[0],"cat")==0 && size > 1 && strcmp(command[1],">")==0)
                signal(SIGINT, signal_handler);
            else {// return normal SIGINT HANDLER
                signal(SIGINT, SIG_DFL);
            }
                execute_single_command(command,size);
        }

        size=0;
    }


    return 0;
}



int Tokenize(char* org,char*** args){
    /*
    Takes a string and breaks it into a words array
    args variable will get the pointer to the array
    */
    char *arg;
    char **temp_args_array;
    arg = strtok(org," ");
    int size=1;

    temp_args_array=(char**)malloc(sizeof(char*)*size+1);
    temp_args_array[size-1]=(char*)malloc(sizeof(char));
    strcpy(temp_args_array[0],arg);


    while(arg = strtok(NULL," ")){
        size++;
        temp_args_array=(char**)realloc(temp_args_array,size*(sizeof(char*)));
        temp_args_array[size-1]=(char*)malloc(sizeof(char));
        strcpy(temp_args_array[size-1],arg);
    }
        temp_args_array=(char**)realloc(temp_args_array,size*(sizeof(char*))+sizeof(char*));
        temp_args_array[size]=(char*)malloc(sizeof(char));
        temp_args_array[size]=NULL;
        *args=temp_args_array;

    return size;
}



boolean hasPipeCall(char** args,int size){
/*
    Checks User command for pipe call
*/

    for(int i=0;i<size;i++)
    {    
        if(strcmp("|",args[i])==0) //Pipe call found
            return true;
    }
    return false;
}

