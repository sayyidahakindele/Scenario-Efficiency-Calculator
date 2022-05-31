#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "defs.h"

/*
  Function:  initFighter
   Purpose:  initializes fighter information
        in:  strength, armour, health
       out:  fighter
    return:  nothing
*/
void initFighter(int s, int a, int h, FighterType **fighter) {
	FighterType *new = (FighterType*) malloc(sizeof(FighterType));
	(new) ->strength = s;
	(new) ->armour = a;
	(new) ->health = h;
	*fighter = new;
}

/*
  Function:  addFighter
   Purpose:  adding fighter to deque
        in:  deque, fighter
    return:  nothing
*/
void addFighter(DequeType *deque, FighterType *f) {
	NodeType *currNode = deque ->head;
	NodeType *newNode = malloc(sizeof(NodeType));
    	newNode ->data = f;
    	newNode ->next = NULL;
    	if (currNode == NULL) {
        	deque ->head = newNode;
        	deque ->tail = newNode;
    	} else {
		while (currNode->next != NULL) {
			currNode = currNode->next;
		}
		currNode ->next = newNode;
    	}
}

/*
  Function:  removeFirstFighter
   Purpose:  removing first fighter from the deque
        in:  deque
       out:  fighter
    return:  nothing
*/
void removeFirstFighter(DequeType *deque, FighterType **f) {
	NodeType *currNode = deque ->head;
	NodeType *toRemove;
	if (currNode == NULL) {
		return;
	}
	toRemove = currNode;
	*f = toRemove ->data;
	deque ->head = deque ->head ->next;
	free(toRemove);
}

/*
  Function:  removeLastFighter
   Purpose:  removing last fighter from the deque
        in:  deque
       out:  fighter
    return:  nothing
*/
void removeLastFighter(DequeType *deque, FighterType **f) {
	NodeType *currNode = deque ->head;
	NodeType *temp;
	NodeType *toRemove;
	NodeType *first;
	if (currNode != NULL) {
	    	if (currNode ->next == NULL) {
	    		first = currNode;
	    		*f = first ->data;
	      		deque ->head = NULL;
	      		free(first);
	      		return;
	    	} else {
		      	temp = currNode;
		      	while (temp ->next ->next !=NULL) {
				temp = temp ->next; 
			}   
		      	toRemove = temp ->next;
		      	*f = toRemove ->data;
		      	temp ->next = NULL;
		      	free(toRemove);
	    	}
    	}
}

/*
  Function:  heroAttack
   Purpose:  simulates the hero hitting the pirate once
        in:  hero, pirate
    return:  C_OK, C_NOK
*/
int heroAttack(FighterType *pirate, FighterType *hero) {
	int damage = hero ->strength - pirate ->armour;
	if (damage < 0) {
		damage = 0;
	}
	pirate ->health = pirate ->health - damage;
	if (pirate ->health < 1) {
		if (hero ->health < 18) {
			hero ->health = hero ->health + 3;	
		}
		pirate ->health = 0;
		return C_OK;
	}
	return C_NOK;
}

/*
  Function:  pirateAttack
   Purpose:  simulates the pirate hitting the hero once
        in:  hero, pirate
    return:  C_OK, C_NOK
*/
int pirateAttack(FighterType *pirate, FighterType *hero) {
	int random = randm(pirate ->strength - 1);
	int temp = pirate ->strength + random;
	int damage = temp - hero ->armour;
	if (damage < 0) {
		damage = 0;
	}
	hero ->health = hero ->health - damage;
	if (hero ->health < 1) {
		hero ->health = 0;
		return C_NOK;
	}
	return C_OK;
}
