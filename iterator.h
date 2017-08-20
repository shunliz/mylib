#ifudef ITERATOR_H
#define ITERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

struct _iterator;

typedef struct _iterator iterator;

 

typedef BOOL  (iterator_prev)(iterator* iter);

typedef BOOL  (iterator_next)(iterator* iter);

typedef BOOL  (iterator_advance)(iterator* iter, int offset);

typedef BOOL  (iterator_is_valid)(iterator* iter);

typedef void* (iterator_get_data)(iterator* iter);

typedef void  (iterator_destroy)(iterator* iter);

 

struct _iterator

{

    iterator_prev      prev;

    iterator_next      next;

    iterator_advance   advance;

    iterator_get_data  get_data;

    iterator_is_valid  is_valid;

    iterator_destroy   destroy;

 

    char priv[1];

};

#ifdef __cplusplus
}
#endif

#endif
