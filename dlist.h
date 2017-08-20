/*
*Copyright@2009 of 周顺利. 
*All right reserved.
*
*文件名称 ： dlist.h
*功能描述：  双向链表的接口定义文件
*作者：      周顺利
*日期：      2009-8-4
*
*修改记录：
*修改人      修改日期             修改描述
*
*/

#ifndef DLIST_H
#define DLIST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "stdlib.h"
#include "Locker.h"


struct _node;
typedef struct _node node;
typedef node* dlist;
typedef int (*equal)(void* src, void* dest);
typedef int (*func_ptr)(void* data);

int init(dlist* list,Locker* locker);
int add(dlist list, void* data);
int delNode(dlist list, void* data,equal eq);
void destroy(dlist list);
void foreach(dlist list,func_ptr visit,void* ctx);

#ifdef __cplusplus
}
#endif

#endif





