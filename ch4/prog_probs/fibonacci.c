/*
 * Prints the first n Fibonacci numbers to stdout, where n is the only command
 * line argument
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *nums; /* store Fibonacci numbers */
void *find_fibs(void *num_fibs); /* thread function which finds Fibonacci numbers */

int main(int argc, char *argv[]) {
	
	int num_terms;
	pthread_t tid;
	pthread_attr_t attr;

	/* check usage */
	if (argc != 2) {
		fprintf(stderr, "Usage: ./fibonacci <positive_integer>\n");
		exit(1);
	}
	
	if ((num_terms = atoi(argv[1])) < 0) {
		fprintf(stderr, "The command line argument must be a positive integer\n");
		exit(1);
	}
	
	/* create thread for finding Fibonacci numbers */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, find_fibs, (void *) &num_terms); /* create thread */
	pthread_join(tid, NULL); /* wait for created thread to terminate */

	/* print Fibonacci numbers */ 
	for (int i = 0; i < num_terms; i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	return 0;
}

void *find_fibs(void *num_fibs) {

	int num_terms = *((int *) num_fibs);

	/* allocate array storing the first num_terms Fibonacci numbers */
	nums = (int *) malloc(num_terms * sizeof(int));
	if (nums == NULL) {
		perror("Malloc() failed");
		exit(1);
	}
	
	/* find first num_terms Fibonacci numbers */
	int n_1, n_2;
	n_1 = nums[0] = 0;
	n_2 = nums[1] = 1;
	for (int i = 2; i < num_terms; i++) {
		nums[i] = n_1 + n_2;
		n_1 = n_2;
		n_2 = nums[i];
	}

	pthread_exit(0);
}
