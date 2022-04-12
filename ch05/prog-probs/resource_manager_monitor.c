#include <stdio.h>
#include <pthread.h>
#include "resource_manager_monitor.h"

/* static so only accessible in this file */
static int available_resources;
static pthread_cond_t cond;
static pthread_mutex_t monitor_lock;

/* initialize monitor */
void init_monitor(void) {
	
	available_resources = MAX_RESOURCES;

	/* initialize condition variable */
	pthread_cond_init(&cond, NULL);

	/* initialize monitor lock */
	pthread_mutex_init(&monitor_lock, NULL);
}


/* decrease available_resources by count resources */
void decrease_count(int count) {
	
	/* acquire monitor lock */
	pthread_mutex_lock(&monitor_lock);

	/* critical section */
	while (available_resources < count) {
		/* wait and then test condition when released */
		pthread_cond_wait(&cond, &monitor_lock);
	}

	available_resources -= count;
	printf("Allocated %d resources, %d remain\n", count, available_resources);

	/* release monitor lock */
	pthread_mutex_unlock(&monitor_lock);
}

/* increase available resources by count */
int increase_count(int count) {
	
	/* acquire monitor lock */
	pthread_mutex_lock(&monitor_lock);

	/* critical section */
	available_resources += count;
	printf("Recovered %d resources, %d remain\n", count, available_resources);

	/* release all blocked process */
	pthread_cond_broadcast(&cond);

	/* release monitor lock */
	pthread_mutex_unlock(&monitor_lock);

	return 0;
}

/* clean up monitor resources */
void free_monitor(void) {
	/* destroy condition variable */
	pthread_cond_destroy(&cond);

	/* destroy monitor lock */
	pthread_mutex_destroy(&monitor_lock);
}
