#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define C_OK		 0
#define C_NOK		-1

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one sce+nario of one run
  FighterType  *hero;	
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


int  randm(int);		// Pseudo-random number generator function

#endif
//deque.c
void initDeque(DequeType*);
void copyDeque();
void initCrew(DequeType*);
int  isEmpty(DequeType*);
void cleanupDeque(DequeType*);

//fighter.c
void initFighter(int, int, int, FighterType**);
void addFighter(DequeType*, FighterType*);
void removeFirstFighter(DequeType*, FighterType**);
void removeLastFighter(DequeType*, FighterType**);
int  heroAttack(FighterType*, FighterType*);
int  pirateAttack(FighterType*, FighterType*);

//stats.c
void initStats(StatsType*);
int computeStats(FighterType*, FighterType*);
void updateStats(ResultType, StatsType*);
void printStats(StatsType*, int);

//fight.c
void initFightSpec(FighterType*, DequeType*, DirectionType, sem_t*, FightSpecsType**);
void initRunSpec(DequeType*, FighterType*, FighterType*, StatsType*, RunSpecsType**);
void *simulateFight(void*);
void *spawnScenarioThread(void*);
void initScenario (int, DequeType*, StatsType*);
