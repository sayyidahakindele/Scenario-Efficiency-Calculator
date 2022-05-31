#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "defs.h"

/*
  Function:  initRunSpec
   Purpose:  initializes a run
        in:  pirate crew, tortoise, hare, statistics
       out:  run
    return:  nothing
*/
void initRunSpec(DequeType *crew, FighterType *tort, FighterType *hare, StatsType *stats, RunSpecsType**run) {
	RunSpecsType *new = (RunSpecsType*) malloc(sizeof(RunSpecsType));
	(new) ->pirates = crew;
	(new) ->tort = tort;
	(new) ->hare = hare;
	(new) ->stats = stats;
	*run = new;
}

/*
  Function:  initFightSpec
   Purpose:  initializes a fight
        in:  hero, crew of pirates, direction, mutex
       out:  fight
    return:  nothing
*/
void initFightSpec(FighterType *hero, DequeType *pirates, DirectionType dir, sem_t *mutex, FightSpecsType **fight) {
	FightSpecsType *new = (FightSpecsType*) malloc(sizeof(FightSpecsType));
	(new) ->hero = hero;
	(new) ->pirates = pirates;
	(new) ->dir = dir;
	(new) ->dqMutex = mutex;
	*fight = new;
}

/*
  Function:  simulateFight
   Purpose:  simulates a fight
    return:  nothing
*/
void *simulateFight(void *str) {
	FighterType *pirate;
	FightSpecsType *fight = ((FightSpecsType*)str);
	while (isEmpty(fight ->pirates) == C_OK && fight ->hero ->health > 0) {
		sem_wait(fight ->dqMutex);
		if (fight ->dir == FRONT) {
			removeFirstFighter(fight ->pirates, &pirate);
		} else if (fight ->dir == BACK) {
			removeLastFighter(fight ->pirates, &pirate);
		}
		sem_post(fight ->dqMutex);
		while (pirate ->health > 0 || fight ->hero ->health > 0) {
			if (heroAttack(pirate, fight ->hero) == C_OK) {
				break;
			}
			if (pirateAttack(pirate, fight ->hero) == C_NOK) {
				break;
			}
		}
		
		usleep(1000);
	}
	//free(pirate);
	return 0;
}

/*
  Function:  spawnScenarioThread
   Purpose:  spawns a scenario thread
    return:  nothing
*/
void *spawnScenarioThread(void *str) {
	RunSpecsType *run = ((RunSpecsType*)str);
	sem_t mutex;
	sem_init(&mutex, 0, 1);
	pthread_t t, h;
	FightSpecsType *tfight, *hfight;
	initFightSpec(run ->tort, run ->pirates, FRONT, &mutex, &tfight);
	initFightSpec(run ->hare, run ->pirates, BACK, &mutex, &hfight);
	pthread_create(&t, NULL, simulateFight, tfight);
	pthread_create(&h, NULL, simulateFight, hfight);
	pthread_join(t, NULL);
	pthread_join(h, NULL);
	int result = computeStats(run ->hare, run ->tort);
	updateStats(result, run ->stats);
	free(tfight);
	free(hfight); 
	return 0;
}

/*
  Function:  initScenario
   Purpose:  initializes a scenario with appropriate data
        in:  scenario id, crew of pirates, statistics
    return:  nothing
*/
void initScenario(int scenarios, DequeType *deque, StatsType *stats) {
	RunSpecsType *run;
	FighterType *tortoise, *hare;
	switch(scenarios) {
		case 0:;
			pthread_t s1;
			initFighter(TORT_STRENGTH + SWORD_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoise);
			initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare);
			initRunSpec(deque, tortoise, hare, stats, &run);
			pthread_create(&s1, NULL, spawnScenarioThread, run);
			pthread_join(s1, NULL);
			free(run ->tort);
			free(run ->hare);
			free(run);
			break;
		case 1:;
			pthread_t s2;
			initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoise);
			initFighter(HARE_STRENGTH + SWORD_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare);
			initRunSpec(deque, tortoise, hare, stats, &run);
			pthread_create(&s2, NULL, spawnScenarioThread, run);
			pthread_join(s2, NULL);
			free(run ->tort);
			free(run ->hare);
			free(run);
			break;
		case 2:;
			pthread_t s3;
			initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, &tortoise);
			initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, &hare);
			initRunSpec(deque, tortoise, hare, stats, &run);
			pthread_create(&s3, NULL, spawnScenarioThread, run);
			pthread_join(s3, NULL);
			free(run ->tort);
			free(run ->hare);
			free(run);
			break;
	}	
}
