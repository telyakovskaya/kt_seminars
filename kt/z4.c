#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]){
        if (argc  != 2){
            return 1;};
	struct stat stat_buf;
        if (lstat(argv[1], &stat_buf)==-1) {
                perror ("Failed to start");
                return 2;
        }
	int fd1 = open(argv[1], O_RDONLY);
        if (fd1 < 0){
                printf("Error");
                return 1;};
        int fd2 = open(argv[2], O_RDONLY | O_CREAT);
        if (fd2 < 0 ){
                printf("Error");
                return 1;};
        fchmod(fd2, stat_buf.st_mode);

               
        return 0;
}
