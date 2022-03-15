/*
 * Makes zombie process that exists for at least 10 seconds
 *
 */
#include <stdio.h>
#include <unistd.h>

int main (void) {

	pid_t pid;
	
	pid = fork();
	
	if (pid < 0) {
		fprintf(stdout, "Fork failed\n");
		return 1;
	}

	if (pid > 0) { /* parent process */
		sleep(10);
	}

	return 0;	

}
