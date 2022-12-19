#include <stdio.h>
#include <string.h>
#include "text_manipulation.h"

int remove_spaces(const char *source, char *result, int *num_spaces_removed) {  
    int i=0,j=0,k = 0,start =0,end = 0, len, numspaces  =0;

    
    if(source!=NULL){
        len = strlen(source);
    }
    if (source == NULL || len == 0){
        return FAILURE;
    }
    
    while(source[i]==' '||source[i]=='\n'|| source[i]=='\t'){
        numspaces++;
        i++;
    } 
    start = i;
    i=len-1;
    while(i>start && (source[i] ==' '||source[i]=='\n'||source[i]=='\t')){
        numspaces++;
        i--;
    }
    end = i;
    for(j = start; j<=end;j++){
        result[k]=source[j];
        k++;
    }    
    result[k] = '\0';
    if(num_spaces_removed !=NULL){
        *num_spaces_removed = numspaces;
    }

    return SUCCESS;

}
  


int center(const char *source, int width, char *result) {   
    int spaces,len;
    int i =0, j=0;
    if(source!=NULL){
        len = strlen(source);
    }
    if (source == NULL || len == 0 || width < len){
        return FAILURE;
    }
    if ((width - len)%2!=0){
        spaces = ((width - len))-1;
    } else {
        spaces = (width -len);
    } 
    while (i<len+spaces){
        if((i<spaces/2) || (i >=((spaces/2)+len))){
            result[i] = ' ';
        }
        else {
            result[i] = source[j];
            j++;
        }
        i++;
    }
    result[i] = '\0';

    return SUCCESS;
}
