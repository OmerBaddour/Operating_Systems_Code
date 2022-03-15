shm : shm-posix-producer shm-posix-consumer

shm-posix-producer : shm-posix-producer.c
	gcc shm-posix-producer.c -Wall -o shm-posix-producer -lrt

shm-posix-consumer : shm-posix-consumer.c
	gcc shm-posix-consumer.c -Wall -o shm-posix-consumer -lrt

unix_pipe : unix_pipe.c
	gcc unix_pipe.c -Wall -o unix_pipe

fig3-30 : fig3-30.c
	gcc fig3-30.c -Wall -o fig3-30

fig3-32 : fig3-32.c
	gcc fig3-32.c -Wall -o fig3-32

fig3-33 : fig3-33.c
	gcc fig3-33.c -Wall -o fig3-33

fig3-34 : fig3-34.c
	gcc fig3-34.c -Wall -o fig3-34

fig3-35 : fig3-35.c
	gcc fig3-35.c -Wall -o fig3-35

simple-shell : simple-shell.o list.o
	gcc simple-shell.o list.o -o simple-shell

simple-shell.o : simple-shell.c
	gcc -c -Wall simple-shell.c

list.o : list.c
	gcc -c -Wall list.c

obj-m += tasks.o
tasks :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean kclean
clean:
	rm shm-posix-producer shm-posix-consumer unix_pipe fig3-30 fig3-32 \
	   fig3-33 fig3-34 fig3-35 simple-shell *.o

kclean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
