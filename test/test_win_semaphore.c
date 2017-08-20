#include <stdio.h>
#include <windows.h>


HANDLE   semHandle;

void thread_proc( void *pParam )
{

	DWORD  retVal;
	printf( "\t%s created.\n", pParam );

	retVal = WaitForSingleObject(semHandle, INFINITE);
	if (retVal == WAIT_FAILED)
		return 2;
	printf( "\tSemaphor blocked by %s. (%lx)\n", pParam, retVal);
	printf( "\t%s sleeps for 5 sec.\n", pParam );
	Sleep(5);
	if( ! ReleaseSemaphore(semHandle, 1, NULL) )
		printf("ReleaseSemaphore error: %d\n", GetLastError());
	printf( "\tSemaphor released by %s.)\n", pParam);
}

int main( int argc, char **argv )
{
	HANDLE    *threadId1;
	HANDLE    *threadId2;
	int        hThrd;
	unsigned long  stacksize = 0;
	int	    arg1;
	if( argc < 2 )
		arg1 = 7;
	else
		arg1 = atoi( argv[1] );
	printf( "Intra Process Semaphor test.\n" );
	printf( "Start.\n" );
	semHandle = CreateSemaphore(NULL, 1, 65536, NULL);
	if( semHandle == (HANDLE) NULL)
	{
		printf("CreateSemaphore error: %d\n", GetLastError());
	}
	printf( "Semaphor created.\n" );

	if( stacksize < 8192 )
		stacksize = 8192;
	else
		stacksize = (stacksize/4096+1)*4096;

	hThrd = _beginthread( thread_proc, // Definition of a thread entry
		NULL,
		stacksize,
		"Thread 1");
	if (hThrd == -1)
		return 1;
	*threadId1 = (HANDLE) hThrd;
	hThrd = _beginthread( thread_proc, // Definition of a thread entry
		NULL,
		stacksize,
		"Thread 2");
		if (hThrd == -1)
			return 1;
	*threadId2 = (HANDLE) hThrd;
	printf( "Main thread sleeps 5 sec.\n" );
	Sleep(5);
	if( ! ReleaseSemaphore(semHandle, 1, NULL) )
		printf("ReleaseSemaphore error: %d\n", GetLastError());
	printf( "Semaphor released.\n" );
	printf( "Main thread sleeps %d sec.\n", arg1 );

	Sleep (arg1);
	if( ! ReleaseSemaphore(semHandle, 1, NULL) )
		printf("ReleaseSemaphore error: %d\n", GetLastError());

	printf( "Semaphor released.\n" );
	printf( "Main thread sleeps %d sec.\n", arg1 );
	Sleep (arg1);
	CloseHandle(semHandle);

	printf( "Semaphor deleted.\n" );
	printf( "Main thread sleeps 5 sec.\n" );

	Sleep (5);
	printf( "Stop.\n" );
	return 0;
}
