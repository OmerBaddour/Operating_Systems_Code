/*
* Use POSIX API to copy the contents of a source file into a destination file
*
* 1) file path max length is dealt with poorly. for simplicity, use arbitrary 1024 bytes, which is likely sufficient
*
*/

#include <stdio.h> // printf, scanf, perror
#include <unistd.h> // access
#include <stdlib.h> // exit

int main(int argc, char *argv[]) {
	
	// prompt user for source file path to copy
	printf("Enter the path of the source file to copy: ");
	char src_path[1024]; // see 1)
	scanf("%s", src_path);

	// check that source file exists and can be read
	if (access(src_path, R_OK) != 0) {
		perror("Error with source file");
		exit(1);
	}

	// prompt user for destination file path to copy to
	printf("Enter the path of the destination file to paste copied contents into: ");
	char dst_path[1024]; // see 1)
	scanf("%s", dst_path);	

	// check that destination file does not exist
	if (access(dst_path, F_OK) == 0) {
		printf("Destination file already exists\n");
		exit(1);
	}	

	// get file descriptors for source and destination files
	FILE *src_fd = fopen(src_path, "rb");
	FILE *dst_fd = fopen(dst_path, "wb"); 
	if (src_fd == NULL || dst_fd == NULL) {
		printf("Could not establish a file pointer\n");
		exit(1);
	}

	// read bytes from source into buffer, and write bytes from buffer into destination
	int c;
	while ((c = fgetc(src_fd)) != EOF) {
		if (fputc(c, dst_fd) != c) {
			perror("Write failed");
			exit(1);
		}
	}

	// exit
	if (fclose(src_fd) != 0 || fclose(dst_fd) != 0) {
		perror("fclose failed");
		exit(1);
	}	

	return 0;
}

