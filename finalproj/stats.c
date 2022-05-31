#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "defs.h"

/*
  Function:  initStats
   Purpose:  initiates each outcome to 0
        in:  statistics
    return:  nothing
*/
void initStats(StatsType *stat) {
	stat ->numSuccess = 0;
	stat ->numPartSuccess = 0;
	stat ->numFailure = 0;
}

/*
  Function:  computeStats
   Purpose:  figures out the outcome of the run
        in:  tort data, hare data
    return:  C_OK, C_NOK
*/
int computeStats(FighterType *tort, FighterType *hare) {
	if (tort ->health == 0 && hare ->health == 0) {
		return FAILURE;
	} else if (tort ->health == 0 || hare ->health == 0) {
		return PART_SUCCESS;
	} else if (tort ->health > 0 && hare ->health > 0) {
		return SUCCESS;
	}
	return RES_UNKNOWN;
}

/*
  Function:  updateStats
   Purpose:  updates the statistics
        in:  result, statistics
    return:  nothing
*/
void updateStats(ResultType result, StatsType *stats) {
	if (result == FAILURE) {
		stats ->numFailure++;
	} else if (result == PART_SUCCESS) {
		stats ->numPartSuccess++;
	} else if (result == SUCCESS) {
		stats ->numSuccess++;
	}
}

/*
  Function:  printStats
   Purpose:  prints final statistics of a scenario
        in:  scenario id, statistics
    return:  nothing
*/
void printStats(StatsType *stats, int scenario) {
	if (scenario == 0) {
		printf(" +-----------------+---------+---------+---------+\n");
		printf(" | HERO WITH SWORD | SUCCESS | PARTIAL | FAILURE |\n");
		printf(" +-----------------+---------+---------+---------+\n");
		printf(" | TORTOISE        | %7d | %7d | %7d |\n", stats ->numSuccess, stats ->numPartSuccess, stats ->numFailure);
	} else if (scenario == 1) {
		printf(" | HARE            | %7d | %7d | %7d |\n", stats ->numSuccess, stats ->numPartSuccess, stats ->numFailure);
	} else if (scenario == 2) {
		printf(" | NONE            | %7d | %7d | %7d |\n", stats ->numSuccess, stats ->numPartSuccess, stats ->numFailure);	
	}
	printf(" +-----------------+---------+---------+---------+\n");
}

