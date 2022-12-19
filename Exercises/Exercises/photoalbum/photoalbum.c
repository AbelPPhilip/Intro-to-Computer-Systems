#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "photoalbum.h"
Photo *create_photo(int id, const char *description){
    Photo *photo = malloc(sizeof(Photo));
    if (photo == NULL){
        return NULL;
    }
    if (description != NULL){
        photo->description = malloc(strlen(description)+1);
        if (photo->description == NULL){
            return NULL;
        }
        strcpy(photo->description,description);
    }else{
        photo->description = NULL;
    }
    photo->id = id;
    return photo;
}
void print_photo(Photo *photo){
    if (photo !=NULL){
        if (photo->description!=NULL){
            printf("Photo Id: %d, Description: %s", photo->id,photo->description);
        }else{
            printf("Photo Id: %d, Description: %s",photo->id,"None");
        }  
    } 
   
}
void destroy_photo(Photo *photo){
    if(photo != NULL){
       free(photo->description);
       free(photo); 
    }
}

void initialize_album(Album *album){
    if (album != NULL){
        album->size=0;
    } 
}
void print_album(const Album *album){
    int i = 0, size;
    
    if (album != NULL){
        size = album->size;
        if (size>0){
            for (i = 0; i<size;i++){
                print_photo(album->all_photos[i]);
                printf("%c",'\n');
            } 
        }else{
            printf("%s","Album has no photos.\n");
        }
    } 
    
}
void destroy_album(Album *album){
    int i, size;
    if (album != NULL){
       size= album->size;
        for(i = 0;i<size;i++){
            destroy_photo(album->all_photos[i]);
        }
        album->size = 0;
    } 
}
void add_photo_to_album(Album *album, int id, const char *description){
    /*if(album!= NULL){
        if (album->size < MAX_ALBUM_SIZE){
            Photo *photo = create_photo(id,description);
            if(photo!=NULL){
                album->all_photos[album->size] = photo;
                (album->size)++; 
            }    
        }
        
    }*/
    if(album!= NULL){
        if (album->size < MAX_ALBUM_SIZE){
            Photo *photo = create_photo(id,description);
            if(photo!=NULL){
                album->all_photos[album->size] = photo;
                (album->size)++; 
            }    
        }
        
    }
    
}