#include "stdio.h"
#include <pthread.h>

pthread_mutex_t MyMutex;
long a[100000] = {0};
int i =0,j=0;
void* ThreadAProc()
{	
	while(1)
	{
		printf("add node %d to list\n",i);
		pthread_mutex_lock(&MyMutex);
		a[i] = i;
		i++;
		pthread_mutex_unlock(&MyMutex);
		sleep(3);
	}
	
	return NULL;
}

void* ThreadBProc()
{
	
	while(1)
	{
		printf("delete node %d from list\n",a[j]);
		pthread_mutex_lock(&MyMutex);
		j++;
		pthread_mutex_unlock(&MyMutex);
		sleep(5);
	}
	
	return NULL;
}


int main()
{
	int k = 0;
	pthread_t thread1;
	pthread_t thread2;
	int ret1;
	int ret2;

	pthread_mutex_init(&MyMutex,NULL);
	ret1 = pthread_create(&thread1,NULL,&ThreadAProc,NULL);
	ret2 = pthread_create(&thread2,NULL,&ThreadBProc,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	pthread_mutex_destroy(&MyMutex);
	
}
