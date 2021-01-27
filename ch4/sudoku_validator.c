/**
 * Validates a Sudoku puzzle
 * Reads in the puzzle state (see example_valid_sud.txt for formatting)
 * Creates threads to check each row, column, and the nine 3x3 squares for 1-9
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* this data is shared by the threads */
int *puzzle_state[9];
char row_status[9];
char col_status[9];
char square_status[9];

/* thread functions */
void *check_row(void *row_to_check); 
void *check_col(void *col_to_check);
void *check_square(void *square_to_check);

int main(int argc, char *argv[]) {

	pthread_t tids[27]; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for each thread */

	if (argc != 2) {
		fprintf(stderr, "usage: ./sudoku_validator <filepath_to_puzzle_state>");
		exit(1);
	}

	/* read puzzle state */
	FILE *f_puzzle = fopen(argv[1], "r");
	if (f_puzzle == NULL) {
		perror("Could not open puzzle to validate");
		exit(1);
	}
	char *line = (char *) malloc(18 * sizeof(char));
	size_t line_len = 18;
	int read;
	for (int i = 0; i < 9; i++) { /* read line by line */
		if ((read = getline(&line, &line_len, f_puzzle)) == -1) {
			perror("Error reading puzzle");
			exit(1);
		}
		if (read != 18 || line[17] != '\n') { /* getline returns \n */
			fprintf(stderr, "Malformed row in puzzle\n");
			exit(1);
		}
		int *row = (int *) malloc(9 * sizeof(int));
		char *token;
		token = strtok(line, " ");
		if (token == NULL || atoi(token) < 1 || atoi(token) > 9) {
			fprintf(stderr, "Missing or invalid token in puzzle\n");
			exit(1);
		}
		row[0] = atoi(token);
		for (int j = 1; j < 9; j++) { /* process other tokens */
			token = strtok(NULL, " \n");
			if (token == NULL || atoi(token) < 1 || atoi(token) > 9) {
				fprintf(stderr, "Missing or invalid token in puzzle\n");
				exit(1);
			}
			row[j] = atoi(token);
		}		
		puzzle_state[i] = row;
	}

	/* free resources */
	free(line);
	fclose(f_puzzle);

	/* print puzzle_state */
	/*
	for (int i = 0; i < 9; i++) {
		printf("row %d: ", i);
		for (int j = 0; j < 9; j++) {
			printf("%d ", puzzle_state[i][j]);
		}
		printf("\n");
	}
	*/

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* create the threads */
	int tmp;
	for (int thread = 0; thread < 27; thread++) {
		if (thread < 9) { /* check rows */
			pthread_create(&tids[thread], &attr, check_row, (void *) (&thread));
		}
		else if (thread < 18) { /* check columns */
			tmp = thread % 9;
			pthread_create(&tids[thread], &attr, check_col, (void *) (&tmp));
		}
		else { /* check 3x3 squares */
			tmp = thread % 9;
			pthread_create(&tids[thread], &attr, check_square, (void *) (&tmp));
		}
	}

	/* now wait for the threads to exit */
	for (int thread = 0; thread < 27; thread++) {
		pthread_join(tids[thread], NULL);
	}

	/* write result to stdout */
	for (int result = 0; result < 27; result++) {
		if (result < 9 && row_status[result] == 0) { /* check rows */
			printf("Invalid Sudoku. Bad row %d\n", result);
		}
		else if (result < 18 && col_status[result % 9] == 0) { /* check columns */
			printf("Invalid Sudoku. Bad column %d\n", result);	
		}
		else { /* check 3x3 squares */
			printf("Invalid Sudoku. Bad 3x3 square %d\n", result);	
		}
	}
	printf("Valid Sudoku!\n");
	
	/* free heap memory used to store the puzzle state */
	for (int i = 0; i < 9; i++) {
		free(puzzle_state[i]);
	}

	return 0;
}

/**
 * The threads will begin control in these functions
 */
void *check_row(void *row_to_check) {

	int row = *((int *) row_to_check);

	pthread_exit(0);
}
 
void *check_col(void *col_to_check) {

	int col = *((int *) col_to_check);

	pthread_exit(0);
}
 
void *check_square(void *square_to_check) {

	int square = *((int *) square_to_check);

	pthread_exit(0);
}
