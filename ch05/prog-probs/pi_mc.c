/*
 * Calculate pi using the Monte Carlo method.
 * Uses NUM_POINTS points.
 * Uses NUM_THREADS threads and is safe to race conditions.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_POINTS 1000000
#define NUM_THREADS 8

int in_circle; /* store count of number of points in unit circle */
int cur_num_points; /* store count of current total number of points */
pthread_mutex_t mutex; /* mutex to serialize access to in_circle, cur_num_points */

void *monte_carlo (); /* thread function which executes Monte Carlo */

int main (void) {

	pthread_t tids[NUM_THREADS];
	pthread_attr_t attr;

	/* initialize everything */
	in_circle = 0;
	cur_num_points = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_attr_init(&attr);
	srand(time(NULL)); /* initialize seed */

	/* create threads */
	for (int thread = 0; thread < NUM_THREADS; thread++) {
		pthread_create(&tids[thread], &attr, monte_carlo, NULL);
	}

	/* wait for threads to exit */
	for (int thread = 0; thread < NUM_THREADS; thread++) {
		pthread_join(tids[thread], NULL);
	}

	printf("Calculated value of pi: %f\n", 4.0 * in_circle / NUM_POINTS);

	/* free mutex */
	pthread_mutex_destroy(&mutex);

	return 0;
}

void *monte_carlo () {

	while (1) {

		/* acquire mutex */
		pthread_mutex_lock(&mutex);

		if (cur_num_points < NUM_POINTS) {

			/* generate an (x, y) point and check if it is in the circle */
			double x = (rand() / (RAND_MAX / 2.0)) - 1;
			double y = (rand() / (RAND_MAX / 2.0)) - 1;
			
			if (sqrt(x * x + y * y) <= 1) {
				/* point is in the circle since its distance from (0, 0)
				 * is <= 1, and 1 is the radius of the unit circle */
				in_circle++;
			}
			
			cur_num_points++;

			/* release mutex */
			pthread_mutex_unlock(&mutex);
		}
		else {
			/* release mutex */
			pthread_mutex_unlock(&mutex);

			break;
		}

	}

	pthread_exit(0);
}
