obj-m += task12.o
CFLAGS_task12.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod task12.ko

rem:
	sudo rmmod task12

