obj-m += task9.o
CFLAGS_task9.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod task9.ko

rem:
	sudo rmmod task9

