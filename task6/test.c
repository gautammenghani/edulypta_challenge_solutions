#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd = open("/dev/edulypta", O_RDWR);
	int res;
	if (fd < 0) {
		printf("cannot open file\n");
	}
	char id[10];

	//read
	res = read(fd, id, strlen(id));
	printf("got id : %s\n", id);

	// write - send correct value
	char *id1 = "testId";
	res = write(fd, id1, strlen(id1));
	if (res < 0)
		printf("error while writing\n");
	else
		printf("writing successful\n");

	// write - send incorrect value
	char id2[] = "testId1";
	res = write(fd, id2, strlen(id2));
	if (res < 0)
		printf("error while writing: %d\n", res);
	else
		printf("writing successful\n");

	close(fd);
	return 0;
}
