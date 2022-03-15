all : pthread_ex thrd-posix openmp Driver

pthread_ex : fig4-23.c
	gcc fig4-23.c -lpthread -o pthread_ex

thrd-posix : thrd-posix.c
	gcc thrd-posix.c -lpthread -o thrd-posix

openmp : openmp.c
	gcc -fopenmp openmp.c -o openmp

.PHONY : clean Driver 

clean :
	rm pthread_ex thrd-posix openmp *.class

Driver :
	javac Driver.java
