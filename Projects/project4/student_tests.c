#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/* Description here: This test checks ...  */
static int test1() {
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }

   add_event(calendar,"Skiing",800,90,NULL,1);
   return FAILURE;
}

static int test3() {
   Calendar *calendar;
    int days = 10,  start_time_mil = 900, duration_minutes = 50;
    void *info = NULL;
   if (init_calendar("Academic", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "zoo visit", start_time_mil, duration_minutes, info, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      printf("TRYING TO add a same event");
      print_calendar(calendar, stdout, 1);
      add_event(calendar,"lunch",1100,60,NULL,8);
      print_calendar(calendar, stdout, 1);
      printf("As you can see the lunch event is not present in Day 8");
      destroy_calendar(calendar);
   }
   return FAILURE;
}


static int test10(){
   Calendar *calendar;
   int days = 60;
   printf("TESTING ADD EVENT");
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      int i = 0;char event[10];
      int j =0;
      add_event(calendar, "Zoo time ", 700, 60, 
             NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      
      for (i = 4;i<days;i++){
         int time = 100;
         int duration = 30;
         sprintf(event,"event %d",j);
         while (time<1200){
            add_event(calendar,event,time,duration,NULL,i);
            sprintf(event,"event %d",++j);
            
            time+=30;
         }
      }
      print_calendar(calendar,stdout,1);
      printf("Clearing Day 20\n");
      clear_day(calendar,20);
      printf("Clearing Day 59\n");
      printf("Clearing Calendar\n");
      clear_day(calendar,59);
      clear_calendar(calendar);
      
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
   return FAILURE;
}

static int test4(){
   Calendar *calendar;
   Event *found;
   int days = 10;
   printf("TESTING Find EVENT\n");
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      int i = 0;char event[10];
      int j =0;
      add_event(calendar, "Zoo time ", 700, 60, 
             NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      if(find_event(calendar,"Zoo time", &found)==FAILURE){
          printf("Event has not been found, test fails\n");
      }else{
         printf("Event has been found, Test pass\n");
      }   
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
   return FAILURE;
}

static int test5(){
   Calendar *calendar;
   Event *found;
   int days = 10;
   printf("Testing remove Event");
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      int i = 0;char event[10];
      int j =0;
      add_event(calendar, "Zoo time ", 700, 60, 
             NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      print_calendar(calendar,stdout,1);
      remove_event(calendar,"lunch");
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
          printf("Lunch event is removed");
         return destroy_calendar(calendar);
      }
   }
   return FAILURE;
}
static int test6(){
   Calendar *calendar;
   Event *found;
   int days = 10;
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "Zoo time ", 700, 60, NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      print_calendar(calendar,stdout,1);
      if(clear_day(calendar,1)==SUCCESS){
         if (print_calendar(calendar,stdout,1)==SUCCESS){
            printf("Lunch event is removed");
            return destroy_calendar(calendar);
         }
      }
   }
   return FAILURE;
}

static int test7(){
   Calendar *calendar;
   int days = 10;
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "Zoo time ", 700, 60, NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      print_calendar(calendar,stdout,1);
      if(clear_calendar(calendar)==SUCCESS){
         if (print_calendar(calendar,stdout,1)==SUCCESS){
            printf("Calendar Cleared");
            return destroy_calendar(calendar);
         }
      }
   }
   return FAILURE;
}
static int test8(){
   Calendar *calendar; Event *found;
   int days = 10;
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "Zoo time ", 700, 60, NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      print_calendar(calendar,stdout,1);
      if(find_event(calendar,"lunch",&found)==SUCCESS){
         printf("Found, Test Passed");
         return destroy_calendar(calendar);
      }else{
         printf("not Found, Test Failed");
         return destroy_calendar(calendar);
      }
   }
   return FAILURE;
}
static int test9(){
   Calendar *calendar; Event *found;
   int days = 10;
   if (init_calendar("Summer", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar, "Zoo time ", 700, 60, NULL, 1);
      add_event(calendar, "review meeting", 800, 80, NULL, 1); 
      add_event(calendar, "group meeting", 500, 60, NULL, 1);
      add_event(calendar, "lunch", 1200, 45, NULL, 3);
      print_calendar(calendar,stdout,1);
      if(find_event_in_day(calendar,"lunch",3,&found)==SUCCESS){
         printf("Found, Test Passed");
         return destroy_calendar(calendar);
      }else{
         printf("not Found, Test Failed");
         return destroy_calendar(calendar);
      }
   }
   return FAILURE;
}









int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if(test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if(test5() == FAILURE) result = FAILURE;
   if(test6() == FAILURE) result = FAILURE;
   if(test7() == FAILURE) result = FAILURE;
   if(test8() == FAILURE) result = FAILURE;
   if(test9() == FAILURE) result = FAILURE;
   /* IMP NOTE: IF test10 CREATES A larger output than the console can handle, please comment it out!!!*/
   if (test10() == FAILURE) result = FAILURE;

   /*if (test3() == FAILURE) result = FAILURE;*/

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
