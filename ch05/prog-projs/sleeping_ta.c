#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define NUM_STUDENTS 5
#define MAX_WORK_TIME 10
#define MAX_HELP_TIME 4
#define MAX_ASSIGNMENT_TIME 30

int students_seated;
pthread_mutex_t seat_mutex;
sem_t student_sem;
sem_t ta_sem;

void *ta_func(); /* TA code */
void *student_func(void *student_id); /* student code */
bool done_assignment(int time_worked, int times_helped, float intelligence); /* student helper, to see if done with assignment */
int max(int x, int y); /* generic helper function */

int main(void){

	/* initialization */
	students_seated = 0;
	pthread_mutex_init(&seat_mutex, NULL);

	sem_init(&student_sem, 0, 0);
	sem_init(&ta_sem, 0, 0);

	srand(time(NULL));

	pthread_t ta_tid;
	pthread_t student_tids[NUM_STUDENTS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	/* create TA thread */
	pthread_create(&ta_tid, &attr, ta_func, NULL);

	/* create student threads */
	int thread_args[NUM_STUDENTS]; /* ints of student IDs */
	for (int i = 0; i < NUM_STUDENTS; i++) {
		thread_args[i] = i;
	}
	for (int thread = 0; thread < NUM_STUDENTS; thread++) {
		pthread_create(&student_tids[thread], &attr, student_func, (void *) (&thread_args[thread]));
	}

	/* wait for all students to complete the assignment */
	for (int thread = 0; thread < NUM_STUDENTS; thread++) {
		pthread_join(student_tids[thread], NULL);
	}

	printf("All students done.\n");

	/* kill TA thread */
	/* by default, threads can be canceled */
	pthread_cancel(ta_tid);

	void *res;
	pthread_join(ta_tid, &res);
	if (res == PTHREAD_CANCELED) {
		printf("TA thread canceled. TA shall hibernate until the next assignment is released.\n");
	}

	printf("All threads done.\n");

	return 0;
}

void *ta_func() {

	while (1) {

		printf("TA sleeping.\n");

		/* wait to be woken up by student thread */
		sem_wait(&ta_sem);

		/* woken up */

		/* remove seated student */
		pthread_mutex_lock(&seat_mutex);
		students_seated -= 1;
		pthread_mutex_unlock(&seat_mutex);

		printf("TA helping student.\n");

		/* help student for random amount of time */
		/* since student is blocked in student_sem, also causes student to wait */
		int time = (rand() % MAX_HELP_TIME) + 1;
		sleep(time);

		printf("TA done helping student after %d seconds.\n", time);

		/* wake up student receiving help */
		sem_post(&student_sem);
	}

	pthread_exit(0);
}

void *student_func(void *tid) {

	int student_id = *((int *) tid);
	int time_worked = 0;
	int times_helped = 0;
	float intelligence = 1 + (float)rand() / RAND_MAX;

	while (1) {

		/* check if finished assignment */
		if (done_assignment(time_worked, times_helped, intelligence)) {
			break;
		}

		printf("%d working.\n", student_id);

		/* work for random amount of time */
		int time = (rand() % MAX_WORK_TIME) + 1;
	  	sleep(time);
		time_worked += time;

		printf("%d done working after %d seconds.\n", student_id, time);

		/* try to get help */		
		pthread_mutex_lock(&seat_mutex);

		if (students_seated < 3) {

			/* wait to get help */
			students_seated += 1;
			pthread_mutex_unlock(&seat_mutex);
		
			printf("%d seated to get help.\n", student_id);

			/* wake up TA */
			sem_post(&ta_sem);
			
			/* wait for TA to finish helping us */
			sem_wait(&student_sem);

			printf("%d done getting help.\n", student_id);
			times_helped += 1;
		}
		else {
			/* no free seats, resume working */
			pthread_mutex_unlock(&seat_mutex);

			printf("%d couldn't get help. All seats full.\n", student_id);
			continue;
		}

	}

	/* student finished assignment */
	printf("%d finished the assignment. %d time_worked, %d times_helped, %.2f intelligence.\n", student_id, time_worked, times_helped, intelligence);

	pthread_exit(0);

}

/* helper student method */
/* probabilistically determine whether a student has completed the assignment */
/* uses max() to set a lower bound of amount of work required */
bool done_assignment(int time_worked, int times_helped, float intelligence) {
	return max(MAX_ASSIGNMENT_TIME / 2, (rand() % MAX_ASSIGNMENT_TIME) + 1) < ((time_worked + 10*times_helped) * intelligence);
}

int max(int x, int y) {
	return (x > y) ? x : y;
}

