/*
 * API for obtaining and releasing PIDs
 *
 */

#include "pid_manager.h"
#include <stdio.h>
#include <pthread.h>

unsigned short pids[LEN_PIDS];
pthread_mutex_t mutex;

int allocate_map(void) {

	/* initialize mutex */
	pthread_mutex_init(&mutex, NULL);

	int i;
	for (i = 0; i < LEN_PIDS; i++) {
		pids[i] = 0;
	}
	
	return 1;
}

int allocate_pid(void) {

	/* acquired lock */
	pthread_mutex_lock(&mutex);

	int ret = -1;

	/* critical section */
	for (int i = 0; i < LEN_PIDS; i++) {
		if (pids[i] == 0) {
			pids[i] = 1;
			ret = i + MIN_PID;
			break;
		}
	}

	/* release lock */
	pthread_mutex_unlock(&mutex);

	return ret;
}

void release_pid(int pid) {
	if (pid < MIN_PID || pid > MAX_PID) {
		fprintf(stderr, "Invalid PID to release\n");
	}
	else {
		/* acquired lock */
		pthread_mutex_lock(&mutex);

		/* critical section */
		pids[pid - MIN_PID] = 0;

		/* release lock */
		pthread_mutex_unlock(&mutex);
	}
}
