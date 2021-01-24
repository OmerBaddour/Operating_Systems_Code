/*
 * Print all primes up to and including the integer enterred as a command line
 * argument.
 * Uses the Sieve of Eratosthenes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *nums; /* store bitmap representing primality of numbers */
void *find_primes(void *upper_bound); /* thread function which to find primes */

int main(int argc, char *argv[]) {
	
	int max;
	pthread_t tid;
	pthread_attr_t attr;

	/* check usage */
	if (argc != 2) {
		fprintf(stderr, "Usage: ./primes <positive_integer>\n");
		exit(1);
	}
	
	if ((max = atoi(argv[1])) < 0) {
		fprintf(stderr, "The command line argument must be a positive integer\n");
		exit(1);
	}
	
	/* create thread for finding primes */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, find_primes, (void *) &max); /* create thread */
	pthread_join(tid, NULL); /* wait for created thread to terminate */

	/* print primes */ 
	for (int i = 2; i <= max; i++) {
		if (nums[i] == 1) {
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}

void *find_primes(void *upper_bound) {

	int max = *((int *) upper_bound);

	/* allocate bitmap storing primality of numbers [0, max] */
	nums = (char *) malloc((max+1) * sizeof(char));
	if (nums == NULL) {
		perror("Malloc() failed");
		exit(1);
	}
	
	memset(nums, 1, max+1); /* initialize all numbers to prime */

	/* identify non-primes with the Sieve of Eratosthenes */
	int sqrt_max = (int) sqrt(max) + 1;
	for (int div = 2; div < sqrt_max; div++) { /* loop through divisors */
		for (int i = 2; i <= max; i++) { /* loop through all numbers */
			if (i % div == 0 && i != div) {
				nums[i] = 0; /* number is divisible, so not prime */
			}
		}
	}

	pthread_exit(0);
}
