obj-m += task13.o
CFLAGS_task13.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod task13.ko

rem:
	sudo rmmod task13

