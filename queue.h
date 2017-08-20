#ifndef RW_LOCKER_H
#define RW_LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif


Queue* queue_create(LinearContainer* container);
int queue_head(Queue* thiz, void** data);
int queue_push(Queue* thiz, void* data);


#ifdef __cplusplus
}
#endif

#endif