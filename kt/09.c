#include <sys/vfs.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
        	printf ("Usage: %s [path]\n", argv[0]);
       	        return 1;
       	}
       	struct statfs buf;
	if ((statfs(argv[1], &buf)) == -1) {
		printf("Failed to statfs");
		return 1;
	}
	printf("Total: %lu \n",buf.f_blocks * buf.f_bsize);
	printf("Available: %lu\n", buf.f_bavail * buf.f_bsize);
	printf("Free: %lu\n", buf.f_bfree * buf.f_bsize);
	printf("Used: %lu\n",buf.f_blocks * buf.f_bsize - buf.f_bfree * buf.f_bsize);
	return 0;
}
