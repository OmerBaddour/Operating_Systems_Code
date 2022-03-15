/**
 * Use pipes to reverse the case of input strings
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE   512
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];
	pid_t pid;
	int fd_p2c[2];
	int fd_c2p[2];

	/* create the pipe */
	if (pipe(fd_p2c) == -1 || pipe(fd_c2p) == -1) {
		fprintf(stderr,"Pipe(s) failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused ends of the pipes */
		close(fd_p2c[READ_END]);
		close(fd_c2p[WRITE_END]);

		/* write to the parent to child pipe */
		write(fd_p2c[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* close the write end of the parent to child pipe */
		close(fd_p2c[WRITE_END]);

		/* read from the child to parent pipe */
		read(fd_c2p[READ_END], read_msg, BUFFER_SIZE);
		printf("parent read: %s\n", read_msg);
	}
	else { /* child process */
		/* close the unused ends of the pipes */
		close(fd_p2c[WRITE_END]);
		close(fd_c2p[READ_END]);

		/* read from the parent to child pipe */
		read(fd_p2c[READ_END], read_msg, BUFFER_SIZE);
		printf("child read: %s\n",read_msg);

		/* reverse case of read message */
		for (int i = 0; i < strlen(read_msg); i++) {
			if (islower(read_msg[i])) {
				read_msg[i] = toupper(read_msg[i]);
			}
			else {
				read_msg[i] = tolower(read_msg[i]);
			}
		}

		/* write reversed case message to the child to parent pipe */
		write(fd_c2p[WRITE_END], read_msg, BUFFER_SIZE); 

		/* close the write end of the child to parent pipe */
		close(fd_c2p[READ_END]);
	}

	return 0;
}
