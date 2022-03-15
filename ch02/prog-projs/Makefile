obj-m += birthday.o
birthday :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY : kclean

kclean :
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

