#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "Locker.h"
#include "nested_locker.h"

#define DEBUG

typedef struct _PrivInfo{    
	unsigned long owner;    
	int refcount;
	Locker* real_locker;    
	TaskSelfFunc task_self;
}PrivInfo;


static enum Ret  locker_nest_lock(Locker* thiz)
{   
	enum Ret ret = RET_OK;  
	PrivInfo* priv = (PrivInfo*)thiz->priv; 

#ifdef DEBUG
	printf("Enter the nested Lock.\n");
#endif
	   
	if(priv->owner == priv->task_self())    
	{        
		priv->refcount++;    
	}    
	else    
	{        
		if( (ret = locker_lock(priv->real_locker)) == RET_OK)        
		{            
			priv->refcount = 1;            
			priv->owner = priv->task_self();        
		}    
	}    
#ifdef DEBUG
	printf("Leave the nested Lock.\n");
#endif
	return ret;
}



static enum Ret  locker_nest_unlock(Locker* thiz)
{    
	enum Ret ret = RET_OK;  
	PrivInfo* priv = (PrivInfo*)thiz->priv;  

#ifdef DEBUG
	printf("Enter the nested unLock.\n");
#endif
	  
	if(priv->owner != priv->task_self())
		return RET_FAIL;   
	priv->refcount--;    
	if(priv->refcount == 0)    
	{        
		priv->owner = 0;        
		ret = locker_unlock(priv->real_locker);    
	}    
#ifdef DEBUG
	printf("Leave the nested unLock.\n");
#endif
	return ret;
}


static enum Ret  locker_nest_destroy(Locker* thiz){
	int ret = thiz->destroy(thiz);
#ifdef DEBUG
	printf("Nested Locker destroyed.\n");
#endif
	return ret == 0 ? RET_OK : RET_FAIL;
}


Locker* locker_nest_create(Locker* real_locker, TaskSelfFunc task_self){    
	Locker* thiz = (Locker*)malloc(sizeof(Locker) + sizeof(PrivInfo));    
	if(thiz != NULL){        
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		thiz->lock    = locker_nest_lock;
		thiz->unlock  = locker_nest_unlock;
		thiz->destroy = locker_nest_destroy;
		priv->real_locker = real_locker;
		priv->task_self = task_self;
		priv->owner = (*task_self)();
		priv->refcount = 0;

	}
#ifdef DEBUG
	printf("Finish create the nested Lock.\n");
#endif
	return thiz;
}

//Locker* locker = locker_pthread_create();    
//Locker* nest_locker = locker_nest_create(locker, (TaskSelfFunc)pthread_self);    
//DList*  dlist = dlist_create(NULL, NULL, nest_locker);


//single thread
//DList* dlist = dlist_create(NULL, NULL, NULL);
//multi thread
//DList* dlist = dlist_create(NULL, NULL, locker_pthread_create());
