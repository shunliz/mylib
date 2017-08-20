#ifndef DARRAY_H
#define DARRAY_H

#ifdef __cplusplus
extern "C" {
#endif



struct _darray;
typedef struct _darray DArray;

typedef void (*DataDestroyFunc)(void* data);
typedef int (*DataCompareFunc)(void* dat,void* dat2);
typedef void (*DataVisitFunc)(void* data);

DArray* darray_create(DataDestroyFunc data_destroy,
					  void* ctx,
					  DataCompareFunc data_compare_func);

int    darray_insert(DArray* thiz, size_t index, void* data);
int    darray_prepend(DArray* thiz, void* data);
int    darray_append(DArray* thiz, void* data);
int    darray_delete(DArray* thiz, size_t index);
int    darray_get_by_index(DArray* thiz, size_t index, void** data);
int    darray_set_by_index(DArray* thiz, size_t index, void* data);
size_t  darray_length(DArray* thiz);
size_t darray_size(DArray* thiz);
int    darray_find(DArray* thiz, DataCompareFunc cmp, void* ctx);
int   darray_foreach(DArray* thiz, DataVisitFunc visit, void* ctx);
DataCompareFunc getDataCompareFunc(DArray* thiz);

void darray_destroy(DArray* thiz);



#ifdef __cplusplus
}
#endif

#endif
