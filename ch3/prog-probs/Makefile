all : zombie pid_requester collatz shm_collatz QOTD Haiku

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

shm_collatz : shm_collatz.c
	gcc shm_collatz.c -Wall -o shm_collatz -lrt -lm

.PHONY : clean QOTD Haiku
clean :
	rm zombie pid_requester collatz shm_collatz *.o *.class

QOTD :
	javac QOTDServer.java
	javac QOTDClient.java

Haiku :
	javac HaikuServer.java
	javac HaikuClient.java
