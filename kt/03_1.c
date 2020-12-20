#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define BUFSIZE 512


int main(int argc, char *argv[]) {
	if (argc != 3) {
                printf ("Usage: %s some.file\n", argv[0]);
                return 1;
	}
	char buf[BUFSIZE];
	ssize_t nbytes, nbytes_w;
	struct stat stat_buf;
        if (lstat (argv[1], &stat_buf) == -1) {
                perror("Failed to lstat");
                return 2;
        }
	if (!S_ISREG(stat_buf.st_mode)) {
		printf("File to copy is not regular file\n");
		return 1;
	}
        int fd1 = open(argv[1], O_RDONLY);
        if (fd1 == -1) {
                perror("Can't open file to read\n");
                return 1;
        }
	int fd2 = open(argv[2], O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
        if (fd2 == -1) {
                perror("Can't open file to write\n");
                return 1;
        }
	size_t nbytes_r;
	while ((nbytes_r = read(fd1, buf, BUFSIZE)) > 0) {
		nbytes = nbytes_r;
		while (nbytes) {
			nbytes_w = write(fd2, &buf[nbytes_r - nbytes], nbytes);
			nbytes = nbytes - nbytes_w;
		}
	}
        int result = 0;
        if (close(fd1) < 0){
                result = errno;
                perror("Failed to close source file");
        }
        if (close(fd2) < 0){
                result = errno;
                perror("Failed to close destination file");
        }
        return result;
}
