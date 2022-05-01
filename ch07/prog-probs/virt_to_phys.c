#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

int main (int argc, char* argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: ./virt_to_phys <virtual_address>\n");
		exit(1);
	}

	unsigned int virt_addr = atoi(argv[1]);

	printf("The address %s contains:\n", argv[1]);
	printf("page number = %u\n", virt_addr / PAGE_SIZE);
	printf("offset = %u\n", virt_addr % PAGE_SIZE);

	return 0;
}
