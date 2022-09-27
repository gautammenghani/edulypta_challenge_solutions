obj-m += task18.o
CFLAGS_task18.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
ins:
	sudo insmod task18.ko

rem:
	sudo rmmod task18

