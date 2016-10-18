#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <limits.h>
int bitindex(unsigned int i) {
	static int j = sizeof(int) * 8;
	static int p = sizeof(int) * 8;
	//printf("	%d", j);
	if(j == 0)
		j = p;
	//unsigned int bitindex = count % 32;
	return (1 << (--j) ) & (i);
}
int main(int argc , char *argv[]) {
	int fd, z, count;
	unsigned int i, p = sizeof(int);
	if (argc < 2) {
		errno = EINVAL;
		perror("Bad Arguments:     ");
		return errno;
	}
	fd = open(argv[1] , O_RDONLY);
	if(fd == -1) {
		perror("Open Failed:	");
		return errno;
	}
	while(read(fd, &i, sizeof(i) ) ) {
		count = 0;
		while(count < p*8) {
			printf("%d", bitindex(i) );
			count++;
		}
	}
return 0;
}
