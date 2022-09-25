obj-m += task17.o
CFLAGS_task17.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

