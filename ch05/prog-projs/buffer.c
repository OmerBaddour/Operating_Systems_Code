#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int in;
int out;

void init_buffer(void) {
	for (int i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = -1;
	}

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUFFER_SIZE); /* producer can write BUFFER_SIZE times */
	sem_init(&full, 0, 0); /* consumer cannot consume */
	in = 0;
	out = 0;
}

int insert_item(buffer_item item) {
	/* insert item into buffer */
	/* return 0 if successful, otherwise */
	/* return -1 indicating an error condition */

	if (sem_wait(&empty) != 0) {
		return -1;
	}
	if (pthread_mutex_lock(&mutex) != 0) {
		return -1;
	}

	buffer[in] = item;
	in = (in + 1) % BUFFER_SIZE;
	
	if (pthread_mutex_unlock(&mutex) != 0) {
		return -1;
	}
	if (sem_post(&full) != 0) {
		return -1;
	}

	return 0;
}

int remove_item(buffer_item *item) {
	/* remove an object from buffer */
	/* placing it in item */
	/* return 0 if successful, otherwise */
	/* return -1 indicating an error condition */

	if (sem_wait(&full) != 0) {
		return -1;
	}
	if (pthread_mutex_lock(&mutex) != 0) {
		return -1;
	}

	*item = buffer[out];
	out = (out + 1) % BUFFER_SIZE;
	
	if (pthread_mutex_unlock(&mutex) != 0) {
		return -1;
	}
	if (sem_post(&empty) != 0) {
		return -1;
	}

	return 0;
}

void clean_buffer(void) {

	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}

