#include "../headers/piped_commands.h"
#include "../headers/globals.h"
#include "../headers/single_commands.h"



void execute_piped(char **args,int size){

    char input[BUFF_SIZE]; // next Command input
    char **sliced_command;
    pid_t f_val;
    int s=0;
    int out,in;
    int index=0;
    int status;

    int c_pipe[2];
    out = dup(1);
    in = dup(0);

    if(pipe(c_pipe)==-1){ // Create a pipe for commands communication
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if(pipeCount(args,size) > 1 ){
        fprintf(stderr,"pipe Error: Too many pipes\n");
        exit(EXIT_FAILURE);
    }

    f_val = fork();
    if(f_val){
        close(c_pipe[1]); //Parent Dosent Write
        dup2(c_pipe[0],0); //Switch Stdin
        waitpid(f_val,&status,WUNTRACED || WNOHANG);
        index++;
    }
    else {
        close(c_pipe[0]); // Child Dosent Read
        dup2(c_pipe[1],1); //Switch Stdout
        sliced_command = getCommand(args,index);
        s = amountOfArgs(sliced_command);
        execute_single_command(sliced_command,s);
        exit(EXIT_SUCCESS);
    }

        dup2(out,c_pipe[1]); //Switch Stdout
        sliced_command = getCommand(args,index);
        s = amountOfArgs(sliced_command);
        if(!isSupported(sliced_command,s)){
            perror("Invalid Command");
            exit(EXIT_FAILURE);
        }
        execvp(sliced_command[0],sliced_command);
}

char** getCommand(char **args,int index){
    char **ptr = args;
    char **sliced_command = (char**)malloc(sizeof(char*));
    int size =0;
    boolean flag = false;
    while(index){
        flag = true;
        ptr++;
        if(strcmp("|",*ptr)==0)
            index--;
    }
    
    if(flag) {
        ptr++;
    }

    while(*ptr && strcmp(*ptr,"|")){
        size++;
        sliced_command=(char**)realloc(sliced_command,size*(sizeof(char*)));
        sliced_command[size-1]=(char*)malloc(sizeof(char));
        strcpy(sliced_command[size-1],*ptr);
        ptr++;
    }
        sliced_command=(char**)realloc(sliced_command,size*(sizeof(char*))+sizeof(char*));
        sliced_command[size]=(char*)malloc(sizeof(char));
        sliced_command[size]=NULL;

    return sliced_command;

}

boolean isPiped(char **args, int index){
    char **ptr = args;
    boolean flag = index > 0 ;
    while(index){
        ptr++;
        if(strcmp("|",*ptr)==0)
            index--;
    }
    if(flag)
        ptr++;

    while(*ptr){
        if(strcmp(*ptr,"|")==0){
            return true;
        }
        ptr++;
    }

    return false;
}



boolean isSupported(char **command,int size){
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
        if(size==1 || strcmp("-r",command[1])==0)
            isValid=true;
    }

    else if(strcmp(command[0],"grep")==0){
        if(size==2 || strcmp("-c",command[2])==0)
            isValid=true;
    }

    else if(strcmp(command[0],"man")==0){
        if(size==2 && (strcmp("exit",command[1])==0 || strcmp("man",command[1])==0 || strcmp("grep",command[1])==0 || strcmp("sort",command[1])==0 ||strcmp("cp",command[1])==0 || strcmp("wc",command[1])==0 || strcmp("cat",command[1])==0 || strcmp("cd",command[1])==0 || strcmp("pwd",command[1])==0 ))
            isValid=true;
    }

    return isValid;
}


int pipeCount(char** args,int size){
    int count = 0;

    for(int i=0;i<size;i++){
        if(strcmp(args[i],"|")==0)
            count++;
    }

    return count;

}