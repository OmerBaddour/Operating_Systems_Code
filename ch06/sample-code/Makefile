all : posix-rt posix-sched

posix-rt : posix-rt.c
	gcc posix-rt.c -o posix-rt -lpthread

posix-sched : posix-sched.c
	gcc posix-sched.c -o posix-sched -lpthread

.PHONY : clean

clean : 
	rm posix-rt posix-sched
