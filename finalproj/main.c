#include "defs.h"

int main(int argc, char *argv[])
{
	int times;
	if (argc < 2) {
		times = NUM_RUNS;
	} else {
		sscanf(argv[1], "%d", &times);
	}
	srand( (unsigned)time( NULL ) );
	StatsType t_stats, h_stats, n_stats;
	initStats(&t_stats);
	initStats(&h_stats);
	initStats(&n_stats);
	for (int j=0; j<times; j++) {
		DequeType deque;
		initDeque(&deque);
		initCrew(&deque);
		for (int i=0; i<NUM_SCENARIOS; i++) {	//change
			if (i == 0) {
				DequeType deque1;
				initDeque(&deque1);	
				copyDeque(&deque, &deque1);
				initScenario(i, &deque1, &t_stats);
				if (j == times-1) {
					printStats(&t_stats, i);
				}
			} else if (i == 1) {
				DequeType deque2;
				initDeque(&deque2);	
				copyDeque(&deque, &deque2);
				initScenario(i, &deque2, &h_stats);
				if (j == times-1) {
					printStats(&h_stats, i);
				}
			} else if (i == 2) {
				DequeType deque3;
				initDeque(&deque3);	
				copyDeque(&deque, &deque3);
				initScenario(i, &deque3, &n_stats);
				if (j == times-1) {
					printStats(&n_stats, i);
				}
			}
		}
		cleanupDeque(&deque);
	}
	printf(" RUNS: %d\n", times);
	return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 
  return (int)(r * max);
}

