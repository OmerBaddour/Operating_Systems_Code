#include <stdio.h>
#include "pid_manager.h"

int main () {
	
	int pid;
	printf("Allocating PIDs...\n");
	allocate_map();

	pid = allocate_pid();
	printf("Got allocated PID %d\n", pid);

	release_pid(pid);
	printf("Released PID\n");
}
