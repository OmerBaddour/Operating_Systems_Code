all : sudoku_validator sort 

sudoku_validator : sudoku_validator.c
	gcc sudoku_validator.c -Wall -lpthread -o sudoku_validator

sort : sort.c
	gcc sort.c -Wall -lpthread -o sort

.PHONY : clean 

clean :
	rm sudoku_validator sort

