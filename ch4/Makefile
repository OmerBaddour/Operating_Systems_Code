all : pthread_ex thrd-posix openmp sudoku_validator sort 

pthread_ex : fig4-23.c
	gcc fig4-23.c -lpthread -o pthread_ex

thrd-posix : thrd-posix.c
	gcc thrd-posix.c -lpthread -o thrd-posix

openmp : openmp.c
	gcc -fopenmp openmp.c -o openmp

sudoku_validator : sudoku_validator.c
	gcc sudoku_validator.c -Wall -lpthread -o sudoku_validator

sort : sort.c
	gcc sort.c -Wall -lpthread -o sort

.PHONY : clean Driver Sumtask ThreadPoolExample

clean :
	rm pthread_ex thrd-posix openmp sudoku_validator sort

Driver :
	javac Driver.java

Sumtask :
	javac SumTask.java

ThreadPoolExample :
	javac ThreadPoolExample.java
