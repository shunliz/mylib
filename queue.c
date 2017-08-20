#include "linearcontainer.h"



struct _Queue
{
    LinearContainer* linear_container;
};

Queue* queue_create(LinearContainer* container)
{
    Queue* thiz = NULL;

    return_val_if_fail(container != NULL, NULL);

    thiz = (Queue*)malloc(sizeof(Queue));

    if(thiz != NULL)
    {
        thiz->linear_container = container;
    }

    return thiz;
}

int queue_head(Queue* thiz, void** data)
{
    return_val_if_fail(thiz != NULL && data != NULL, RET_INVALID_PARAMS);

    return linear_container_get_by_index(thiz->linear_container, 0, data);
}
int queue_push(Queue* thiz, void* data)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS); 

    return linear_container_append(thiz->linear_container, data);
}
