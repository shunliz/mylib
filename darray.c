#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <string.h>
#include "darray.h"


//当有效空间利用率大于90％时，调整空间大小为时间使用空间的2倍
//当有效空间利用率小于10％时，调整空间大小为原来一半。

//初始出度
static const size_t INIT_SIZE = 10;

struct _darray 
{
	void** arr;
	size_t size;
	size_t length;
	double highlevel; //高水位
	double lowlevel; //低水位
	DataDestroyFunc data_destroy;
	DataCompareFunc data_compare_func;
};


static int default_compare_func(void* dat1,void* dat2)
{
	return memcmp(dat1,dat2,1);
}



void set_high_level(DArray* arr,double high)
{
	double nowlevel = (double)arr->size/arr->length;
	if(nowlevel< high)
	{
		arr->highlevel = high;
	}
	else
	{
		arr->highlevel = nowlevel;
	}

	
}

void set_low_level(DArray* arr,double low)
{
	double nowlevel = (double)arr->size/arr->length;
	if(nowlevel > low)
	{
		arr->lowlevel = low;
	}
	else
	{
		arr->lowlevel = nowlevel;
	}
	
}

double get_high_level(DArray* arr)
{
	return arr->highlevel;
}

double get_low_level(DArray* arr)
{
	return arr->lowlevel;
}

static void expand(DArray* thiz)
{
	if(NULL == thiz)
	{
		printf("Cannot expand null array\n");
		return ;
	}
	if(((double)thiz->size)/thiz->length >thiz->highlevel)
	{
		thiz->arr = realloc(thiz->arr,thiz->length * 2);
		if(NULL == thiz->arr)
		{
			printf("realloc arr memory fail.\n");
			exit(1);
		}
		thiz->length = thiz->length*2;
	}
}

static void shrink(DArray* thiz)
{
	if(NULL == thiz)
	{
		printf("Cannot shrink null array\n");
		return ;
	}
	if(((double)thiz->size-1)/thiz->length <thiz->lowlevel)
	{
		thiz->arr = realloc(thiz->arr,thiz->length /2);
		if(NULL == thiz->arr)
		{
			printf("realloc arr memory fail.\n");
			exit(1);
		}
		thiz->length = thiz->length/2;
	}
}

DArray* darray_create(DataDestroyFunc data_destroy, 
					  void* ctx,
					  DataCompareFunc data_compare_func)
{
	void* data = NULL;
	DArray* darray = NULL; 

	darray = (DArray*)malloc(sizeof(DArray));
	if(darray == NULL)
	{
		printf("No memory to create darray!\n");
		exit(1);
	}
	
    data = malloc(INIT_SIZE*sizeof(void*));
	if(data == NULL)
	{
		printf("No memory for the data space!\n");
		exit(1);
	}

	darray->data_destroy = data_destroy;
	darray->data_compare_func = default_compare_func;
	if(NULL == data_destroy)
	{
		printf("Cannot Init arrat with null destructor!\n");
		return NULL;
	}
	memset(data,NULL,INIT_SIZE*sizeof(void*));
	darray->arr = data;
	darray->size = 0;
	darray->length = INIT_SIZE;
	darray->highlevel = 0.9;
	darray->lowlevel = 0.1;

	//TODO:return something impoortant in ctx,it is of no use now.
	return darray;
}

int darray_insert(DArray* thiz, size_t index, void* data)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(index<0||index>thiz->length-1)
	{
		printf("Index out of bound.\n");
		return -1;
	}
	if(NULL == data)
	{
		printf("Cannot insert null data to the array.\n");
		return -1;
	}
	expand(thiz);
	for(i=thiz->size;i>index;i--)
	{
		thiz->arr[i] = thiz->arr[i-1];
	}
	thiz->arr[i] = data;
	thiz->size ++;
	
	return 0;		
}

int darray_prepend(DArray* thiz, void* data)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(NULL == data)
	{
		printf("Cannot insert null data to the array.\n");
		return -1;
	}
	shrink(thiz);
	for(i=thiz->size;i>0;i--)
	{
		thiz->arr[i] = thiz->arr[i-1];
	}
	thiz->arr[0] = data;
	thiz->size++;
	return 0;
	
}

int darray_append(DArray* thiz, void* data)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(NULL == data)
	{
		printf("Cannot insert null data to the array.\n");
		return -1;
	}
	expand(thiz);

	thiz->size++;
	thiz->arr[thiz->size] = data;
	return 0;
}

int darray_delete(DArray* thiz, size_t index)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(index<0||index>thiz->length-1)
	{
		printf("Index out of bound.\n");
		return -1;
	}

	shrink(thiz);
	thiz->data_destroy(thiz->arr[index]);
	thiz->arr[index] = NULL;

	for(i=index;i<thiz->size-1;i++)
	{
		thiz->arr[i] = thiz->arr[i+1];
	}
	thiz->size--;
	return 0;
}

int darray_get_by_index(DArray* thiz, size_t index, void** data)
{
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(index<0||index>thiz->length-1)
	{
		printf("Index out of bound.\n");
		return -1;
	}

	*data = thiz->arr[index];
	return 0;
}

DataCompareFunc getDataCompareFunc(DArray* thiz)
{
	return thiz->data_compare_func;
}

int darray_set_by_index(DArray* thiz, size_t index, void* data)
{
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	if(index<0||index>thiz->length-1)
	{
		printf("Index out of bound.\n");
		return -1;
	}
	thiz->arr[index] = data;
	return 0;
}

size_t darray_length(DArray* thiz)
{
	return thiz->length;
}

size_t darray_size(DArray* thiz)
{
	return thiz->size;
}

int darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}
	
	for(;i<thiz->size-1;i++)
	{
		if(cmp(thiz->arr[i],ctx) == 0)
		{
			ctx = &i;
			return 0;
		}
	}
	return -1;
}

int darray_foreach(DArray* thiz, DataVisitFunc visit, void* ctx)
{
	size_t i = 0;
	if(NULL == thiz)
	{
		printf("Cannot insert data to NULL array!\n");
		return -1;
	}

	for(;i<thiz->size-1;i++)
	{
		visit(thiz->arr[i]);
	}
	return 0;
}

void darray_destroy(DArray* thiz)
{
	size_t i =0;
	if(NULL == thiz)
	{
		return ;
	}
	
	for(;i<thiz->size-1;i++)
	{
		free(thiz->arr[i]);
		thiz->arr[i] = NULL;
	}

	free(thiz);
	thiz = NULL;
}