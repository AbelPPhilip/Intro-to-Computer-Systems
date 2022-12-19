/* 
Name: Abel P.
UID: 117868234
Grace ID: aphilip2
Project Description: A calendar program to practice memory allocation. 
*/
#include <stdio.h>
#include "calendar.h"
#include <stdlib.h>
#include <string.h>
#include "event.h"

/* Initialize calendar function that initializes the calendar with the provided parameters */
int init_calendar(const char *name, int days, int (*comp_func) (const void *ptr1, const void *ptr2), void (*free_info_func) (void *ptr), Calendar ** calendar){
    if (name == NULL || (*calendar) == NULL || days<1){
        return FAILURE;
    }
    
    (*calendar) = malloc(sizeof(Calendar));
    if(calendar){
        (*calendar)->name = malloc(strlen(name)+1);
        if ((*calendar)->name){
            strcpy((*calendar)->name,name);
            (*calendar)->events = calloc(days,sizeof(Event));
            (*calendar)->days = days;
            (*calendar)->comp_func = comp_func;
            (*calendar)->free_info_func = free_info_func;
            (*calendar)->total_events = 0;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/* The Print Calendar function that prints out the whole calendar */
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all){
    Event *curr;
    int i = 0;
    if (calendar && output_stream){
        if(print_all == 1){/* If the option is provided as one.*/
            fprintf(output_stream,"Calendar's Name: \"%s\"\n",calendar->name);
            fprintf(output_stream,"Days: %d\n",calendar->days);
            fprintf(output_stream,"Total Events: %d\n",calendar->total_events);
        }
        printf("\n");
        printf("**** Events ****\n");
        if(calendar->total_events>0){/*Iterating through each event in a day*/
            for (i = 0; i <calendar->days;i++){
                curr = calendar->events[i];
                fprintf(output_stream,"Day %d\n",i+1);
                while(curr){
                    fprintf(output_stream,"Event's Name: \"%s\", ",curr->name);
                    fprintf(output_stream,"Start_time: %d, ",curr ->start_time);
                    fprintf(output_stream,"Duration: %d\n",curr->duration_minutes);
                    curr = curr->next;
                }
            }
        }  
        return SUCCESS;
    }
    return FAILURE;
}

/*The Add event function that adds events according to the comp func*/
int add_event(Calendar *calendar, const char *name, int start_time,int duration_minutes, void *info, int day){
    Event * new_event,*head,*curr,*found, *prev = NULL;
    if (calendar && name && (start_time >= 0 && start_time <= 2400) && duration_minutes > 0 && (day >= 1 && day <= calendar->days)){
        if(find_event(calendar,name,&found)==FAILURE){/* Checking if the event exists in the calenedar*/
            /* Creating a new event to place into the linked list*/
            new_event = malloc(sizeof(Event));
            if (new_event){
                new_event->name =  malloc(strlen(name)+1);
                if(new_event->name){
                    strcpy(new_event->name,name);
                    new_event->info = info;
                    new_event->start_time = start_time;
                    new_event->duration_minutes = duration_minutes; 
                }
            } 
            /* Identifying the head of the calendar*/  
            head = calendar->events[day-1];
            curr = head;
            if (curr){
                while(curr && calendar->comp_func(new_event,curr)>0){
                    prev = curr;
                    curr = curr->next;
                }   
                new_event->next = curr;
                if (prev == NULL){/* If the pointer hasn't moved so adding to the beginning of the list*/
                    calendar->events[day-1] = new_event;
                }else{/* Adding into the middle */
                    prev->next = new_event;
                }
            }else{/* Adding an event when the event linked list is not even initialized*/
                calendar->events[day-1] = new_event;
                new_event->next = NULL;
            }  (calendar->total_events)++;
            return SUCCESS;
        }
    }
    return FAILURE;
}
/* Finding an event in the calendar*/
int find_event(Calendar *calendar, const char *name, Event **event){
    Event *curr;int i;
    
    if (calendar && name){
        if(calendar->days>0){  
            for (i=0;i<calendar->days;i++){
                curr = calendar->events[i];
                while(curr){
                    if(strcmp(name,curr->name)==0){
                        if(event){
                            *event = curr;
                        }
                        return SUCCESS;
                    }
                    curr = curr->next;
                }
                
            } 
        }
    }
   return FAILURE;
}
/* Finding an event in a day and setting the parameter node to that found node. */
int find_event_in_day(Calendar *calendar, const char *name, int day, Event **event){
    Event *curr;
    if (calendar && name && day>0){
        if (day<=calendar->days){
            curr = calendar->events[day-1];
            while(curr){
                if(strcmp(name,curr->name)==0){
                    if(event){
                            *event = curr;
                    }
                    return SUCCESS;
                }
                curr=curr->next;
            }
        }
    }
    return FAILURE;
}
/* Remove event function that removes a particular node from the linked list in any day*/
int remove_event(Calendar *calendar, const char *name){
    Event *curr,*prev;
    int i =0;
    if (calendar && name){
        for (i=0;i<calendar->days;i++){
            curr = calendar->events[i];
            prev = NULL;
            while(curr && strcmp(curr->name,name)!=0){
                prev = curr;
                curr = curr->next;
            }
            if (curr){
                if (prev==NULL){ 
                    calendar->events[i] = curr->next;
                    curr->next = NULL;
                }else{
                    prev->next = curr->next;
                }
                /* Freeing the current variable*/
                free(curr->name);
                if (calendar->free_info_func){
                    if (curr->info) {
                        calendar->free_info_func(curr->info);
                    }
                }
                free(curr);

                (calendar->total_events)--;
                return SUCCESS;
            } 
        }
        
    }
    return FAILURE; 
 
}
/* Get event info function that retrieves the event info*/
void *get_event_info(Calendar *calendar, const char *name){
    Event *curr;
    if(find_event(calendar,name,&curr)==FAILURE){
        return NULL;
    }
    return curr->info;
}
/*Clear Calendar clears each event in every day one by one*/
int clear_calendar(Calendar *calendar){
    int i; 
    if (calendar){
        if (calendar->days > 0){
            for(i = 0; i<calendar->days;i++){
                clear_day(calendar,i+1);
            }
            return SUCCESS;
        }
    }
    return FAILURE;
}
/* Clear day function that clears the events in a day*/
int clear_day(Calendar *calendar, int day){
    Event *curr,*delete; 
    if (calendar && day>0 && day<=calendar->days){
        curr = calendar->events[day-1]; 
        while (curr){
                /*Creating a temporary node to delete so the pointer node can shift to the next event in the linked list*/
                delete = curr; 
                curr = curr->next;

                /* Freeing the temporary node*/
                free(delete->name);
                if (calendar->free_info_func){
                    if (delete->info) {
                        calendar->free_info_func(delete->info);
                    }
                }
                free(delete); 
                (calendar->total_events)--;
        }
	    calendar->events[day - 1] = NULL; /* Setting that linked list to null*/
        return SUCCESS;
    }
    return FAILURE;
}
/*Destroy calendar frees every event in each day and finally frees the calendar itself.*/
int destroy_calendar(Calendar *calendar){
    if (calendar==NULL){
        return FAILURE;
    }
    clear_calendar(calendar);
    free(calendar->name);
    free(calendar->events);
    free(calendar);
    return SUCCESS; 
}