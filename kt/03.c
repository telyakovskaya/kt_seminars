#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 512
int main(int argc, char *argv[]){
	if (argc  != 3){
                return 1;
	}
	struct stat fmode;
	lstat (argv[1], &fmode);
	if (!S_ISREG(fmode.st_mode)){
		printf("File is not regular");
		return 1;
	}
        char text[BUFSIZE];	
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0){
		perror("Failed to open source file");
		return 1;
	}
	int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0600);
	if (fd2 < 0 ){
		printf("Failed to open destination file for working");
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
	    
