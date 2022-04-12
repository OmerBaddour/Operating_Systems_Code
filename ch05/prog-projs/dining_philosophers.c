#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_FORKS 5
#define NUM_PHILOSOPHERS NUM_FORKS

bool fork_taken[NUM_FORKS];
pthread_cond_t fork_conds[NUM_FORKS];
pthread_mutex_t fork_mutexes[NUM_FORKS];


void *philosopher_func(void *philosopher_number);

void pickup_forks(int philosopher_number);
void pickup_left_fork(int philosopher_number);
void pickup_right_fork(int philosopher_number);

void return_forks(int philosopher_number);
void return_left_fork(int philosopher_number);
void return_right_fork(int philosopher_number);

int activity_length(void);


int main (void) {

	/* initialization */
	srand(time(NULL));
	for (int i = 0; i < NUM_FORKS; i++) {
		fork_taken[i] = false;
		pthread_cond_init(&fork_conds[i], NULL);
		pthread_mutex_init(&fork_mutexes[i], NULL);
	}
	pthread_t philosopher_tids[NUM_PHILOSOPHERS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* create philosopher threads */
	int thread_args[NUM_PHILOSOPHERS];
	for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
		thread_args[i] = i;
	}
	for (int thread = 0; thread < NUM_PHILOSOPHERS; thread++) {
		pthread_create(&philosopher_tids[thread], &attr, philosopher_func, (void *) (&thread_args[thread]));
	}
	
	/* wait for philosopher threads to terminate */
	for (int thread = 0; thread < NUM_PHILOSOPHERS; thread++) {
		pthread_join(philosopher_tids[thread], NULL);
	}

	/* clean up resources */
	for (int i = 0; i < NUM_FORKS; i++) {
		pthread_cond_destroy(&fork_conds[i]);
		pthread_mutex_destroy(&fork_mutexes[i]);
	}

}

void *philosopher_func(void *philosopher_number) {

	int id = *((int *) philosopher_number);
	printf("%d\n", id);

	while (true) {
	
		/* think */
		int think_time = activity_length();
		sleep(think_time);

		printf("%d thought for %d seconds.\n", id, think_time);

		/* pickup forks */
		pickup_forks(id);

		/* eat */
		int eat_time = activity_length();
		sleep(eat_time);

		printf("%d ate for %d seconds.\n", id, eat_time);

		/* return forks */
		return_forks(id);
	}

	pthread_exit(0);
}

void pickup_forks(int philosopher_number) {

	/* pickup forks in a starvation-free way */

	if (philosopher_number % 2 == 1) {
		/* philosophers with an odd numbered id start with left fork */
		pickup_left_fork(philosopher_number);
		printf("%d picked up left fork %d.\n", philosopher_number, philosopher_number);
		pickup_right_fork(philosopher_number);
		printf("%d picked up right fork %d.\n", philosopher_number, (philosopher_number+1) % NUM_FORKS);
	}
	else {
		/* philosophers with an even numbered id start with right fork */
		pickup_right_fork(philosopher_number);
		printf("%d picked up right fork %d.\n", philosopher_number, (philosopher_number+1) % NUM_FORKS);
		pickup_left_fork(philosopher_number);
		printf("%d picked up left fork %d.\n", philosopher_number, philosopher_number);
	}

}

void pickup_left_fork(int philosopher_number) {

	pthread_mutex_lock(&fork_mutexes[philosopher_number]);
	while (fork_taken[philosopher_number] == true) {
		pthread_cond_wait(&fork_conds[philosopher_number], &fork_mutexes[philosopher_number]);
	}
	fork_taken[philosopher_number] = true;
	pthread_mutex_unlock(&fork_mutexes[philosopher_number]);
}


void pickup_right_fork(int philosopher_number) {
	pthread_mutex_lock(&fork_mutexes[(philosopher_number+1) % NUM_FORKS]);
	while (fork_taken[(philosopher_number+1) % NUM_FORKS] == true) {
		pthread_cond_wait(&fork_conds[(philosopher_number+1) % NUM_FORKS], &fork_mutexes[(philosopher_number+1) % NUM_FORKS]);
	}
	fork_taken[(1+philosopher_number) % NUM_FORKS] = true;
	pthread_mutex_unlock(&fork_mutexes[(philosopher_number+1) % NUM_FORKS]);
}


void return_forks(int philosopher_number) {

	/* return forks in a starvation-free way */

	if (philosopher_number % 2 == 1) {
		/* philosophers with an odd numbered id start with right fork */
		return_right_fork(philosopher_number);
		printf("%d returned right fork %d.\n", philosopher_number, (philosopher_number+1) % NUM_FORKS);
		return_left_fork(philosopher_number);
		printf("%d returned left fork %d.\n", philosopher_number, philosopher_number);

	}
	else {
		/* philosophers with an even numbered id start with left fork */
		return_left_fork(philosopher_number);
		printf("%d returned left fork %d.\n", philosopher_number, philosopher_number);
		return_right_fork(philosopher_number);
		printf("%d returned right fork %d.\n", philosopher_number, (philosopher_number+1) % NUM_FORKS);
	}
}

void return_left_fork(int philosopher_number) {

	pthread_mutex_lock(&fork_mutexes[philosopher_number]);
	fork_taken[philosopher_number] = false;
	pthread_cond_signal(&fork_conds[philosopher_number]);
	pthread_mutex_unlock(&fork_mutexes[philosopher_number]);
}


void return_right_fork(int philosopher_number) {
	pthread_mutex_lock(&fork_mutexes[(philosopher_number+1) % NUM_FORKS]);
	fork_taken[(1+philosopher_number) % NUM_FORKS] = false;
	pthread_cond_signal(&fork_conds[(philosopher_number+1) % NUM_FORKS]);
	pthread_mutex_unlock(&fork_mutexes[(philosopher_number+1) % NUM_FORKS]);
}

int activity_length(void) {
	/* returns random numbers in the range [1, 3] */
	return (rand() % 2) + 1;
}
