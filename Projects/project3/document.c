
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
            if (i < (doc->number_of_paragraphs - 1))
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
        /* Check adding more than max*/
        if(doc->number_of_paragraphs<=MAX_PARAGRAPHS){
            for(i = number_paragraphs ;i >= paragraph_number;i--){
                doc->paragraphs[i + 1] = doc->paragraphs[i];
            }
            doc->paragraphs[paragraph_number].number_of_lines = 0;
        }
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

/* Function that allows texts to be replaced*/    
int replace_text(Document *doc, const char *target, const char *replacement){
    int i,j, doc_paragraphs,replacementlength,targetlength;
    char *pos, str[MAX_STR_SIZE + 1] = {0};
    
    if (doc == NULL || target == NULL || replacement == NULL){
        return FAILURE;
    }
    
    doc_paragraphs = doc->number_of_paragraphs;
    for (i = 0; i < doc_paragraphs; i++) {
        for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) {
            pos = strstr(doc->paragraphs[i].lines[j], target);
            while (pos != '\0') {
                strcpy(str, pos);
                strcpy(pos, "");
                strcat(pos, replacement);
                /* Joins the new string together*/
                replacementlength = strlen(replacement);
                targetlength = strlen(target);
                strcat(pos + replacementlength, str + targetlength);
                pos = strstr(pos + targetlength, target);	       
            }
        }
    } 
    return SUCCESS;
}

/* Highlight function */
int highlight_text(Document *doc, const char *target){
    char new_string[MAX_STR_SIZE+1]={""};
   
    if (doc ==NULL || target==NULL){
        return FAILURE;
    }
  
    strcat(new_string,HIGHLIGHT_START_STR);
    strcat(new_string,target);
    strcat(new_string,HIGHLIGHT_END_STR);

    replace_text(doc,target,new_string);
    return SUCCESS;
}
int remove_text(Document *doc, const char *target){
   
    if (doc ==NULL || target == NULL){
        return FAILURE;
    }
    
    replace_text(doc,target,"");
    return SUCCESS;
}
static int is_empty(const char *str) {
  if (strlen(str)==0){
    return 1;
  }
  while (*str != '\0') {
    if (!isspace((unsigned char)*str))
      return 0;
    str++;
  }
  return 1;
}
/* The load file function that loads a file and fills up*/
int load_file(Document *doc, const char *filename){
    FILE* file;
    char line[MAX_STR_SIZE+1],symbol, str[MAX_STR_SIZE+1];
    int isempty, paragraph_no,terminate;
    if (doc == NULL || filename == NULL || doc->number_of_paragraphs > MAX_PARAGRAPHS){
        return FAILURE;
    }
    paragraph_no = 1;
    /* Opens a file*/
    if ((file = fopen(filename, "r")) == NULL) {
        return FAILURE;
    } else {
        add_paragraph_after(doc,0);
        while (fgets(line, MAX_STR_SIZE+1, file) != NULL || terminate==0) {
            char *pos;
            if((pos = strchr(line,'\n'))!=NULL){
                *pos = '\0';
            }
            /* Checks if isempty*/
            isempty = is_empty(line);
            if (isempty == 1){
                if (doc->number_of_paragraphs<=MAX_PARAGRAPHS){
                    add_paragraph_after(doc,paragraph_no);
                    paragraph_no++;
                }
            } else{
                sscanf(line," %c%c",&symbol,str);
                if (symbol!='#'){
                    append_line(doc,paragraph_no,line);
                }
            }
            if(feof(file)){
                terminate=0;
            }
        } 
    }
    return SUCCESS;
}
/* Save document function that saves the document onto a file*/
int save_document(Document *doc, const char *filename){
    char line[MAX_STR_SIZE+1]; int i, j;
    FILE*outfile;
    if (doc == NULL || filename == NULL){
        return FAILURE;
    }
    if ((outfile = fopen(filename,"w")) == NULL){
        fclose(outfile);
        return FAILURE;
    } else{ 
        for (i = 0; i < doc->number_of_paragraphs;i++){
            for (j = 0; j<doc->paragraphs[i].number_of_lines;j++){
                strcpy(line, doc->paragraphs[i].lines[j]);
                if(j<doc->paragraphs[i].number_of_lines){
                    strcat(line,"\n");
                }
                fputs(line,outfile);
            }
            if(doc->number_of_paragraphs>=(i+1)){
                fputs("\n",outfile);
            }
        }
    } 
    fclose(outfile);
    return SUCCESS;
}
