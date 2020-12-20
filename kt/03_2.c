#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define BUFSIZE 512
int main(int argc, char *argv[]){
        struct stat fmode;
        lstat (argv[1], &fmode);
        if (argc  != 2){
		printf ("Usage: %s some.file\n", argv[0]);
                return 1;};
        if (!S_ISREG(fmode.st_mode)){
                printf("File is not regular");
                return 1;};
        char text[BUFSIZE];
        int fd1 = open(argv[1], O_RDONLY);
        if (fd1 < 0){
                perror("Can't open file to read\n");
                return 1;};
        int fd2 = open(argv[2], O_RDWR | O_CREAT | 0600);
        if (fd2 < 0 ){
                perror("Can't open file to write\n");
                return 1;};
	int  ofst = 0;
        while (pread(fd1, text, BUFSIZE, ofst)!=0){
            if(pwrite(fd2, text, BUFSIZE, ofst) < 0){
                perror("Error with copying");
                return 1;};
            ofst+= 512;	};
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

