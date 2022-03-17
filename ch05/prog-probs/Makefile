all : pid_requester 

pid_requester : pid_requester.o pid_manager.o
	gcc pid_requester.o pid_manager.o -o pid_requester -lpthread

pid_requester.o : pid_requester.c
	gcc -c -Wall pid_requester.c 

pid_manager.o : pid_manager.c
	gcc -c -Wall pid_manager.c

.PHONY : clean 
clean :
	rm pid_requester *.o

