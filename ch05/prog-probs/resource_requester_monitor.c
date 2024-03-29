#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "resource_manager_monitor.h"

#define NUM_THREADS 3
#define NUM_ITERATIONS 3

int main (void) {

	/* init random number generator */
	srand(time(NULL));
	
	printf("Initialize resource manager...\n");
	init_monitor();

	#pragma omp parallel for
	for (int i = 0; i < NUM_THREADS; i++) {

		for (int j = 0; j < NUM_ITERATIONS; j++) {

			/* fetch a random number of resources */
			/* waits if necessary, so call is eventually always successful */
			int resources_to_fetch = (rand() % MAX_RESOURCES) + 1;
			decrease_count(resources_to_fetch);
			printf("Fetched %d resources\n", resources_to_fetch);

			/* sleep for random amount of time */
			int time = rand() % 10;
			sleep(time);

			/* if acquired resources, return resources */
			increase_count(resources_to_fetch);
			printf("Released %d resources after sleeping for %d seconds \n",
				resources_to_fetch, time
			);
		}
	}

	free_monitor();

	return 0;

}
