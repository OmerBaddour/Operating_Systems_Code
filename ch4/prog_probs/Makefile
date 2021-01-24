all : pid_requester stats pi_mc_1 pi_mc_2 primes Date fibonacci

pid_requester : pid_requester.o pid_manager.o
	gcc pid_requester.o pid_manager.o -o pid_requester -fopenmp 

pid_requester.o : pid_requester.c
	gcc -c -Wall pid_requester.c -fopenmp

pid_manager.o : pid_manager.c
	gcc -c -Wall pid_manager.c

stats : stats.c
	gcc stats.c -Wall -o stats -lpthread

pi_mc_1 : pi_mc_1.c
	gcc pi_mc_1.c -Wall -o pi_mc_1 -lpthread -lm

pi_mc_2 : pi_mc_2.c
	gcc pi_mc_2.c -Wall -o pi_mc_2 -fopenmp -lm

primes : primes.c
	gcc primes.c -Wall -o primes -lpthread -lm

fibonacci : fibonacci.c
	gcc fibonacci.c -Wall -o fibonacci -lpthread -lm

.PHONY : clean Date
clean :
	rm pid_requester stats pi_mc_1 pi_mc_2 primes fibonacci *.o *.class

Date :
	javac DateServer.java
	javac DateClient.java
