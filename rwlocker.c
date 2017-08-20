#include "rwlocker.h"

struct _RwLocker 
{
	int readers;
	Emode mode;
	Locker* rw_locker;
	Locker* rd_locker;
};

RwLocker* rw_locker_create(Locker* rw_locker, Locker* rd_locker)
{
    RwLocker* thiz = NULL;
    return_val_if_fail(rw_locker != NULL && rd_locker != NULL, NULL);

    thiz = (RwLocker*)malloc(sizeof(RwLocker));
    if(thiz != NULL)
    {
        thiz->readers = 0;
        thiz->mode = RW_LOCKER_NONE;
        thiz->rw_locker = rw_locker;
        thiz->rd_locker = rd_locker;
    }

    return thiz;
}

/*
写的时候不允许任何其它线程读或者写，读的时候允许其它线程读，但不允许其它线程写。所以在实现时，写的时候一定要加锁，第一个读的线程要加锁，后面其它线程读时，只是增加锁的引用计数。我们需要两个锁：一个锁用来保存被保护的对象，一个锁用来保护引用计数。

*/

Ret rw_locker_wrlock(RwLocker* thiz)
{
    Ret ret = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if((ret = locker_lock(thiz->rw_locker)) == RET_OK)
    {
        thiz->mode = RW_LOCKER_WR;
    }

    return ret;
}

/*
加写锁很简单，直接加保护受保护对象的锁，然后修改锁的状态为已加写锁。后面其它的线程想写，就会这个锁上等待，如果想读也要等待
*/




Ret rw_locker_unlock(RwLocker* thiz)
{
    Ret ret = RET_OK;
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if(thiz->mode == RW_LOCKER_WR)
    {
        thiz->mode == RW_LOCKER_NONE;
        ret = locker_unlock(thiz->rw_locker);
    }
    else
    {
        assert(thiz->mode == RW_LOCKER_RD);
        if((ret = locker_lock(thiz->rd_locker)) == RET_OK)
        {
            thiz->readers--;
            if(thiz->readers == 0)
            {
                thiz->mode == RW_LOCKER_NONE;
                ret = locker_unlock(thiz->rw_locker);
            }
            locker_unlock(thiz->rd_locker);
        }
    }

    return ret;
}

