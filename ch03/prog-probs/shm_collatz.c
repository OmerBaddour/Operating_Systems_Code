/*
 * Collatz conjecture algorithm executed by child process
 * Child process writes sequence to shared memory with parent
 * Parent process reads shared memory and writes contents to stdout
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <math.h>

int main (int argc, char *argv[]) {

	int z;
	pid_t pid;
	int status;
	const int size = 8192;
	const char *name = "collatz";
	int shm_fd;
	void *ptr;

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
		printf("Child process completed with status %d\n", status);
		
		/* read from shared memory */
		shm_fd = shm_open(name, O_RDONLY, 0666);
		ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0);
		printf("%s", (char *)ptr);
		
		shm_unlink(name); /* unlink */
	}
	else { /* child process */
		/* prepare shared memory object*/
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, size);
		ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);

		/* collatz algorithm */
		while (z != 1) {
			/* write to shared memory */
			sprintf(ptr, "%d, ", z);
			ptr += (int)log10((double)z) + 3;

			if (z % 2 == 0) {
				z /= 2;
			}
 			else {
				z = z * 3 + 1;
			}
		}
		sprintf(ptr, "%d.\n", z);
		ptr += (int)log10((double)z) + 3;
	}

	return 0;

}
