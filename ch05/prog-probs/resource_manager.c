#include <stdio.h>
#include <semaphore.h>
#include "resource_manager.h"

int available_resources = MAX_RESOURCES;
sem_t sem;

void init_sem(void) {
	/* create semaphore and initialize to 1 */
	/* only one thread can modify available_resources at a time */
	/* makes more sense to just use a mutex, but using a semaphore for practice */
	sem_init(&sem, 0, 1);
}


/* decrease available_resources by count resources
 * return 0 if sufficient resources available,
 * otherwise return -1 
*/
int decrease_count(int count) {
	
	/* acquire semaphore */
	sem_wait(&sem);		

	int ret;

	/* critical section */
	if (available_resources < count) {
		printf("Unable to allocate %d resources, %d remain\n", count, available_resources);
		ret = -1;
	}
	else {
		available_resources -= count;
		printf("Allocated %d resources, %d remain\n", count, available_resources);
		ret = 0;
	}

	/* release semaphore */
	sem_post(&sem);

	return ret;
}

/* increase available resources by count */
int increase_count(int count) {
	
	/* acquire semaphore */
	sem_wait(&sem);

	/* critical section */
	available_resources += count;
	printf("Recovered %d resources, %d remain\n", count, available_resources);

	/* release semaphore */
	sem_post(&sem);

	return 0;
}

void free_sem(void) {
	/* destroy semaphore */
	sem_destroy(&sem);
}
