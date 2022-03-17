/*
 * API for obtaining and releasing PIDs
 *
 */

#include "pid_manager.h"
#include <stdio.h>

unsigned short pids[LEN_PIDS];

int allocate_map(void) {

	int i;
	for (i = 0; i < LEN_PIDS; i++) {
		pids[i] = 0;
	}
	
	return 1;
}

int allocate_pid(void) {

	int i;
	for (i = 0; i < LEN_PIDS; i++) {
		if (pids[i] == 0) {
			pids[i] = 1;
			return i + MIN_PID;
		}
	}

	return -1;
}

void release_pid(int pid) {
	if (pid < MIN_PID || pid > MAX_PID) {
		fprintf(stderr, "Invalid PID to release\n");
	}
	else {
		pids[pid - MIN_PID] = 0;
	}
}
