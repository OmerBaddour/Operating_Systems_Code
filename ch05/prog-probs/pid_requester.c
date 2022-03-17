#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "pid_manager.h"

#define NUM_THREADS 3
#define NUM_PROCESSES_PER_THREAD 3

/* shared mutex by threads */
pthread_mutex_t mutex;

/* thread function */
void *request_pids(void *);

int main (void) {

	/* init random number generator */
	srand(time(NULL));
	
	printf("Allocating PIDs...\n");
	allocate_map();

	pthread_mutex_init(&mutex, NULL); /* initialize mutex */

	pthread_t tids[NUM_THREADS]; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for each thread */
	pthread_attr_init(&attr); /* initialize thread attributes object */

	/* create threads */
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_create(&tids[i], &attr, request_pids, NULL);
	}

	/* wait for all threads to terminate */
	for (int i = 0; i < NUM_THREADS; i++){
		pthread_join(tids[i], NULL);
	}

	printf("Terminating...\n");

	return 0;

}

/* using gcc's __attribute__((unused)) to signify that the parameter is unused 
 * unfortunately need a parameter to match the definition of pthread_create()'s
 * last parameter
*/
void *request_pids(__attribute__((unused)) void *arg){

	int pid;
	int time;

	for (int i = 0; i < NUM_PROCESSES_PER_THREAD; i++){
		/* acquire lock to acquire PID */
		pthread_mutex_lock(&mutex);

		/* critical section */
		pid = allocate_pid();

		/* release lock */
		pthread_mutex_unlock(&mutex);

		printf("Got allocated PID %d\n", pid);

		time = rand() % 10;
		sleep(time);

		release_pid(pid);
		printf("Released PID %d after sleeping for %d seconds \n", pid, time);
	}

	pthread_exit(0);
} 

