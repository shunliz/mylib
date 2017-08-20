#ifdef _WIN32_
#include <windows.h>
#include "win_semaphor_thread.h"
#endif

#include "pthread.h"
#include "../locker_pthread.h"
#include "stdlib.h"
#include "string.h"
#include "../Locker.h"
#include "../nested_locker.h"
#include "../dlist.h"
//#include "log.h"

dlist list = NULL;



int eq(void* data1,void* data2)
{
	int* dat1 = (int*)data1;
	int* dat2 = (int*)data2;
	
	if(*dat1>*dat2)
	{
		return *dat1-*dat2;
	}
	else
	{
		return *dat2-*dat1;
	}

}

int print(void* data)
{
	printf("%d,",*(int*)data);
}

/*

void thread_proc1( void *pParam )
{
	int sleeptime = 0;
	printf( "%s created.\n", pParam );
	while(1)
	{
		void* data1 = NULL;
		sleeptime = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		data1 = malloc(sizeof(int));
		*(int*)data1 = (int)(10.0*rand()/(RAND_MAX+1.0));
		add(list,data1);
		printf("Thread1 Add %d to the list.\n",*(int*)data1);
		printf("The all data of the list printed by thread1.\n");
		foreach(list,print,NULL);
		printf("Thread1 sleep for %d time.\n",sleeptime);
		Sleep(1000*sleeptime);
	}
	
}

void thread_proc2( void *pParam )
{
	int sleeptime = 0;
	printf( "%s created.\n", pParam );
	while(1)
	{
		void* data1 = NULL;
		sleeptime = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		data1 = malloc(sizeof(int));
		*(int*)data1 = (int)(10.0*rand()/(RAND_MAX+1.0));
		delNode(list,data1,eq);
		printf("Thread2 Delete data %d from the list.\n",*(int*)data1);
		printf("The all data of the list printed by thread2.\n");
		foreach(list,print,NULL);
		printf("Thread2 sleep for %d time.\n",sleeptime);
		Sleep(1000*sleeptime);
	}
	
}
*/


void* ThreadAProc()
{	

		
	int sleeptime = 0;
	printf( "Thread A created.\n");
	while(1)
	{
		void* data1 = NULL;
		sleeptime = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		data1 = malloc(sizeof(int));
		*(int*)data1 = (int)(10.0*rand()/(RAND_MAX+1.0));
		add(list,data1);
		printf("Thread1 Add %d to the list.\n",*(int*)data1);
		printf("The all data of the list printed by thread1.\n");
		foreach(list,print,NULL);
		printf("Thread1 sleep for %d time.\n",sleeptime);
		sleep(1*sleeptime);
	}
	
	
}
void* ThreadBProc()
{
	
	int sleeptime = 0;
	printf( "Thread B created.\n");
	while(1)
	{
		void* data1 = NULL;
		sleeptime = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		data1 = malloc(sizeof(int));
		*(int*)data1 = (int)(10.0*rand()/(RAND_MAX+1.0));
		delNode(list,data1,eq);
		printf("Thread2 Delete data %d from the list.\n",*(int*)data1);
		printf("The all data of the list printed by thread2.\n");
		foreach(list,print,NULL);
		printf("Thread2 sleep for %d time.\n",sleeptime);
		sleep(1*sleeptime);
	}
}




int main(int argc,char** argv)
{
	int k = 0;
	pthread_t thread1;
	pthread_t thread2;
	int ret1;
	int ret2;


	Locker* locker = locker_pthread_create();
	Locker* nest_locker = locker_nest_create(locker, (TaskSelfFunc)pthread_self);
	init(&list,nest_locker);

	ret1 = pthread_create(&thread1,NULL,&ThreadAProc,NULL);
	ret2 = pthread_create(&thread2,NULL,&ThreadBProc,NULL);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	
	


	//Locker* locker = locker_win_create();
	//Locker* nest_locker = locker_nest_create(locker, (TaskSelfFunc)GetCurrentThreadId);
	//init(&list,nest_locker);

	//_beginthread( thread_proc1, 4096,"Thread 1");

	//_beginthread( thread_proc2, 4096,"Thread 2");

	/*
	Logger* log = NULL;
	log = create_log("D:\\log.log",nest_locker,6);
	log->debug(log,"Test the var list First: %d and second :%d\n",1,2);
	*/


	getchar();
	return 0;
}

