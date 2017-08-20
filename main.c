#include <windows.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Locker.h"
#include "nested_locker.h"
#include "win_semaphor_thread.h"
#include "dlist.h"
#include "log.h"
#include "darray.h"
#include "sort.h"
#include "BiTree.h"

/*
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

void print(void* dat)
{
	printf("%d ",*(int*)dat);

}


int main(int argc,char** argv)
{

	
	//void* ctx = NULL;
	//int sleeptime = 0;
	//int i;
	//void* data = NULL;

	//DArray* darr = NULL;
	Logger* log = NULL;

	Locker* locker = locker_win_create();
	//Locker* nest_locker = locker_nest_create(locker, (TaskSelfFunc)GetCurrentThreadId);
	//init(&list,nest_locker);

	//_beginthread( thread_proc1, 4096,"Thread 1");

	//_beginthread( thread_proc2, 4096,"Thread 2");

	
	log = create_log("D:\\log.log",locker,3);
	
	log->all(log,
		     __FILE__,
			 __LINE__,
			 __FUNCTION__,
			 "this is my %dth test of print %s",
			 3,
			 "test zsl log");

	log->warn(log,
		     __FILE__,
			 __LINE__,
			 __FUNCTION__,
			 "this is my %dth test of print %s",
			 4,
			 "test zsl log");
	//log->debug(log,"Test the var list First:  and second :\n");
	//log->info(log,"this is my %dth test of print %s",4,"test zsl log");
	//log->warn(log,"this is my %dth test of print %s",5,"test zsl log");
	//log->error(log,"this is my %dth test of print %s",6,"test zsl log");
	//log->fatal(log,"this is my %dth test of print %s",7,"test zsl log");
	/*
	darr = darray_create(free,ctx,NULL);

	for(i = 0 ;i<100;i++)
	{
		data = malloc(sizeof(int));
		sleeptime = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		*(int*)data = sleeptime;
		darray_append(darr,data);
	}
	
	printf("The all data in the array.");
	darray_foreach(darr,print,NULL);
	printf("\n");

	bubble_sort(darr,0);

    printf("The all data in the array.");
	darray_foreach(darr,print,NULL);
	printf("\n");
	*/
	


	getchar();
	return 0;
}

