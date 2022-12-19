/* Implement your shell here */
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sysexits.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX 1024 

int main(){
    pid_t pid;
    char input[MAX+1];
    char cmd[3];
    char *commands[3];
    char extra[MAX+1];
   
    printf("shell_jr: ");
    fflush(stdout);
    while(fgets(input, 1025,stdin) != NULL){
        if(strcmp(input,"exit\n")!=0 && strcmp(input,"hastalavista\n")){
            char*pos;
            if((pos=strchr(input,'\n'))!=NULL){
                *pos  = '\0';
            }
        }else{
            printf("See you\n");
            fflush(stdout);
            exit(0);
        }
    
        sscanf(input,"%s%s",cmd,extra);
        commands[0] = cmd;
        commands[1] = extra;
        if(strstr(cmd,"cd")){
            if(chdir(commands[1]) == -1){
                err(EX_OSERR,"Cannot change to a directory %s",commands[0]);
            }
        } else{
            if((pid = fork())<0){
                err(EX_OSERR,"fork error");
            }
            if (pid){
                wait(NULL);
            } else{
                if(execvp(commands[0], commands)==-1){
                    printf("Failed to execute %s\n", commands[0]);
                    fflush(stdout);
                    exit(EX_OSERR);
                }
            }
        }
        printf("shell_jr: ");
        fflush(stdout);
    
    }
    return 0;
}
