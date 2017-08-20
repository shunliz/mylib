#ifndef LOCKER_H
#define LOCKER_H

#ifdef __cplusplus
extern "C" {
#endif

struct _HashTable
{
    DataHashFunc    hash;
    DList**         slots;
    size_t           slot_nr;
    DataDestroyFunc  data_destroy;
    void*           data_destroy_ctx;
};



#ifdef __cplusplus
}
#endif

#endif