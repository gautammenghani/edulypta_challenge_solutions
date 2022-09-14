obj-m += task8.o
CFLAGS_task8.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

