all : pid_requester pid_requester_2 resource_requester resource_requester_monitor pi_mc pi_mc_2 pi_mc_3 barrier_tester

pid_requester : pid_requester.o pid_manager.o
	gcc pid_requester.o pid_manager.o -o pid_requester -lpthread

pid_requester.o : pid_requester.c
	gcc -c -Wall pid_requester.c 

pid_manager.o : pid_manager.c
	gcc -c -Wall pid_manager.c

pid_requester_2 : pid_requester_2.o pid_manager_2.o
	gcc pid_requester_2.o pid_manager_2.o -o pid_requester_2 -lpthread

pid_requester_2.o : pid_requester_2.c
	gcc -c -Wall pid_requester_2.c 

pid_manager_2.o : pid_manager_2.c
	gcc -c -Wall pid_manager_2.c

resource_requester : resource_requester.o resource_manager.o
	gcc resource_requester.o resource_manager.o -o resource_requester -fopenmp -lpthread

resource_requester.o : resource_requester.c
	gcc -c -Wall resource_requester.c -fopenmp

resource_manager.o : resource_manager.c
	gcc -c -Wall resource_manager.c

resource_requester_monitor : resource_requester_monitor.o resource_manager_monitor.o
	gcc resource_requester_monitor.o resource_manager_monitor.o -o resource_requester_monitor -fopenmp -lpthread

resource_requester_monitor.o : resource_requester_monitor.c
	gcc -c -Wall resource_requester_monitor.c -fopenmp

resource_manager_monitor.o : resource_manager_monitor.c
	gcc -c -Wall resource_manager_monitor.c

pi_mc : pi_mc.c
	gcc pi_mc.c -Wall -o pi_mc -lpthread -lm

pi_mc_2 : pi_mc_2.c
	gcc pi_mc_2.c -Wall -o pi_mc_2 -lpthread -lm

pi_mc_3 : pi_mc_3.c
	gcc pi_mc_3.c -Wall -o pi_mc_3 -fopenmp -lm

barrier_tester : barrier_tester.o barrier.o
	gcc barrier_tester.o barrier.o -Wall -o barrier_tester -lpthread

barrier_tester.o : barrier_tester.c
	gcc -c -Wall barrier_tester.c

barrier.o : barrier.c
	gcc -c -Wall barrier.c

.PHONY : clean 
clean :
	rm pid_requester pid_requester_2 resource_requester resource_requester_monitor pi_mc pi_mc_2 pi_mc_3 barrier_tester *.o

