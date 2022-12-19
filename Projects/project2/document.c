#include <stdio.h>
#include <string.h>
#include "document.h"
/*
Name: Abel Philip
Class: CMSC216 0203*/

/* 
Initialize function that sets the paragraph number to 0 and sets the name*/
int init_document(Document *doc, const char *name){
    if (doc == NULL || name == NULL ||strlen(name)> MAX_STR_SIZE){
        return FAILURE;
    }
    doc->number_of_paragraphs =0;
    strcpy(doc->name,name);
    return SUCCESS;
}
/*
Sets the document number of paragraphs to 0*/
int reset_document(Document *doc){
    if(doc == NULL){
        return FAILURE;
    }
    doc->number_of_paragraphs = 0;
    return SUCCESS;
}

/*
Iterates through the document struct to print out each paragraph line by line*/
int print_document(Document *doc){
    int i,j;
    if (doc==NULL){
        return FAILURE;
    }
    
    printf("Document name: \"%s\"\n",doc->name);
    printf("Number of Paragraphs: %d\n",doc->number_of_paragraphs);
    for (i = 0;i < doc->number_of_paragraphs;i++){
        if(doc->paragraphs[i].number_of_lines > 0){
            for (j = 0;j < doc->paragraphs[i].number_of_lines;j++){
                printf("%s\n",doc->paragraphs[i].lines[j]);
            }
            printf("\n");
        }
        
    }
    return SUCCESS;
}

/*
Function to Add paragraph after a given paragraph numer*/
int add_paragraph_after(Document *doc, int paragraph_number){
    int i = 0, number_paragraphs;
    /* Checks for the validity of the parameters*/
    if (doc == NULL){
        return FAILURE;
    }
    number_paragraphs = doc ->number_of_paragraphs;
    if (paragraph_number > number_paragraphs){
        return FAILURE;
    }
    /*Adds a paragraph to the beginning of the document*/
    if(paragraph_number == 0 && number_paragraphs <= 0){
        doc->paragraphs[0].number_of_lines = 0;
    }/*Adds a paragraph to the end of the document*/
    else if(paragraph_number == number_paragraphs){
        doc->paragraphs[number_paragraphs].number_of_lines=0;
    }
    else{ /* Adds a paragraph to after the given paragraph number*/
        for(i = number_paragraphs ;i >= paragraph_number;i++){
            doc->paragraphs[i + 1] = doc->paragraphs[i];
        }
        doc->paragraphs[paragraph_number].number_of_lines = 0;
    }
    (doc->number_of_paragraphs)++;
    
    return SUCCESS;
}
/* Function to add a line in given paragraph number after a given line.*/
int add_line_after(Document *doc, int paragraph_number, int line_number,const char *new_line){
    int i, number_lines;
    /*Checks the validity of the parameters*/
    if (doc == NULL || new_line == NULL || paragraph_number > doc->number_of_paragraphs){
        return FAILURE;
    }
    number_lines = doc->paragraphs[paragraph_number-1].number_of_lines;
    if(number_lines >= MAX_PARAGRAPH_LINES || line_number>number_lines){
        return FAILURE;
    }
    /*Adds a line to the beginning of the paragraph*/
    if (line_number == 0 && number_lines <= 0){
        strcpy(doc->paragraphs[paragraph_number-1].lines[0],new_line);
    }/*Adds a line to the end of the paragraph */
    else if (line_number == doc->paragraphs[paragraph_number-1].number_of_lines){
        strcpy(doc->paragraphs[paragraph_number-1].lines[number_lines],new_line);
    }
    else{/*Adds a line after the given line number in the given paragraph*/
        for(i = number_lines; i >= line_number;i--){
            strcpy(doc->paragraphs[paragraph_number-1].lines[i+1],doc->paragraphs[paragraph_number-1].lines[i]);
        }
        strcpy(doc->paragraphs[paragraph_number-1].lines[line_number],new_line);
    }
    (doc->paragraphs[paragraph_number-1].number_of_lines)++;
    return SUCCESS;
} 
/* Function to get the number of lines in a paragraph*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines){
    int numparas, numlines;
    /* Checking the validity of the parameters*/
    if (doc == NULL || number_of_lines == NULL) {
        return FAILURE;
    }
    numparas = doc->number_of_paragraphs;
    if(paragraph_number > numparas){
        return FAILURE;
    }
    /*Sets the number of lines parameter to numlines*/
    numlines = doc->paragraphs[paragraph_number].number_of_lines;
    *number_of_lines = numlines;
    return SUCCESS;
}
/*Function to add a line to the end of the paragraph*/
int append_line(Document *doc, int paragraph_number, const char *new_line){
    int doc_lines;
    /* Checking validity of the parameter*/
    if (doc == NULL || new_line == NULL || paragraph_number < 0){
        return FAILURE;
    }
    doc_lines  = doc->paragraphs[paragraph_number-1].number_of_lines;
    if(paragraph_number > doc->number_of_paragraphs || doc_lines > MAX_PARAGRAPH_LINES){
        return FAILURE;
    }
    /*if the paragraph is empty, adds the line to the beginning of the paragraph*/
    if(doc_lines == 0){
        strcpy(doc->paragraphs[paragraph_number-1].lines[0],new_line);
    }
    else{/*Calls the add line function to add a line to the end of the paragraph*/
        add_line_after(doc,paragraph_number,doc_lines,new_line);
        
    }
    doc_lines++;
    doc->paragraphs[paragraph_number-1].number_of_lines = doc_lines;   
    return SUCCESS;
}

