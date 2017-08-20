#ifndef RW_LOCKER_H
#define RW_LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Locker.h"

enum Emode {
	RW_LOCKER_NONE,
	RW_LOCKER_WR,
	RW_LOCKER_RD
};

struct _RwLocker;
typedef struct _RwLocker RwLocker;

RwLocker* rw_locker_create(Locker* rw_locker, Locker* rd_locker);

Ret rw_locker_wrlock(RwLocker* thiz);
Ret rw_locker_rdlock(RwLocker* thiz);
Ret rw_locker_unlock(RwLocker* thiz);

void rw_locker_destroy(RwLocker* thiz);


#ifdef __cplusplus
}
#endif

#endif



