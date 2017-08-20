#include "stdio.h"
#include "darray.h"
#include "sort.h"

static void swap(void** dat1, void** dat2)
{
	void* temp = *dat1;
	*dat1 = *dat2;
	*dat2 = *dat1;
}


int bubble_sort(DArray* darray,int asc)
{

	size_t i,j;
		
	for(i=0;i<darray_size(darray)-1;i++)
	{
		for(j=i+1;j<darray_size(darray)-1;j++)
		{
			void* dat1 = NULL,*dat2 = NULL;
			if(asc == 1)
			{
				if((*getDataCompareFunc(darray))(darray_get_by_index(darray,i,&dat1),darray_get_by_index(darray,j,&dat2))>0)
				{
					swap(&dat1,&dat2);
				}
			}
			else
			{
				if((*getDataCompareFunc(darray))(darray_get_by_index(darray,i,&dat1),darray_get_by_index(darray,j,&dat2))<0)
				{
					swap(&dat1,&dat2);
				}
			}
		}
		
	}
	
	return 0;
}


int quick_sort(DArray* arr,int asc)
{
	return 0;
}

int merge_sort(DArray* arr,int asc)
{
	return 0;
}
