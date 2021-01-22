all : pid_requester

pid_requester : pid_requester.o pid_manager.o
	gcc pid_requester.o pid_manager.o -o pid_requester -fopenmp 

pid_requester.o : pid_requester.c
	gcc -c -Wall pid_requester.c -fopenmp

pid_manager.o : pid_manager.c
	gcc -c -Wall pid_manager.c

.PHONY : clean
clean :
	rm pid_requester *.o
