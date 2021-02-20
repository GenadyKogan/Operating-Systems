#include "../headers/single_commands.h"
#include "../headers/globals.h"
#include <signal.h>

volatile sig_atomic_t is_child = 0;


void signal_handler(int signum) {
    keepScanning=false;

    if(is_child){
        printf("\n");
        exit(EXIT_SUCCESS);
    }

}
   
void execute_single_command(char** args,int size){
    if(isBuiltIn(args[0])){
        execute_builtIn(args);
    }

    else{
        pid_t f_val = fork(); //Prepare to execute not builtIn command
        int status;
        if(f_val) //Parent Process
        {
            wait(NULL);
            if(status == -1){
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            return ; //finished child Process return to main Loop
        }
        else if(!f_val && isValidCommand(args,size)){
            is_child=1;
            execute_not_builtIn(args,size);    
        }
        else {
            if(args[0][0]!='\n')
                fprintf(stderr,"'%s' is not supported\n",args[0]);
            exit(EXIT_FAILURE);
        }
    }

}

void execute_builtIn(char** args){
    if(strcmp(args[0],"cd")==0){
                chdir(args[1]);
                return ;
            }
            int f_val = fork();
            if(!f_val){ // Child Process to call these commands
                 if(strcmp(args[0],"pwd")==0){
                    execv("/bin/pwd", args);
                    exit(1);
                    }
                else if(strcmp(args[0],"exit")==0){
                    kill(0,2);
                }
            }
}



void execute_not_builtIn(char **args,int size){
    if(strcmp(args[0],"cat")==0){
        if(strcmp(">",args[1])==0){
            FILE *fp =NULL;
            char *input;
            fp=fopen(args[2],"w+");
            if (!fp)
                perror("fopen");
            
            while(keepScanning){
                input=ScanFromUser();
                fprintf(fp,"%s\n",input);
            }
                keepScanning=true;
                fclose(fp);
                exit(EXIT_SUCCESS);
        }
        else
            execv("/bin/cat", args);
    }

    else if(strcmp(args[0],"nano")==0){
        execv("/bin/nano",args);
    }

    else if(strcmp(args[0],"wc")==0){
        execvp("wc",args);
        perror("wc");
        exit(EXIT_FAILURE);
    }

    else if(strcmp(args[0],"cp")==0){
        execvp("cp",args);
        perror("cp");
        exit(EXIT_FAILURE);
    }

    else if(strcmp(args[0],"sort")==0){
        execvp("sort",args);
        perror("sort");
        exit(EXIT_FAILURE);
    }


    else if(strcmp(args[0],"grep")==0){
        execvp("grep",args);
        perror("grep");
        exit(EXIT_FAILURE);
    }

    else if(strcmp(args[0],"man")==0){
        printMan(args);
        exit(EXIT_FAILURE);
    }

}

void printMan(char **args){
    if(strcmp("pwd",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("cd",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("cat",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("wc",args[1])==0){
        execvp("man",args);
    }
    
    else if(strcmp("cp",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("sort",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("grep",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("man",args[1])==0){
        execvp("man",args);
    }

    else if(strcmp("exit",args[1])==0){
        execvp("man",args);
    }
    else {
        printf("Command %s is not supported\n",args[1]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}