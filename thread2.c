#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define LEN 100000
int num = 0;

void *thread_func(void *arg)
{
	pthread_mutex_t *p_mutex = (pthread_mutex_t *)arg;
	for(int i=0; i<LEN; i++)
	{
//		pthread_mutex_lock(p_mutex);
		num += 1;
//		pthread_mutex_unlock(p_mutex);
	}

	return NULL;
}

int thread2_main(void)
{
	pthread_mutex_t m_mutex;
	pthread_mutex_init(&m_mutex, NULL);

	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, (void *)thread_func, (void *)&m_mutex);	
	pthread_create(&tid2, NULL, (void *)thread_func, (void *)&m_mutex);	

	char * rev = NULL;
	pthread_join(tid1, (void *)&rev);
	pthread_join(tid2, (void *)&rev);

	pthread_mutex_destroy(&m_mutex);
	printf("right, %d, fact, %d\n", LEN*2, num);
	return 0;
}
