

#include <pthread.h>
#include "libae.h"
#include "config.h"

ae_status go(routine func)
{
	pthread_t pt;
	
	int ret = pthread_create(&pt, NULL, func, NULL);
	
	if(0 != ret)
	{
		return AE_ERR;
	}
	
	/*
	if(pthread_detach(pt))
	{
		return AE_ERR;
	}
	*/
	return AE_SUCC;
}

#ifdef __GCC_ATOMIC

#define sync_pre_add(X) __sync_add_and_fetch(&X, 1)

#define sync_post_add(X) __sync_fetch_and_add(&X, 1)

#define sync_pre_sub(X) __sync_sub_and_fetch(&X, 1)

#define sync_post_sub(X) __sync_fetch_and_sub(&X, 1)

#endif


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;

static void* func(void* arg)
{
	int i = 1;
	for(i = 1; i <= 100000000; i++)
	{
		//count ++;
		sync_pre_add(count);
	}
	printf("count: %d\n", count);
	
}

int main()
{
	go(func);
	printf("count: %d\n", count);
	go(func);
	printf("count: %d\n", count);
	go(func);
	printf("count: %d\n", count);
	go(func);
	printf("count: %d\n", count);
	go(func);
	printf("count: %d\n", count);
	
	sleep(15);
	printf("count: %d\n", count);
	
	return 0;
}





