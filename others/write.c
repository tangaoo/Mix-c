#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char const* str_data = "boy";
char read_data[1024] = {0};

int main(int argc, char** argv)
{
	// open
	int fd = open(argv[1], O_RDWR | O_APPEND);
	
	// write
	write(fd, str_data, strlen(str_data));	

	// set index start
	lseek(fd, 0, SEEK_SET);

	//read
	int num = read(fd, read_data, sizeof(read_data));
	
	// print
	read_data[num] = '\0';
	printf("%s \n", read_data);
}
