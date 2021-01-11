/*
 * Collatz conjecture algorithm executed by child process
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {

	int z;
	pid_t pid;
	int status;

	/* error checking */
	if (argc != 2) {
		fprintf(stderr, "Usage: ./collatz <positive_integer>\n");
		return 1;
	}

	z = atoi(argv[1]);
	if (z < 1) {
		fprintf(stderr, "First argument must be a positive integer\n");
		return 1;
	}

	/* fork */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		return 1;
	}
	if (pid > 0) { /* parent process */
		wait(&status);
		printf("Child process completed with status %d; algorithm " 
		       "terminated\n", status);
	}
	else { /* child process */
		while (z != 1) {
			if (z % 2 == 0) {
				printf("%d, ", z);
				z /= 2;
			}
 			else {
				printf("%d, ", z);
				z = z * 3 + 1;
			}
		}
		printf("%d.\n", z);
	}

	return 0;

}
