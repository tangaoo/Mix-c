#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define __USE_GNU
#include <pthread.h>
#include <sched.h>

long long a = 0;
long long b = 0;

int attach_cpu(int cpu_index)
{
    int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
    if (cpu_index < 0 || cpu_index >= cpu_num)
    {
        printf("cpu index ERROR!\n");
        return -1;
    }

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu_index, &mask);

    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
    {
        printf("set affinity np ERROR!\n");
        return -1;
    }

    return 0;
}


void *thread1(void *param)
{
    attach_cpu(0);

    long long i;
    for (i = 0; i < 10000000000; i++)
    {
        a++;
    }
}

void *thread2(void *param)
{
    attach_cpu(0);

    long long i;
    for (i = 0; i < 10000000000; i++)
    {
        b++;
    }
}


int main()
{
    pthread_t t1;
    pthread_t t2;

    int policy;
    struct sched_param param;

    if (pthread_create(&t1, NULL, thread1, NULL) < 0)
    {
        printf("create t1 failed!\n");
        return -1;
    }

    param.sched_priority = 10;
    policy = SCHED_FIFO;
    pthread_setschedparam(t1, policy, &param);

    if (pthread_create(&t2, NULL, thread2, NULL) < 0)
    {
        printf("create t2 failed!\n");
        return -1;
    }

    param.sched_priority = 11;
    policy = SCHED_FIFO;
    pthread_setschedparam(t2, policy, &param);

    while (1)
    {
        printf("a=%lld, b=%lld\n", a, b);
        sleep(1);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
