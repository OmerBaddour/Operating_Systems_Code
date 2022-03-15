cp_posix : cp_posix.c
	gcc -Wall cp_posix.c -o cp_posix

obj-m += simple.o birthday.o
birthday :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY : clean kclean
clean :
	rm cp_posix

kclean :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
