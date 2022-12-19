#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define MAX_ASSIGNMENTS 50
/* Method Prototypes*/
double calculate_mean(int scores[],int delayeddays[],double points_penalty, int total_assignments);
double calculate_stdev(double mean, int scores[], int delayeddays[], double points_penalty, int total_assignments);
void drop(int score[], int weightage[], int total_assignments, int dropped_assignments);
double calculate_numericscore(int scores[], int weightage[], int delayeddays[],int points_penalty, int dropped_assignments, int total_assignments);
double find_max(int scores[], int weightage[], int total_assignments);

/*Main Method*/
int main(){
    /*Nessecary Variable declaration*/
    double mean, stddev, numeric_score;
    char status;
    int dropped_assignments, total_assignments, total_weightage, points_penalty;
    int i = 0, index;
    /* Arrays Used to store assignment data*/
    int assignments[MAX_ASSIGNMENTS] = {0}, scores[MAX_ASSIGNMENTS]={0}, weightage[MAX_ASSIGNMENTS]={0}, delayeddays[MAX_ASSIGNMENTS] = {0};
    /* Copy Arrays*/
    int copyassignments[MAX_ASSIGNMENTS] = {0}, copyscores[MAX_ASSIGNMENTS]={0}, copyweightage[MAX_ASSIGNMENTS]={0}, copydelayeddays[MAX_ASSIGNMENTS] = {0};
    /*Receiving Input*/
    scanf("%d %d %c",&points_penalty, &dropped_assignments, &status);
    scanf("\n%d",&total_assignments);
    while(i<total_assignments){
        scanf("\n%d, %d, %d, %d",&assignments[i],&scores[i],&weightage[i],&delayeddays[i]);
        i++;
    }
    /* Copying All data to clone arrays*/
    for (i=0;i<total_assignments;i++){
        copyassignments[i] = assignments[i];
        copyscores[i] = scores[i];
        copyweightage[i] = weightage[i];
        copydelayeddays[i] = delayeddays[i];
    }
    /*Output Printing*/
    total_weightage = 0; 
    for (i = 0; i < total_assignments;i++){
        total_weightage += weightage[i];
    }
    if (total_weightage > 100){
        printf("ERROR: Invalid values provided");
    }
    else{ 
        /*Function Calls*/
        mean = calculate_mean(scores,delayeddays,points_penalty,total_assignments);
        stddev = calculate_stdev(mean, scores, delayeddays, points_penalty, total_assignments);
        numeric_score = calculate_numericscore(scores,weightage,delayeddays,points_penalty, dropped_assignments,total_assignments);
        printf("Numeric Score: %5.4f\n",numeric_score);
        printf("Points Penalty Per Day Late: %d\n",points_penalty);
    
        if (dropped_assignments>=total_assignments){
            dropped_assignments = total_assignments -1;
        }
        printf("Number of Assignments Dropped: %d\n",dropped_assignments);
        printf("Values Provided: \n");
        printf("Assignment, Score, Weight, Days Late\n");
        index = 1;
        while(index<=total_assignments){
            for (i = 0; i < total_assignments;i++){
                if(copyassignments [i] == index){
                    printf("%d, %d, %d, %d\n",copyassignments[i],copyscores[i],copyweightage[i],copydelayeddays[i]);
                }
            }
            index ++;
        }  
        if (status == 'Y' || status == 'y'){
            printf("Mean: %5.4f, Standard Deviation: %5.4f",mean,stddev);
        }
    }
    
    return 0;
}

/* The Drop Function that drops the assignments with the lowest value*/
void drop(int scores[], int weightage[], int total_assignments, int dropped_assignments){
    double value = 0;
    int dropped = 0;
    int i,index = 0;
    double min_value = scores[0]*weightage[0];
    /* Algorithm to Drop Assignments in each iteration*/ 
    while(dropped<dropped_assignments){
        if (dropped < total_assignments-1){
            min_value = find_max(scores,weightage,total_assignments);
            for(i = 0; i < total_assignments;i ++){
                value = scores[i]*weightage[i];
                if (value != 0){
                    if (value < min_value || (value == min_value && i < dropped)){
                        min_value = value;
                        index = i; 
                    }
                } 
            }
        }
        scores[index] = 0;
        weightage[index] = 0;  
        dropped ++; 
    }   
}

/*Helper find maximum in array Method for drop algorithm*/
double find_max(int scores[], int weightage[], int total_assignments){
    double max_value = scores[0] * weightage[0];
    int i = 0;
    for(i = 0; i < total_assignments;i ++){
            if ((scores[i] * weightage[i]) > max_value){
                max_value = scores[i] * weightage[i];
            }
    }
    return max_value;
}
/* Numeric Score Calculating Algorithm */
double calculate_numericscore(int scores[], int weightage[], int delayeddays[],int points_penalty, int dropped_assignments, int total_assignments){
    double total_weights,total =0;
    int i;
    
    if (dropped_assignments > 0){
        drop(scores,weightage,total_assignments, dropped_assignments);
    }
    /*Sum of all weights*/
    for (i = 0; i < total_assignments; i++){
        total_weights += weightage[i];
    }
    /*Sum of true scores*/
    for (i = 0; i < total_assignments;i++){
        if(weightage[i]!=0){
           total+= ((scores[i]-(delayeddays[i]*points_penalty))*(weightage[i]/total_weights)); 
        }
        
    }
    
    return total;
    
}

/*Method to calculate Mean*/
double calculate_mean(int scores[],int delayeddays[],double points_penalty, int total_assignments){
   double total;
   int i;
   for (i = 0;i<total_assignments;i++){
        total += (scores[i]-(delayeddays[i]*points_penalty));
    }
    
    return total/total_assignments;
}

/*Method to calculate Standard Deviation*/ 
double calculate_stdev(double mean, int scores[], int delayeddays[], double points_penalty, int total_assignments){
    int i;
    double total = 0;
    for(i = 0; i < total_assignments; i++){
        total += pow(abs(((scores[i]-(delayeddays[i]*points_penalty))-mean)),2);
        /*printf("%f\n", (pow(abs(((scores[i]-(delayeddays[i]*points_penalty))-mean)),2))/2);*/
    }

    return sqrt(total/total_assignments);
}

