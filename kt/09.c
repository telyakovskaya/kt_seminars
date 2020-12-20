#include <sys/vfs.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
        	printf ("Usage: %s [path]\n", argv[0]);
       	        return 1;
       	}
       	struct statvfs buf;
	if ((statvfs(argv[1], &buf)) == -1) {
		printf("Failed to statvfs");
		return 1;
	}
	printf("Total: %lu \n",buf.f_blocks * buf.f_frsize);
	printf("Available: %lu\n", buf.f_bavail * buf.f_frsize);
	printf("Free: %lu\n", buf.f_bfree * buf.f_frsize);
	printf("Used: %lu\n",buf.f_blocks * buf.f_frsize - buf.f_bfree * buf.f_frsize);
	return 0;
}
