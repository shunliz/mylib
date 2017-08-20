#ifndef NESTED_LOCKER_H
#define NESTED_LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long (*TaskSelfFunc)(void);

Locker* locker_nest_create(Locker* real_locker, TaskSelfFunc task_self);

#ifdef __cplusplus
}
#endif

#endif
