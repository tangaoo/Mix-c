#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char const* str_data = "boy";
char data[1024] = {0};

int main(int argc, char** argv)
{
	// open
	int fd = open(argv[1], O_RDWR);
	
	// write
	sprintf(data, "%d\n", getpid());
	write(fd, data, strlen(data));	

	// close
	close(fd);	
}
