#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_STUDENTS 5
#define MAX_WORK_TIME 10
#define MAX_HELP_TIME 5

/* TODO: add students_finished, to allow TA to terminate */
int students_seated;
pthread_mutex_t seat_mutex;
sem_t student_sem;
sem_t ta_sem;

void *student_func(void *student_id);
void *ta_func();

int main(void){

	/* initialization */
	students_seated = 0;
	pthread_mutex_init(&seat_mutex, NULL);
	sem_init(&student_sem, 0, 0); /* initialize to 1, allowing immediate student activity */
	sem_init(&ta_sem, 0, 0); /* initialize to 0: sleeping */
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

	/* wait for student threads */
	for (int thread = 0; thread < NUM_STUDENTS; thread++) {
		pthread_join(student_tids[thread], NULL);
	}

	/* wait for TA thread */
	pthread_join(ta_tid, NULL);

	return 0;
}

void *ta_func() {

	while (1) {

		printf("TA sleeping\n");

		/* start asleep */
		sem_wait(&ta_sem);

		/* woken up */
		/* acquire seat mutex */
		pthread_mutex_lock(&seat_mutex);

		/* remove helped student from seat */
		students_seated -= 1;

		/* release seat mutex */
		pthread_mutex_unlock(&seat_mutex);

		printf("TA helping student\n");

		/* help student for random amount of time */
		/* since student is blocked in student_sem, also causes student to wait */
		int time = (rand() % MAX_HELP_TIME) + 1;
		sleep(time);

		printf("TA done helping student after %d seconds\n", time);

		/* signal to student that they are done receiving help */
		sem_post(&student_sem);
	}

	pthread_exit(0);
}

void *student_func(void *tid) {
	int student_id = *((int *) tid);

	for (int i = 0; i < 3; i++) { /* every student is done after 3 rounds of help */

		printf("%d working\n", student_id);

		/* work for random amount of time */
		int time = (rand() % MAX_WORK_TIME) + 1;
	  	sleep(time);

		printf("%d done working after %d seconds\n", student_id, time);

		/* try to get help */		
		pthread_mutex_lock(&seat_mutex);

		if (students_seated < 3) {
			/* wait to get help */
			students_seated += 1;

			/* unlock seat mutex */
			pthread_mutex_unlock(&seat_mutex);
		
			printf("%d seated to get help\n", student_id);

			/* alert TA */
			sem_post(&ta_sem);
			
			/* wait */
			sem_wait(&student_sem);

			printf("%d done getting help\n", student_id);
		}
		else {
			/* no free seats, resume working */
			pthread_mutex_unlock(&seat_mutex);
			printf("%d couldn't get help. seats full\n", student_id);
			continue;
		}

	}

	pthread_exit(0);

}

