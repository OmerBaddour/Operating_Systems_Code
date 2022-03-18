all : pid_requester pid_requester_2 resource_requester_1

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

resource_requester_1 : resource_requester_1.o resource_manager_1.o
	gcc resource_requester_1.o resource_manager_1.o -o resource_requester_1 -fopenmp -lpthread

resource_requester_1.o : resource_requester_1.c
	gcc -c -Wall resource_requester_1.c -fopenmp

resource_manager_1.o : resource_manager_1.c
	gcc -c -Wall resource_manager_1.c

.PHONY : clean 
clean :
	rm pid_requester pid_requester_2 resource_requester_1 *.o

