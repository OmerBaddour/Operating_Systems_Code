/**
 * Simple shell interface program.
 *
 * Logs the history of all commands using a circular doubly linked list.
 * (see list.c and list.h for details and rights)
 *
 * To re-execute the previous command, type !!
 * To re-execute the nth previous command, type !n
 * To exit cleanly, type exit
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
#include "list.h" /* circular doubly linked list implementation */

#define MAX_LINE 80 /* 80 chars per line, per command */
#define LEN_HIST 10 /* 10 commands printed with history command */

int main(void)
{
	char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */

	/* history is circular doubly linked list */
	struct list *history = list_new(NULL, &free);
	int len_hist = 0;
		
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

		/* check special cases:
		 * - were any args enterred?
		 * - is exit enterred?
		 * - is history enterred?
		 * - is !! enterred?
		 * - is !z enterred? (where z is a positive integer)
		 * - is last argument &? */
		int background = 0;
		if (cur_arg == 0) { 
			continue; /* no args enterred */
		}
		else if (cur_arg == 1 && strcmp(args[0], "exit") == 0) {
			break; /* exit */
		}
		else if (cur_arg == 1 && strcmp(args[0], "history") == 0) {
			/* iterate over last LEN_HIST nodes in history and write to stdout */
			int i = 0;
			struct list_node *n = list_tail(history);
			while (!list_end(n) && i < LEN_HIST) {
				printf("%d ", len_hist-i);
				char **data = (char **)n->data;
				for (int i = 0; i < MAX_LINE/2 + 1; i++) {
					if (data[i] != 0) {
						printf("%s ", data[i]);
					}
				}
				printf("\n");
				n = n->prev;
				i++;
			}

			continue; /* don't write history command to history log */
		}
		else if (cur_arg == 1 && strcmp(args[0], "!!") == 0) {
			struct list_node *n = list_tail(history);
			if (list_end(n)) {
				fprintf(stderr, "No commands in history\n");
				continue;
			}
			else {
				/* recover args and cur_args from previous command 
				 * so rest of program executes previous command */
				char **data = (char **)n->data;
				cur_arg = 0;
				for (int i = 0; i < MAX_LINE/2 + 1; i++) {
					if (data[i] != 0) {
						args[i] = data[i];
						cur_arg++;
					}
				}
			}
		}
		else if (cur_arg == 1 && strlen(args[0]) == 2 &&
			 args[0][0] == '!' && isdigit(args[0][1]) != 0) {
			
			int z = (int)args[0][1] - '0'; /* (int) returns char set value */
			if (z > len_hist) {
				fprintf(stderr, "No such command in history\n");
				continue;
			}

			struct list_node *n = list_tail(history);
			while (!list_end(n) && z != 1) {
				n = n->prev;
				z--;
			}
			/* recover args and cur_args from previous command 
			 * so rest of program executes previous command */
			char **data = (char **)n->data;
			cur_arg = 0;
			for (int i = 0; i < MAX_LINE/2 + 1; i++) {
				if (data[i] != 0) {
					args[i] = data[i];
					cur_arg++;
				}
			}
		}
		else if (strcmp(args[cur_arg-1], "&") == 0) {
			background = 1;
			args[cur_arg-1] = 0; /* trailing & should not be passed to execvp */
		}

		/* zero out remainder of args */
		for (int i = cur_arg; i < MAX_LINE/2 + 1; i++) {
			args[i] = 0;
		}

		/* make deep copy of args */
		/* need to calloc because stack variable in loop reuses same memory address */
		char **data = (char **)calloc(MAX_LINE/2 + 1, sizeof(char *));
		if (data == 0) {
			fprintf(stderr, "Calloc failed");
			exit(1);
		} 
		for (int i = 0; i < cur_arg; i++) {
			data[i] = strdup(args[i]);
		}

		/* add deep copy to history */
		list_push_back(history, list_node_new(data));
		len_hist++;

		/* fork and have child process execute command */
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
	
	/* free history */
	struct list_node *n = list_head(history);
	while (!list_end(n)) { 
		char **data = (char **)n->data;
		for (int i = 0; i < MAX_LINE/2 + 1; i++) {
			if (data[i] != 0) {
				free(data[i]);
			}
		}
		n = n->next;
	}
	list_free(history); 

	return 0;
}
