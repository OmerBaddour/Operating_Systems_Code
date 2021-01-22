all : pthread_ex thrd-posix openmp 

pthread_ex : fig4-23.c
	gcc fig4-23.c -lpthread -o pthread_ex

thrd-posix : thrd-posix.c
	gcc thrd-posix.c -lpthread -o thrd-posix

openmp :
	gcc -fopenmp openmp.c -o openmp

.PHONY : clean Driver Sumtask ThreadPoolExample

clean :
	rm pthread_ex thrd-posix openmp

Driver :
	javac Driver.java

Sumtask :
	javac SumTask.java

ThreadPoolExample :
	javac ThreadPoolExample.java
