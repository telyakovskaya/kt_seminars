#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	DIR* dirp;
	if (argc != 2) {
		printf("Incurrent number of arguments\n");
		return 1;
	}
	if ((dirp = opendir(argv[1])) == NULL) {
		perror("Can't open the directory\n");
		return 1;
	}
	struct dirent *dir;
	struct stat stat_buf;
	while (1 ) {
		errno=0;
		if (( dir = readdir(dirp)) == NULL) {
                	if (errno) {
				perror("failed to fetch next directory entry");
			}
		}
		printf("File type: ");
		if ((dir->d_type) == DT_UNKNOWN) {
			if (lstat (dir->d_name, &stat_buf) == -1) {
                	        perror("Failed to lstat");
        	                return 1;
	                }
	        	switch (stat_buf.st_mode & S_IFMT) {
        			case S_IFBLK: printf("block device "); break;
       	   		        case S_IFCHR: printf("character device "); break;
          			case S_IFDIR: printf("directory "); break;
         			case S_IFIFO: printf("FIFO/pipe "); break;
	        		case S_IFLNK: printf("symlink "); break;
	        		case S_IFREG: printf("regular file "); break;
	        		case S_IFSOCK: printf("socket "); break;
	        		default: printf("unknown "); break;
	        	}
		}
	       	else {
			switch (dir->d_type) {
				case DT_BLK: printf("block device "); break;
				case DT_DIR: printf("directory "); break;
				case DT_CHR: printf("character device "); break;
				case DT_FIFO: printf("FIFO/pipe "); break;
                                case DT_LNK: printf("symlink "); break;
				case DT_REG: printf("regular file "); break;
				case DT_SOCK: printf("socket "); break;
			}
		}
		printf("Name: %s \n", dir->d_name);

        }
        if (closedir(dirp) != 0) {
		perror("Failed to close directory\n");
		return 1;
	}
	return 0;
}
