pthread_ex.c

Example pthread program, corresponding to figure 4.16.

$ make pthread_ex

--------------------------------------------------------------------------------

thrd-posix.c

Example pthread program, corresponding to figure 4.9.

$ make thrd-posix

--------------------------------------------------------------------------------

openmp.c

Example openmp program, corresponding to section 4.5.2.

$ make openmp
 
--------------------------------------------------------------------------------

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
of integers from 1 to 9 inclusive. I used an open-source C set implementation
to simplify this checking process (set.c and set.h).

--------------------------------------------------------------------------------

The other programs do not correspond to my version of the textbook.

