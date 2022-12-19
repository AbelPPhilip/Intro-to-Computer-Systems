/*
Name: Abel Philip 
UID: 117868235
Grace ID: aphilip2
Project Description: The following project is a userinterface that allows users to create a formatted document
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sysexits.h>
#include "document.h"
/* Execute function prototype*/
static int execute(Document *doc, char *line);
/* Main Function that accepts input from the user*/
int main(int argc, char *argv[]) {
    Document doc;
    FILE *file;
    char line[MAX_STR_SIZE + 1], comment[MAX_STR_SIZE + 1], hashtag;
    int num_commands;
    /*Initializing*/
    if (init_document(&doc, "main_document") != FAILURE) {
        /* If statement when more than two inputs provided*/
        if (argc > 2){
            fprintf(stderr, "Usage: user_interface\n");
            fprintf(stderr, "Usage: user_interface <filename>\n");
            exit(EX_USAGE);
        }/* When only one input provided*/
        else if (argc == 1) {
            char exitcommand[5], extra[MAX_STR_SIZE];
            int exitcommands;
            file = stdin;
            printf("> ");
            fgets(line, MAX_STR_SIZE + 1, stdin);
            if(strlen(line)<1025){
                while (strcmp(line, "exit\n")!=0 && strcmp(line, "quit\n")!=0) {
                    char*pos;
                    sscanf(line, " %c%s", &hashtag, comment); 
                    if ((pos=strchr(line,'\n'))!=NULL){
                        *pos = '\0';
                    }
                    if (hashtag != '#') {
                        execute(&doc, line);
                    }
                    printf("> ");
                    fgets(line, MAX_STR_SIZE + 1, stdin);
                }   
                /* If quit is called, it checks if the quit or exit is valid*/
                if (strstr(line,"quit")!=NULL || strstr(line,"exit")!=NULL){
                    exitcommands = sscanf("%s %s",exitcommand,extra);
                    if(exitcommands >1){
                        printf("Invalid Command\n");
                    }
                }
            }
            else{
                printf("Invalid Command\n");
            }
        }/* when a filename is specified*/
        else if (argc == 2) {
            file = fopen(argv[1],"r");
            if (file != NULL) {     
                while (fgets(line, MAX_STR_SIZE, file)!=NULL) {
                    if(strlen(line)<1025){
                        sscanf(line," %c%s",&hashtag,comment);
                        if (hashtag!='#'){/* Condition ignores Hashtag */
                            if(strcmp(line,"quit\n")!=0 && strcmp(line,"exit\n")!=0){
                                char*pos;
                                if((pos=strchr(line,'\n'))!=NULL){
                                    *pos  = '\0';
                                }
                                execute(&doc,line); 
                            }
                                /* Checks the validity of the quit and exit functions. */
                            if (strstr(line,"quit")!=NULL || strstr(line,"exit")!=NULL){
                                char exitcommand[5], extra[MAX_STR_SIZE];
                                num_commands = sscanf("%s%s",exitcommand,extra);
                                if (num_commands>1){
                                    printf("Invalid Command\n");
                                }
                            }
                            
                        } 
                    } else{
                        printf("Invalid Command\n");
                    }
                } 
            } else{/* When file cannot be opened. */
                fprintf(stderr, "%s cannot be opened.\n", argv[1]);
                exit(EX_OSERR);
            }
        }
    } 
    fclose(file);
    exit(EXIT_SUCCESS);
}
/* Helper function to recognize command and execute their respective functions*/
/* The valid int keeps a track of wether commands are failing or passing*/
static int execute(Document *doc, char *line) {
    int valid = 0;
    int check = 0;  
    /* If command is add paragraph*/
    if (strstr(line, "add_paragraph_after") != NULL) {
        char command[MAX_STR_SIZE + 1], extra[1025];
        int paragraph_no, executed,num_commands; 
        /*This format follows for the following if statements num_commands checks how many inputs were provided*/
        num_commands = sscanf(line, "%s%d%s", command, &paragraph_no, extra);
        if (num_commands ==2 && paragraph_no >= 0) {
            check = add_paragraph_after(doc, paragraph_no);
            if (check == FAILURE){
                printf("add_paragraph_after failed\n");
            }
               executed = SUCCESS;
        } else { executed = FAILURE;}
        valid = executed;
    }/* Append line function*/
    else if (strstr(line, "append_line") != NULL) {
        char command[MAX_STR_SIZE + 1], linestr[MAX_STR_SIZE + 1], extra[MAX_STR_SIZE + 1];
        int paragraph_no, executed, num_commands;

        num_commands = sscanf(line, "%s%d%s", command, &paragraph_no, extra);
        if (num_commands == 3 && paragraph_no > 0) {
            if (strchr(line, '*') != NULL) {
                strcpy(linestr, strchr(line, '*') + 1);
                check = append_line(doc,paragraph_no, linestr);
                if (check == FAILURE) {
                    printf("append_line failed\n");
                }
                    executed = SUCCESS;
            }else {
                executed = FAILURE;
            }
        }else {executed = FAILURE;};
        valid = executed;
    }/* Print Document command */
    else if (strstr(line, "print_document") != NULL) {
        int executed,num_commands;
        char command[MAX_PARAGRAPH_LINES+1], extra[MAX_STR_SIZE+1];
        /* Checks if only one command is give in the line*/
        num_commands = sscanf(line,"%s%s",command, extra);
        if (num_commands == 1){
            check = print_document(doc);
            executed = SUCCESS;
        }else{ executed = FAILURE;}
        valid = executed;
    }
    /* Add line after command*/
    else if (strstr(line, "add_line_after") != NULL){
        char command[MAX_STR_SIZE + 1], linestr[MAX_STR_SIZE + 1];
        char extra[MAX_STR_SIZE + 1];
        int paragraph_no, line_no, executed, num_commands;
        num_commands = sscanf(line, "%s%d%d%s", command, &paragraph_no,&line_no, extra);
        if (num_commands == 4 && paragraph_no > 0 && line_no>=0) {
            if (strchr(line, '*') != NULL) {
                strcpy(linestr, strchr(line, '*') + 1);
                check = add_line_after(doc,paragraph_no,line_no,linestr);
                if (check == FAILURE) {
                    printf("add_line_after failed\n");
                }
                executed = SUCCESS;
            }else{
                executed = FAILURE;
            }
        }else {executed = FAILURE;};
        valid = executed;
    }/* Remove line command*/
    else if(strstr(line, "remove_line")!= NULL){
        char command[MAX_STR_SIZE+1],extra[MAX_STR_SIZE+1];
        int paragraph_no,line_no,executed, num_commands;
        num_commands = sscanf(line, "%s%d%d%s",command,&paragraph_no, &line_no,extra);
        
        if (num_commands==3 && paragraph_no > 0 && line_no > 0){
            check  = remove_line(doc,paragraph_no,line_no);
            if (check == FAILURE){
                printf("remove_line failed\n");
            }
                executed = SUCCESS;

        } else{executed = FAILURE;}
        valid = executed;
    }/* Load File command*/
    else if (strstr(line,"load_file")!= NULL){
        char command[MAX_STR_SIZE+1], filename[MAX_STR_SIZE+1],extra[MAX_STR_SIZE+1];
        int values,executed;
        values = sscanf(line, "%s %s%s",command,filename,extra);
        /* Checking if only two values are provided*/
        if (values == 2 && filename!=NULL){
            check = load_file(doc,filename);
            if (check == FAILURE){
                printf("load_file failed\n");
            }
            executed = SUCCESS;
 
        }else {executed = FAILURE;}
        valid = executed;
    }
    /* Replace text command*/
    else if(strstr(line,"replace_text")!=NULL){
        char command [MAX_STR_SIZE+1], replacement[MAX_STR_SIZE+1],target[MAX_STR_SIZE+1];
        int executed,num_inputs;
        char *quote1,*quote2,*quote3,*quote4;
        
        num_inputs = sscanf(line,"%s%s%s",command,target,replacement);
        /*Using strchr to attain the pointer to the first instance of a quotation mark  */
        quote1 = strchr(line, '\"');
        
        /* Checking if only 3 inputs provided, then checking for the subsequent 4 quotation marks. */
        if (num_inputs == 3){ 
            if(quote1 != NULL) {
                quote2 = strchr(quote1 + 1, '\"');
                if (quote2 != NULL) {
                    quote3 = strchr(quote2 + 1, '\"');
                    if (quote3 != NULL) {
                    quote4 = strchr(quote3 + 1, '\"');
                        if (quote4 != NULL) {
                            /*If we know all quotations are valid, we continue to extract the word inside the quotation pointers*/
                            strncpy(target, quote1 + 1, quote2 - quote1);
                            target[quote2 - (quote1 + 1)] = '\0';
                            strncpy(replacement, quote3 + 1, quote4 - quote3);
                            replacement[quote4 - (quote3 + 1)] = '\0';
                            /*With the words */
                            check = replace_text(doc,target,replacement);    
                            if (check == FAILURE) {
                                printf("replace_text failed\n");
                            } executed = SUCCESS;         	      
                        }else{ executed = FAILURE;}
                    }else{executed = FAILURE;}	 
                }else {executed = FAILURE;}
            }else {executed = FAILURE;}
        } else { executed = FAILURE;}
        valid = executed;
    }
    /* Highlight text command execution */
    else if(strstr(line,"highlight_text")!=NULL){
        char command[MAX_STR_SIZE + 1], target[MAX_STR_SIZE + 1];
        char extra[MAX_STR_SIZE + 1], *quote1,*quote2;
        int num_values,executed;
      
        num_values = sscanf(line, "%s%s", command, extra);
        quote1 = strchr(line, '\"');
        /* Checking if the only 2 inputs are provided and if                                                         */
        if (num_values == 2 && quote1 != NULL) {
            quote2 = strchr(quote1+1,'\"');
            if (quote2 != NULL) {
                strncpy(target, quote1 + 1, quote2 - quote1);
                target[quote2 - (quote1 + 1)] = '\0';
                check = highlight_text(doc,target);  
                executed = SUCCESS;  
            }else{executed = FAILURE;}
        } else{executed = FAILURE;}
        valid = executed;
    }/* Save Document */ 
    else if(strstr(line,"save_document")!=NULL){
        char command[MAX_STR_SIZE+1], filename[MAX_STR_SIZE],extra[MAX_STR_SIZE+1];
        int executed, num_commands;
        num_commands = sscanf(line, "%s%s%s",command, filename,extra);
        /* Checking if two commands are entered*/
        if (num_commands == 2){
            check = save_document(doc,filename);
            if (check == FAILURE){
                printf("save_document failed\n");
            }
            executed = SUCCESS;
        }else{ executed = FAILURE;}
        valid = executed;
    } 
    /* Reset Document Command */
    else if(strstr(line,"reset_document")!=NULL){
        int executed,num_commands;
        char command[MAX_STR_SIZE+1],extra[MAX_STR_SIZE+1];
        num_commands = sscanf("%s%s",command,extra);
        if (num_commands == 1){
            check = reset_document(doc);
            executed = SUCCESS;
        }else {executed = FAILURE;}
        valid = executed;
    } 
    /* Remove Text Function*/
    else if(strstr(line,"remove_text")!=NULL){
        char command[MAX_STR_SIZE+1],text[MAX_STR_SIZE+1];
        int num_commands, executed;
        char *quote1, *quote2;
        num_commands = sscanf(line, "%s%s", command, text);
        quote1 = strchr(line, '\"');
        if (num_commands == 2 && quote1 != NULL) {
            quote2 = strchr(quote1+1,'\"');
            if (quote2 != NULL) {
                /* Extracts the word inside the quotation*/
                strncpy(text, quote1 + 1, quote2 - quote1);
                text[quote2 - (quote1 + 1)] = '\0';
                check = remove_text(doc,text);  
                executed = SUCCESS;  
            } else{executed=FAILURE;}
        } else{executed = FAILURE;}
        valid = executed;
    }
    /* If Valid is failure*/
    if (valid == FAILURE){
        printf("Invalid Command\n");
    }
    return valid; 
}



    



    
