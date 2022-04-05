#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "resource_manager.h"

#define NUM_THREADS 3
#define NUM_ITERATIONS 3

int main (void) {

	/* init random number generator */
	srand(time(NULL));
	
	printf("Initialize resource manager...\n");
	init_sem();

	#pragma omp parallel for
	for (int i = 0; i < NUM_THREADS; i++) {

		for (int j = 0; j < NUM_ITERATIONS; j++) {

			/* try to fetch a random number of resources */
			int resources_to_fetch = (rand() % MAX_RESOURCES) + 1;
			int success = decrease_count(resources_to_fetch);
			if (success == 0) {
				printf("Fetched %d resources\n", resources_to_fetch);
			}
			else {
				printf("Failed to fetch %d resources\n", resources_to_fetch);
			}

			/* sleep for random amount of time */
			int time = rand() % 10;
			sleep(time);

			/* if acquired resources, return resources */
			if (success == 0) {
				increase_count(resources_to_fetch);
				printf("Released %d resources after sleeping for %d seconds \n",
					resources_to_fetch, time
				);
			}
		}
	}

	free_sem();

	return 0;

}
