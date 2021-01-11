all : zombie pid_requester collatz

zombie : zombie.c
	gcc zombie.c -Wall -o zombie

pid_requester : pid_requester.o pid_manager.o
	gcc pid_requester.o pid_manager.o -o pid_requester

pid_requester.o : pid_requester.c
	gcc -c -Wall pid_requester.c

pid_manager.o : pid_manager.c
	gcc -c -Wall pid_manager.c

collatz : collatz.c
	gcc collatz.c -Wall -o collatz

.PHONY : clean
clean :
	rm zombie pid_requester collatz *.o
