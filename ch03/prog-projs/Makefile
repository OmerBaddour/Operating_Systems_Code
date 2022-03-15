simple-shell : simple-shell.o list.o
	gcc simple-shell.o ../sample-code/list.o -o simple-shell

simple-shell.o : simple-shell.c
	gcc -I../sample-code -c -Wall simple-shell.c

list.o :
	cd ../sample-code && make list.o

obj-m += tasks.o
tasks :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean kclean
clean:
	rm simple-shell *.o ../sample-code/list.o

kclean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
