#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "barrier.h"

#define NUM_THREADS 8

void *test_barrier(); /* thread function to test barrier */

int main(void) {

	pthread_t tids[NUM_THREADS];
	pthread_attr_t attr;

	/* initialize */
	pthread_attr_init(&attr);
	srand(time(NULL));
	init(NUM_THREADS);
	
	/* create threads */
	for (int thread = 0; thread < NUM_THREADS; thread++) {
		pthread_create(&tids[thread], &attr, test_barrier, NULL);
	}

	/* wait for threads to exit */
	for (int thread = 0; thread < NUM_THREADS; thread++) {
		pthread_join(tids[thread], NULL);
	}

	printf("All threads done.\n");

	clean_up();

	return 0;
}

void *test_barrier() {

	/* simulate work by sleeping for a random amount of time */
	int time = rand() % 10;
	sleep(time);

	printf("Done first round after sleeping for %d seconds\n", time);

	/* stop at barrier point */
	barrier_point();

	/* simulate work again */
	time = rand() % 10;
	sleep(time);

	printf("Done second round after sleeping for %d seconds\n", time);

	/* stop at barrier point */
	barrier_point();

	pthread_exit(0);
}

