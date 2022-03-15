/**
 * Figure 3.32
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int i;
	pid_t pid;

	for (i = 0; i < 4; i++)
		pid = fork();

	printf("%d\n", pid);	

	return 0;
}
