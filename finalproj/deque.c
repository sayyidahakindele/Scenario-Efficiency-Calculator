#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "defs.h"

/*
  Function:  initDeque
   Purpose:  initializes elements of the deque
        in:  deque
    return:  nothing
*/
void initDeque(DequeType *deque) {
	deque ->head = NULL;
	deque ->tail = NULL;
}

/*
  Function:  copyDeque
   Purpose:  deepcopies the data from the original deque into another deque
        in:  original deque, new deque
    return:  nothing
*/
void copyDeque(DequeType *deque, DequeType *newDeque){
	NodeType *currNode = deque ->head;
	FighterType *fighter;
	while (currNode != NULL) {
		initFighter(currNode ->data ->strength, currNode ->data ->armour, currNode ->data ->health, &fighter);
		addFighter(newDeque, fighter);	
		currNode = currNode ->next;
	}
};

/*
  Function:  initCrew
   Purpose:  creates a deque of ten pirates
        in:  deque
    return:  nothing
*/
void initCrew(DequeType *crew) {
	int health, strength, armour;
	FighterType *fighter;
	for (int i=0; i<NUM_PIRATES; i++) {
		health = PIRATE_HEALTH;
		strength = randm(5) + 5;
		armour = randm(4) + 1;
		initFighter(strength, armour, health, &fighter);
		addFighter(crew, fighter);
	}
}

/*
  Function:  isEmpty
   Purpose:  checks if the deque is empty
        in:  fighter
    return:  C_OK, C_NOK
*/
int isEmpty(DequeType *deque) {
	if (deque ->head == NULL) {
		//printf("this is empty\n"); 
		return C_NOK;
	}
	return C_OK;
}

/*
  Function:  cleanupDeque
   Purpose:  cleans up memory of deque
        in:  deque
    return:  nothing
*/
void cleanupDeque(DequeType *deque) {
	 NodeType *currNode = NULL;
	 NodeType *nextNode = NULL;
	 currNode = deque ->head;
	 while (currNode != NULL) {
	 	nextNode = currNode->next;
    		free(currNode ->data);
    		free(currNode);
    		currNode = nextNode;
  	 }
}
