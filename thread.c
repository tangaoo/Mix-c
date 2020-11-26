#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

char* thread_func1(void *arg)
{
	pid_t pid = getpid();
	pthread_t tid = pthread_self();

	printf("%s pid,%u, tid,%u (0x%x)\n", (char *)arg, pid, tid, tid);
	char* msg = "thread_func1";

	return msg;
}

void *thread_func2(void *arg)
{
	pid_t pid =getpid();
	pthread_t tid = pthread_self();

	printf("%s pid,%u, tid,%u (0x%x)\n", (char *)arg, pid, tid, tid);
	char *msg = "thread_func2";
	while(1)
	{
		printf("%s running\n", msg);
		sleep(1);
	}

	return NULL;
}

int thread1_main(void)
{
	pthread_t tid1, tid2;

	if(pthread_create(&tid1, NULL, (void *)thread_func1, "thread_func1") != 0)
	{
		printf("err");	
		exit(-1);
	}

	if(pthread_create(&tid2, NULL, (void *)thread_func2, "thread_func2") != 0)
	{
		printf("err");	
		exit(-1);
	}

	pthread_detach(tid2);
	char* rev = NULL;
	pthread_join(tid1, (void *)&rev);
	printf("%s, return.\n", rev);
	sleep(10);
	pthread_cancel(tid2);

	printf("main thread end.\n");

	return 0;
}
