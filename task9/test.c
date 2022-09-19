#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	// id
	int fd = open("/sys/kernel/eudyptula/id", O_RDWR);
	int res;
	if (fd < 0) {
		printf("cannot open file\n");
	}
	char id[10];

	//id - read
	res = read(fd, id, strlen(id));
	printf("got id : %s, %d\n", id, res);

	// id : write - send correct value
	char *id1 = "testId";
	res = write(fd, id1, strlen(id1));
	if (res < 0)
		printf("error while writing\n");
	else
		printf("writing successful\n");

	// id: write - send incorrect value
	char id2[] = "testId1";
	res = write(fd, id2, strlen(id2));
	if (res < 0)
		printf("error while writing: %d\n", res);
	else
		printf("writing successful\n");

	close(fd);
/*
	// jiffies
	fd = open("/sys/kernel/debug/edulypta/jiffies", O_RDONLY);
	if (fd < 0)
		printf("cannot open jiffies file\n");
	char data[sizeof(unsigned long int)];
	res = read(fd, data, sizeof(unsigned long int));
	printf("Kernel timer value: %s\n", data);
	close(fd);

	//foo - write 
	fd = open("/sys/kernel/debug/edulypta/foo", O_RDWR);
	if (fd < 0) {
		printf("cannot open foo file\n");
		return 0;
	}
	char buff[4096]="abcdefghijk";
	res = write(fd, buff, strlen(buff));
	if (res < 0)		
		printf("error while writing to foo:  %d\n", res);
	else
		printf("Writing to foo successful\n");

	//foo - read
	memset(buff, 0, 4096);
	res = read(fd, buff, 4096);
	printf("data read from foo: %s\n", buff);
	close(fd);
	*/
	return 0;
}
