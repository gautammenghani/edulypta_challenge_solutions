obj-m += task19.o
CFLAGS_task19.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod task19.ko

rem:
	sudo rmmod task19

