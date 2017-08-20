#ifndef SORT_H
#define SORT_H

#ifdef __cplusplus
extern "C" {
#endif


int bubble_sort(DArray* darray,int asc);

int quick_sort(DArray* darray,int asc);
int merge_sort(DArray* darray,int asc);


	
#ifdef __cplusplus
}
#endif

#endif
