/*
*Copyright@2009 of ��˳��. 
*All right reserved.
*
*�ļ����� �� dlist.h
*����������  ˫������Ľӿڶ����ļ�
*���ߣ�      ��˳��
*���ڣ�      2009-8-4
*
*�޸ļ�¼��
*�޸���      �޸�����             �޸�����
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





