#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define bufsize 512
int main(int argc, char *argv[]){
	struct stat fmode;
	lstat (argv[1], &fmode);
	if (argc  != 2){
		return 1;};
	if ((fmode.st_mode & S_IFMT) != S_IFREG){
		printf("File is not regular");
		return 1;};
        char text[bufsize];	
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0){
		printf("Error");
		return 1;};
	int fd2 = open(argv[2], O_RDWR | O_CREAT);
	if (fd2 < 0 ){
		printf("Error");
		return 1;};
	while (read(fd1, text, bufsize)!=0){
            if(write(fd2, text, bufsize) < 0){
                printf("Error");
                return 1;};	};
	close(fd1);
	if (close(fd1) < 0){
		printf("Error");
		return 1;};
	close(fd2);
	if (close(fd2) < 0){
		printf("Error");
		return 1;};
	return 0;
}
	    
