/**
 * Prints average, max and min of command line arguments using different pthreads
 * Command line arguments should be positive integers
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* this data is shared by the thread(s) */
int num_vals; /* argc - 1 */
float avg;
int max;
int min; 

/* thread functions */
void *avg_f(void *int_args); 
void *max_f(void *int_args);
void *min_f(void *int_args);

int main(int argc, char *argv[]) {

	pthread_t tid_1, tid_2, tid_3; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for the thread */

	num_vals = argc - 1;
	int int_args[num_vals]; /* store int format of the command line arguments */

	if (argc < 2) {
		fprintf(stderr, "usage: stats <positive_integer> ... <positive_integer>\n");
		exit(1);
	}

	/* convert all command line arguments to ints */
	for (int i = 1; i < argc; i++) {
		int int_arg = atoi(argv[i]);
		if (int_arg < 0) {
			fprintf(stderr, "Argument %d must be non-negative\n", int_arg);
			exit(1);
		}
		else {
			int_args[i-1] = int_arg;
		}
	}

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the threads */
	pthread_create(&tid_1, &attr, avg_f, (void *) int_args);
	pthread_create(&tid_2, &attr, max_f, (void *) int_args);
	pthread_create(&tid_3, &attr, min_f, (void *) int_args);

	/* now wait for the threads to exit */
	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	pthread_join(tid_3, NULL);

	/* write results to stdout */
	printf("avg = %f\n", avg);
	printf("max = %d\n", max);
	printf("min = %d\n", min);
}

/**
 * The threads will begin control in these functions
 */
void *avg_f(void *int_args) {

	int *vals = (int *) int_args;
	float sum = 0;

	for (int i = 0; i < num_vals; i++) {
		sum += vals[i];
	}

	avg = sum / num_vals;

	pthread_exit(0);
}

void *max_f(void *int_args) {

	int *vals = (int *) int_args;
	max = vals[0];

	for (int i = 1; i < num_vals; i++) {
		if (vals[i] > max) {
			max = vals[i];
		}
	}

	pthread_exit(0);
}


void *min_f(void *int_args) {

	int *vals = (int *) int_args;
	min = vals[0];

	for (int i = 1; i < num_vals; i++) {
		if (vals[i] < min) {
			min = vals[i];
		}
	}

	pthread_exit(0);
}
