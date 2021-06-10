#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/select.h>

#define tt_max3(x, y, z)  (((x) > (y))? (((x) > (z))? (x) : (z)) : (((y) > (z))? (y) : (z)))

void* write_pipe(void* arg)
{
	int fd = (int)arg;
	int i = 0;
	char buff[10];

	printf("thread, %d\n", fd);

	while(1)
	{
		sprintf(buff, "%d,", i++);
		write(fd, buff, strlen(buff));
		sleep(1);
	}
}

int main(void)
{
	char buff[16];
	pthread_t t1, t2, t3;
	int p1[2]={0}, p2[2]={0}, p3[3]={0};
	int num;

	pipe(p1);
	pipe(p2);
	pipe(p3);

	printf("%d, %d, %d\n", p1[1], p2[1], p3[1]);

	fcntl(p1[0], F_SETFL, fcntl(p1[0], F_GETFL)|O_NONBLOCK);
	fcntl(p1[1], F_SETFL, fcntl(p1[1], F_GETFL)|O_NONBLOCK);
	fcntl(p2[0], F_SETFL, fcntl(p2[0], F_GETFL)|O_NONBLOCK);
	fcntl(p2[1], F_SETFL, fcntl(p2[1], F_GETFL)|O_NONBLOCK);
	fcntl(p3[0], F_SETFL, fcntl(p3[0], F_GETFL)|O_NONBLOCK);
	fcntl(p3[1], F_SETFL, fcntl(p3[1], F_GETFL)|O_NONBLOCK);

	pthread_create(&t1, NULL, write_pipe, (void*)p1[1]);
	pthread_create(&t2, NULL, write_pipe, (void*)p2[1]);
	pthread_create(&t3, NULL, write_pipe, (void*)p3[1]);

	fd_set fds;

	while(1)
	{
		FD_ZERO(&fds);
		FD_SET(p1[0], &fds);
		FD_SET(p2[0], &fds);
		FD_SET(p3[0], &fds);
		select(tt_max3(p1[0], p2[0], p3[0]) + 1, &fds, NULL, NULL, NULL);	
        
		if(FD_ISSET(p1[0], &fds))
		{
			sleep(1);
		    num = read(p1[0], buff, sizeof(buff));
			buff[num] = '\0';
		    printf("read p1, %s \n", buff);
		}

		if(FD_ISSET(p2[0], &fds))
		{
		    num = read(p2[0], buff, sizeof(buff));	
			buff[num] = '\0';
		    printf("read p2, %s \n", buff);
		}

		if(FD_ISSET(p3[0], &fds))
		{
		    num = read(p3[0], buff, sizeof(buff));	
			buff[num] = '\0';
		    printf("read p3, %s \n", buff);
		}
	}
}

		
