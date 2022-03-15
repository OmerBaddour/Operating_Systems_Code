/*
 * Use POSIX API to copy the contents of a source file into a destination file
 * Use an ordinary pipe to send the file contents to the child (writing) process
 *
 * 1) file path max length is dealt with poorly. for simplicity, use arbitrary 
 * 1024 bytes, which is likely sufficient
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
	
	/* check usage */
	if (argc != 3) {
		fprintf(stderr, "Usage: ./filecopy input.txt copy.txt");
		exit(1);
	}

	/* check that source file exists and can be read */
	char *src_path = argv[1];
	if (access(src_path, R_OK) != 0) {
		perror("Error with source file");
		exit(1);
	}

	/* check that destination file does not exist */
	char *dst_path = argv[2];
	if (access(dst_path, F_OK) == 0) {
		fprintf(stderr, "Destination file already exists\n");
		exit(1);
	}	

	/* get file descriptors for source and destination files */
	FILE *src_fd = fopen(src_path, "r");
	FILE *dst_fd = fopen(dst_path, "w"); 
	if (src_fd == NULL || dst_fd == NULL) {
		fprintf(stderr, "Could not establish a file pointer\n");
		exit(1);
	}

	/* create ordinary pipe */
	int fd[2];
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
		exit(1);
	}

	char *buf;
	long num_bytes;

	/* get number of bytes in source file */ 
	fseek(src_fd, 0L, SEEK_END);
	num_bytes = ftell(src_fd);

	/* reset the file position indicator to the beginning of the
	 * file */
	fseek(src_fd, 0L, SEEK_SET);

	/* obtain sufficiently sized buffer for file */
	buf = (char *)calloc(num_bytes, sizeof(char));

	/* fork */
	pid_t pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		exit(1);
	}

	if (pid > 0) { /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]); 

		/* read source file contents into buf */
		if (fread(buf, sizeof(char), num_bytes, src_fd) < num_bytes) {
			perror("Error reading file contents into buf");
			exit(1);
		}

		/* write buf contents to pipe */
		if (write(fd[WRITE_END], buf, num_bytes) == -1) {
			perror("Error writing to pipe");
			exit(1);
		}

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

		/* read pipe contents into buf */ 
		if (read(fd[READ_END], buf, num_bytes) == -1) {
			perror("Error reading from pipe");
			exit(1);
		} 

		/* write buf contents to destination file */
		if (fwrite(buf, sizeof(char), num_bytes, dst_fd) < num_bytes) {
			perror("Error writing to destination file");
			exit(1);
		}

		/* close the read end of the pipe */
		close(fd[READ_END]);
	}

	/* exit */
	if (fclose(src_fd) != 0 || fclose(dst_fd) != 0) {
		perror("fclose failed");
		exit(1);
	}	

	return 0;
}

