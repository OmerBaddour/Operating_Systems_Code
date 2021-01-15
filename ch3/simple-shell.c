/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* 80 chars per line, per command */

int main(void)
{
	char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */

	/* history is circular doubly-linked list */
		
    	while (1) {   
		/* prompt user */
        	printf("osh>");
        	fflush(stdout);
        
		/* read user input */
		char input[MAX_LINE];
		fgets(input, MAX_LINE, stdin); 

		/* process user input 
		 * replace spaces with null terminators, and populate args with
		 * pointers to the beginning of strings in input[] */
		int cur_arg = 0;
		int new_arg = 1;
		int len_input = strlen(input);
		for (int i = 0; i < len_input; i++) { 
			if (isspace(input[i]) == 0) { /* not whitespace */
				if (new_arg == 1) {
					args[cur_arg] = &input[i];
					cur_arg++;
					new_arg = 0;
				}
			}
			else { 
				input[i] = 0;
				new_arg = 1;
			}
		}

		/* zero out remainder of args */
		for (int i = cur_arg; i < MAX_LINE/2 + 1; i++) {
			args[i] = 0;
		}

		/* check special cases:
		 * - were any args enterred?
		 * - is exit enterred?
		 * - is last argument &? */
		int background = 0;
		if (cur_arg == 0) { 
			continue; /* no args enterred */
		}
		else if (cur_arg == 1 && strcmp(args[cur_arg-1], "exit") == 0) {
			break; /* exit */
		}
		else if (strcmp(args[cur_arg-1], "&") == 0) {
			background = 1;
			args[cur_arg-1] = 0; /* trailing & should not be passed to execvp */
		}

		pid_t pid = fork();

		if (pid < 0) {
			fprintf(stderr, "Fork failed");
			exit(1);
		}

		if (pid > 0) { /* parent process */
			if (background == 0) { /* wait */
				int status;
				wait(&status);
			} 
		}
		else { /* child process */
			execvp(args[0], args);
		}

    	}
    
	return 0;
}
