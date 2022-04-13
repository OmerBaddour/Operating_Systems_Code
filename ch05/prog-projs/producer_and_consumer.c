#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include "buffer.h"
#include "producer_and_consumer.h"

void *producer(void *param) {
	srand(time(NULL));

	buffer_item item;

	while (true) {	
		/* sleep for random period of time */
		sleep((rand() % MAX_SLEEP_TIME) + 1);

		/* generate random number */
		item = rand();

		if (insert_item(item)) {
			fprintf(stderr, "report error condition\n");
		}
		else {
			printf("producer produced %d\n", item);
		}
	}
}

void *consumer(void *param) {
	srand(time(NULL));

	buffer_item item;
	
	while (true) {	
		/* sleep for random period of time */
		sleep((rand() % MAX_SLEEP_TIME) + 1);

		if (remove_item(&item)) {
			fprintf(stderr, "report error condition\n");
		}
		else {
			printf("consumer consumed %d\n", item);
		}
	}
}

