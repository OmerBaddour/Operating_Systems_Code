#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include "pid_manager.h"

#define NUM_THREADS 100

int main () {
	
	printf("Allocating PIDs...\n");
	allocate_map();

	# pragma omp parallel for
	for (int i = 0; i < NUM_THREADS; i++) {
		int pid = allocate_pid();
		printf("Got allocated PID %d\n", pid);

		int time = rand() % 10;
		sleep(time);

		release_pid(pid);
		printf("Released PID %d after sleeping for %d seconds \n", pid, time);
	}

}
