#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"
#include "producer_and_consumer.h"

int main(int argc, char *argv[]) {

	/* 1. Get command line arguments argv[1], argv[2], argv[3] */
	if (argc != 4) {
		fprintf(stderr, "usage: ./producer_consumer_main <total_runtime> <num_producer_threads> <num_consumer_threads>\n");
		exit(1);
	}
	int total_runtime = atoi(argv[1]);
	int num_producer_threads = atoi(argv[2]);
	int num_consumer_threads = atoi(argv[3]);

	/* 2. Initialize buffer */
	init_buffer();

	/* 3. Create producer thread(s) */
	pthread_t prod_tids[num_producer_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for (int thread = 0; thread < num_producer_threads; thread++) {
		pthread_create(&prod_tids[thread], &attr, producer, NULL);
	}

	/* 4. Create consumer thread(s) */
	pthread_t cons_tids[num_consumer_threads];
	for (int thread = 0; thread < num_consumer_threads; thread++) {
		pthread_create(&cons_tids[thread], &attr, consumer, NULL);
	}

	/* 5. Sleep */
	sleep(total_runtime);

	/* 6. Exit */
	printf("exiting\n");
	for (int thread = 0; thread < num_producer_threads; thread++) {
		pthread_cancel(prod_tids[thread]);
	}
	for (int thread = 0; thread < num_consumer_threads; thread++) {
		pthread_cancel(cons_tids[thread]);
	}
	clean_buffer();

	return 0;
}
