#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define BUFSIZE 512

int main(int argc, char *argv[]) {
	if (argc != 3) {
        	printf ("Usage: %s some.file\n", argv[0]);
                return 1;
        }
	char text[BUFSIZE];
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
	while (1) {
                ssize_t count_read = read(fd1, text, sizeof(text));
                if (count_read == -1) {
                        perror("Failed to read\n");
                        return 6;
                }
                if (count_read == 0) {
                        break;
                }
                ssize_t i = 0;
                while (i < count_read) {
                        ssize_t count_write = write(fd2, text+i, BUFSIZE-i);
                        if (count_write == -1) {
                                perror("Failed to write");
                                return 7;
                        }
                        i += count_write;
                }
        }
	if (fchmod(fildes_w, stat_buf.st_mode) != 0) {
		perror("Error with copying meta data");
	}
	struct timespec times[2] = {stat_buf.st_atim, stat_buf.st_mtim};
	if (futimens(fd2, times) != 0) {
		perror("Error with copying time");
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
