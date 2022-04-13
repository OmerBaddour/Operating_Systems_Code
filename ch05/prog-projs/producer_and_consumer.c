#include <stdio.h>
#include <stdlib.h> /* required for rand() */
#include <stdbool.h>
#include "buffer.h"

void *producer(void *param) {
	buffer_item item;
	
	while (true) {	
		/* sleep for random period of time */
		sleep(1);

		/* generate random number */
		item = rand();

		if (insert_item(item)) {
			fprintf(stderr, "report error condition");
		}
		else {
			printf("producer produced %d\n", item);
		}
	}
}

void *consumer(void *param) {
	buffer_item item;
	
	while (true) {	
		/* sleep for random period of time */
		sleep(1);

		if (remove_item(&item)) {
			fprintf(stderr, "report error condition");
		}
		else {
			printf("consumer consumed %d\n", item);
		}
	}
}