/*Function to remove a given line from a given paragraph number*/
int remove_line(Document *doc, int paragraph_number, int line_number){
    int i = 0,doc_lines;
    /*Checking the validity of the parameters*/
    if (doc == NULL){
        return FAILURE;
    }
    doc_lines = doc->paragraphs[paragraph_number-1].number_of_lines; 
    if(paragraph_number > doc->number_of_paragraphs || line_number > doc_lines){
        return FAILURE;
    }
    /*Shifts all the lines to cover up the line intended to be removed*/
    for(i = line_number-1;i<doc_lines-1;i++){
        strcpy(doc->paragraphs[paragraph_number-1].lines[i],doc->paragraphs[paragraph_number-1].lines[i+1]);
    }
    doc_lines--;
    doc->paragraphs[paragraph_number-1].number_of_lines = doc_lines;
    return SUCCESS;
}
/*Function to load a document with a given array of strings*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines){
    int i, doc_paragraphs;
    /*Checking the validity of the parameters*/
    if (doc == NULL || data == NULL){
        return FAILURE;
    }
    doc_paragraphs = doc->number_of_paragraphs;
    /*Adds a beginning paragraph */
    add_paragraph_after(doc,doc_paragraphs);
    for(i = 0; i < data_lines;i++){
        if (strcmp(data[i],"")==0){
            doc_paragraphs++;
            add_paragraph_after(doc,doc_paragraphs);
        } else{
            append_line(doc,doc_paragraphs+1,data[i]);
        }
    }
    return SUCCESS;
    
}
/* A helper function that returns the index of the last character in a string */  
static int find_end_pos(char*str){
    return strlen(str) - 1; 
}
/* Function that allows texts to be replaced*/    
int replace_text(Document *doc, const char *target, const char *replacement){
    int num_paragraphs, num_paragraph_lines, target_length, replacement_length;
    int i,j,k,x;
    char str[MAX_STR_SIZE];
    /* Checking the validity of parameters*/
    if (doc == NULL || target == NULL || replacement == NULL){
        return FAILURE;
    }
    /*Initializes the target length and replacement length*/
    target_length = strlen(target);
    replacement_length = strlen(replacement);

    num_paragraphs = doc->number_of_paragraphs;
    /*Iterates through every paragraph present in the doc*/
    for(i = 0; i < num_paragraphs; i++){
        num_paragraph_lines = doc->paragraphs[i].number_of_lines;
        /*Iterates through every line in the paragraph*/
        for(j = 0; j < num_paragraph_lines;j++){
            int linelength = strlen(doc->paragraphs[i].lines[j]);
            /*Iterates through every character of the line*/
            for (k = 0; k + target_length < linelength;k++){
                int index = k;
                /*Collects the number of characters equal to the target length*/
                for(x = 0;x < target_length;x++){
                    char character = doc->paragraphs[i].lines[j][index];
                    str[x]=character;
                    index++;
                }
                /*Checks if the collected characters is equal to the target string*/
                if (strcmp(str,target)==0){
                    int y, fill, fillindex, endindex, shift;
                    /*If the replacement is empty, the target is removed by shifting each character in the array*/
                    if (strcmp(replacement,"")==0){
                        endindex = find_end_pos(doc->paragraphs[i].lines[j]);
                        for (y = k + target_length;y <= endindex;y++){
                            shift = (target_length);
                            doc->paragraphs[i].lines[j][y - shift]=doc->paragraphs[i].lines[j][y];
                        }
                        doc->paragraphs[i].lines[j][y-shift]='\0';
                    } else{
                        /*If the replacement length is bigger than the target length, all elements in the array
                        is to be shifted to the right*/
                        if (replacement_length > target_length){
                            endindex = find_end_pos(doc->paragraphs[i].lines[j]);
                            for (y = endindex;y >= index;y --){
                                shift = (replacement_length-target_length);
                                doc->paragraphs[i].lines[j][y+shift] = doc->paragraphs[i].lines[j][y];
                            }
                            doc->paragraphs[i].lines[j][y+shift] = '\0';
                        } else if(target_length > replacement_length){
                            endindex = find_end_pos(doc->paragraphs[i].lines[j]);
                            for(y = index;y < endindex+1;y++){
                                shift = (target_length-replacement_length);
                                if(y - shift > 0){
                                    doc->paragraphs[i].lines[j][y-shift] = doc->paragraphs[i].lines[j][y];
                                }
                            } 
                            doc->paragraphs[i].lines[j][y-shift] = '\0';
                    
                        }
                        /* After the space for the replacement string is made by shifting, the number of spaces
                        are filled in the original line*/
                        fill =0;
                        fillindex = 0;
                        for(fill = k;fill < k + replacement_length;fill++){
                            doc->paragraphs[i].lines[j][fill] = replacement[fillindex];
                            fillindex++;
                        }
                        /*Once the replacement is filled, the index of the character is moved to the end of replacement*/
                        if(replacement_length > target_length){ 
                            k = index+((replacement_length-target_length)-1);
                        }
                        else if (replacement_length < target_length){
                            k = index - ((target_length-replacement_length)+1);
                        }
                    }
                }
            }
        }
    }
    return SUCCESS;
}


int highlight_text(Document *doc, const char *target){
    char new_string[MAX_STR_SIZE+1]={""};
    /* Checking the validity of the parameters*/
    if (doc ==NULL || target==NULL){
        return FAILURE;
    }
    /* Calling the strcat Functions to create a string with the target surrounded by [ and ]*/
    strcat(new_string,HIGHLIGHT_START_STR);
    strcat(new_string,target);
    strcat(new_string,HIGHLIGHT_END_STR);
    /* Calling the replace text function to replace the text with the new string*/
    replace_text(doc,target,new_string);
    return SUCCESS;
}
int remove_text(Document *doc, const char *target){
    /*Checking the validity of the parameters*/
    if (doc ==NULL || target == NULL){
        return FAILURE;
    }
    /*Calling the function to replace the target text with an empty string*/
    replace_text(doc,target,"");
    return SUCCESS;
}

