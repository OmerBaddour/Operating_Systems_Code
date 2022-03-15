sudoku_validator.c

A multithreaded Sudoku validator program.

$ make sudoku_validator
$ ./sudoku_validator <filepath_to_puzzle_state>

Where <filepath_to_puzzle_state> is a filepath to a file whose contents match
the format of example_valid_sud.txt. The validator program actually just reads
the first 9 lines of the supplied file, and builds int *puzzle_state[9] using
the first 9 space-delimited characters in each line.

Each character must be convertible to an int using atoi(), and must lie in the
bounds [1-9]. Furthermore, the 17th character is checked for equality with \n.
This results in a pretty strict specification for input files.

I do not check that the file only contains 9 lines. Thus files with a correct
format for the first 9 lines, and arbitrary contents for the remainder of the
file, result in successful execution of sudoku_validator. This is fine since
the remaining contents are ignored.

I create threads to check that each row, column and 3x3 square contain the set
of integers from 1 to 9 inclusive. I used bitmaps to do this.

My order of checking rows, columns and 3x3 squares is top to bottom, and left
to right. Thus for the 3x3 squares, I traverse them in the following order:

				-------------
				|   |   |   |
				| 0 | 1 | 2 |
				|   |   |   |
				-------------
				|   |   |   |
				| 3 | 4 | 5 |
				|   |   |   |
				-------------
				|   |   |   |
				| 6 | 7 | 8 |
				|   |   |   |
				-------------

Note that this is also the ordering I traverse the individual cells within each
3x3 square too.

To map square number [0, 8] to entries in puzzle_state ([0, 8]), ([0, 8]), I 
compute:
	(square/3)*3, to get the top row of the desired cells, and
	(square%3)*3, to get the left column of the desired cells.

Note that this takes advantage of integer division.

From here, traverse the remaining cells entails adding the
	iterator/3, to the top row of the desired cells, and the
	iterator%3, to the left column of the desired cells.

Note the symmetry from the square to puzzle_state mapping.

--------------------------------------------------------------------------------

sort.c

Multithreaded sorting program.

$ make sort
$ ./sort a b ... z

Where a b ... z is an arbitrary length space-delimited list of positive integers.

Uses an open source merge sort implementation (source at top of program). Splits
the input array in half, and makes two threads that sort each half. Then, the
contents of the sorted arrays are merged.

