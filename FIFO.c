// Suzana Nesic
// April 14, 2017
// ECGR 3101 Homework 6

#include <stdio.h>
#include <stdlib.h>

struct FIFOstruct {
	char character;
	struct FIFOstruct *next;
}*head, *tail, *temp;

void FIFO();
void add(char ch);
void rem();

int counter=0;

int main(){

	int i,j,k,l,s=0;
	
	printf("*********Test case 1*********\n");
	printf("Inputting 4 characters and outputting 2 characters\n");
	FIFO();
		for(j=0;j<2;j++) {
			add('a');
			counter=counter+4;
			printf("Input: FIFO size : %d\n", counter);
		}

	do {
			rem();
			counter=counter-2;
			printf("Output: FIFO size : %d\n", counter);
			add('a');
			counter=counter+4;
			printf("Input: FIFO size : %d\n", counter);
	}while(counter<=14);

	if(counter>14) {
		printf("Fifo full\n");
	}

	printf("*********Test case 2*********\n");
	printf("Inputting 2 characters and outputting 6 characters\n");
	FIFO();
	counter=0;
	for(s=0;s<4;s++) {
		add('b');
		counter=counter+2;
		printf("Input: FIFO size : %d\n", counter);
	}
	do {
		rem();
		counter=counter-6;
		if(counter<0) {
			counter=0;
			printf("Output: FIFO size : %d\n", counter);
			printf("Fifo empty\n");
			break;	
		}
		printf("Output: FIFO size : %d\n", counter);
		add('a');
		counter=counter+2;
		printf("Input: FIFO size : %d\n", counter);	
	} while (counter >=0); 	
		
	return 0;
}

void FIFO() {
	tail = NULL;
	head = NULL;
	printf("Fifo Empty\n");
}
 
void add(char ch) {
	temp= (struct FIFOstruct *)malloc(sizeof(struct FIFOstruct));
	temp->character = ch;
        temp->next = NULL;

	if (head==NULL) {
		tail = temp;
		head = tail;
	}
	else {
		tail->next=temp;
		tail=temp;
	}
}
 
void rem() {
	if (temp == NULL) {
		printf("Error: empty FIFO\n");
		return;
    	}
	else {
		temp = temp->next;
		free(head);
		head = temp;	
   	}
}
