#include <stdio.h>
int draw_rectangle(char, int,int);
int draw_triangle(char, int);
int main(){
	int option;
	printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
	scanf("%d",&option);
	while (option != 0){
		if(option==1){
			int width,length; 
			char character;
			printf("Enter character, width and length: ");
			scanf(" %c %d %d",&character, &width, &length);
			draw_rectangle(character,width,length);
		}	
		else if(option == 2){
			int size;
			char character;
			printf("Enter character and size:");
			scanf(" %c %d",&character,&size);
			draw_triangle(character, size);
		}	
		else if(option == 3){	

		}
		else if(option!=0 || option !=1 || option!=2 || option != 3){
			printf("Invalid Choice.\n");
		}
		printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
        scanf("%d",&option);
	}
	printf("Bye Bye.");
	return 0;
}
int validCharacter(char character){
	if (character == '#' || character == '*' || character == '%'){
		return 1;
	}
	return 0;
}
int draw_rectangle(char character, int wid, int len){
	int i,j=0;
	if (wid <=0 || len <=0 || validCharacter(character)==0){
		printf("Invalid data provided.\n");
		return 0;
	}
	
	for(i = 0; i < wid; i = i+1){
		for(j = 0; j < len; j = j+1){
			printf("%c", character);
		}
		printf("\n");
	}	
	return 1;		
}
int draw_triangle(char character, int size){
	int i,j, k=0;
	if (size <= 0 || validCharacter(character)==0){
		printf("Invalid data provided.");
		return 0;
	}
    for(i =1; i<=size;i++, k=0){
    	for (j =1;j<=size-i;j++){
        	printf(" ");
    	}
    	for(k = 1;k <= (2*i-1);k++){
     	   	printf("%c",character);
    	}
    	printf("\n");
    }
    return 1;
}
