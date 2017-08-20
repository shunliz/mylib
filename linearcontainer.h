#ifndef LINEAR_CONTAINER_H
#define LINEAR_CONTAINER_H

#ifdef __cplusplus
extern "C" {
#endif

struct _LinearContainer;
typedef struct _LinearContainer LinearContainer;

typedef Ret (*LinearContainerInsert)(LinearContainer* thiz, size_t index, void* data);
typedef Ret (*LinearContainerPrepend)(LinearContainer* thiz, void* data);
typedef Ret (*LinearContainerAppend)(LinearContainer* thiz, void* data);
typedef Ret (*LinearContainerDelete)(LinearContainer* thiz, size_t index);
typedef Ret (*LinearContainerGetByIndex)(LinearContainer* thiz, size_t index, void** data);
typedef Ret (*LinearContainerSetByIndex)(LinearContainer* thiz, size_t index, void* data);
typedef size_t (*LinearContainerLength)(LinearContainer* thiz);
typedef int    (*LinearContainerFind)(LinearContainer* thiz, DataCompareFunc cmp, void* ctx);
typedef Ret    (*LinearContainerForeach)(LinearContainer* thiz, DataVisitFunc visit, void* ctx);
typedef void   (*LinearContainerDestroy)(LinearContainer* thiz);

struct _LinearContainer
{
    LinearContainerInsert     insert;
    LinearContainerPrepend    prepend;
    LinearContainerAppend     append;
    LinearContainerDelete     del;
    LinearContainerGetByIndex get_by_index;
    LinearContainerSetByIndex set_by_index;
    LinearContainerLength     length;
    LinearContainerFind       find;
    LinearContainerForeach    foreach;
LinearContainerDestroy    destroy;

    char priv[0];
};

#ifdef __cplusplus
}
#endif

#endif