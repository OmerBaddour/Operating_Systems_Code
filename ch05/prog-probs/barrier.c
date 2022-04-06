#include <stdio.h>
#include <pthread.h>
#include "barrier.h"

/* static so only accessible in this file */
static int num_threads_to_wait_for;
static pthread_cond_t cond;
static pthread_mutex_t mutex;

void init(int n) {

	/* initialize everything */
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	num_threads_to_wait_for = n;
}

void barrier_point(void) {

	/* acquire lock */
	pthread_mutex_lock(&mutex);

	num_threads_to_wait_for -= 1;
	if (num_threads_to_wait_for > 0) { /* should be same as while */
		/* wait for other threads */
		pthread_cond_wait(&cond, &mutex);
	}
	else {
		/* unblock all waiting threads */
		pthread_cond_broadcast(&cond);
	}

	/* release lock */
	pthread_mutex_unlock(&mutex);
}

void clean_up(void) {

	/* clean up resources */
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

