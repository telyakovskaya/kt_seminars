#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main (int argc, char *argv[]){
	int fd;
	fd = open(argv[1], O_RDWR);
	size_t s = strlen(argv[2]);
	write(fd, argv[2], s);
        close(fd);
	return 0;
}

