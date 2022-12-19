/*
Name: Abel Philip
UID:  117868234*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"
#include "executor.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sysexits.h>
#include <fcntl.h>
#include <err.h>

/*static void print_tree(struct tree *t);*/
static int aux_execute(int input, int output, struct tree *t);
/*
static void execute_NONE(struct tree *t);
static void execute_AND(struct tree *t);
static void execute_PIPE(struct tree *t);
static void execute_SUBSHELL(struct tree * t);*/

int execute(struct tree *t) { 
   int input_fd = -1, output_fd = -1;
   if (t != NULL){
      aux_execute(input_fd, output_fd, t);
   }
   /*print_tree(t)*/
   return 0;
}


static int aux_execute(int input, int output, struct tree *t){
   pid_t pid; 
   int status; 
   int fd[2];
   if (t-> input != NULL){
         input = open(t->input, O_RDONLY);
         if (input == -1){
           perror("Opening input failed");
           exit(EX_OSERR);
         }
      }
   if (t-> output != NULL){
         output = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664);
         if (output < 0){
            perror("Opening output failed");
            exit(EX_OSERR);
         }
   }
   /* if user input has no conjunction*/
   if (t->conjunction == NONE){
      /*if the command is not exit, it prepares to read other inputs*/
      if (strcmp(t->argv[0],"exit")!= 0){ 
         /*if the command is cd*/
         if (strcmp(t->argv[0],"cd")==0){
            if(t->argv[1]!= NULL){ 
               if(chdir(t->argv[1])<0){
                  perror("Invalid Directory:");
                  exit(EX_OSERR);

               }
            }else{
               if(chdir(getenv("HOME"))<0){
                  perror("Directory Change failed (Home)");
                  exit(EX_OSERR);
               }
            }
         }
         else{ /*handling other commands. */
            
            pid = fork();
            if(pid < 0){/*fork failed*/
               err(EX_OSERR, "fork error");
            }else if(pid != 0){
               wait(&status); 
               return status;  
            }else{  
               if (t->input != NULL && input >= 0){ 
                  if(dup2(input, 0) < 0){
                     perror("(dup2) reading failed");
                     exit(EX_OSERR);
                  } 
                  close(input);
               }
               if(t->output != NULL && output >= 0){
                  int dupstatus;
                  /* Moving the output file into standard output*/
                  dupstatus = dup2(output, 1);
                  if (dupstatus < 0){
                     err(EX_OSERR,"(dup2) writing failed.\n");
                     exit(EX_OSERR);
                  }
                  close(output);
               }
              
               if (execvp(t->argv[0], t->argv)<0){
                  fprintf(stderr, "Failed to execute %s\n", t->argv[0]);    
                  exit(EX_OSERR);
               }
            }
         }
      } else {
         exit(0);
      }
      
   }
   else if (t->conjunction == AND){
      if (aux_execute(input, output, t->left) == 0){
         aux_execute(input, output, t->right);
      }   
   } else if (t->conjunction == OR){
      if (aux_execute(input, output, t->left) != 0){
         aux_execute(input, output, t->right);
      }
   }
   else if(t->conjunction == PIPE){
      int pipestatus; 
      /*
      if (t->left->output && t->right->input){
         printf("Ambiguous output redirect.");
      }else if (t->left->output && t->right->input == NULL){
         printf("Ambiguous input redirect");
      }else if (t->left->output == NULL && )
      */
      if (t->left->output == NULL && t->right->input == NULL){
         pipestatus = pipe(fd);
         if (pipestatus < 0){
            perror("fork error");
         }
         pid = fork();
         if (pid < 0){
            perror("fork failed (PIPE)");
         }
         else if (pid != 0){
            close(fd[1]);
            if (dup2(fd[0], STDIN_FILENO) < 0){
               perror("dup2 error (Parent pipe)");
            }
            aux_execute(fd[0],output,t->right);
            close(fd[0]);
            wait(NULL);
         }else{
            close(fd[0]);
            if (dup2(fd[1],1)<0){
               perror("dup2 error (child pipe)");
            }
            aux_execute(input,fd[1],t->left);
            close (fd[1]);
         }} 
      else if(t->left->output == NULL && t->right->input){
         printf("Ambiguous input redirect.\n");
         fflush(stdout);
      }else{
         printf("Ambiguous output redirect.\n");
         fflush(stdout);
      }
   } else if (t-> conjunction == SUBSHELL){
      pid = fork();
      if (pid < 0){
         perror("Fork failed (SUBSHELL)");
      }
      else if (pid!=0){
         wait(NULL);
      }else{
         aux_execute(input,output,t->left);
         exit(0);
      }
   }
   return 0;

}


/*

static void print_tree(struct tree *t) {
   if (t != NULL) {
      print_tree(t->left);

      if (t->conjunction == NONE) {
         printf("NONE: %s, ", t->argv[0]);
      } else {
         printf("%s, ", conj[t->conjunction]);
      }
      printf("IR: %s, ", t->input);
      printf("OR: %s\n", t->output);

      print_tree(t->right);
   }
}*/




