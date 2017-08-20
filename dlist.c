/*******************************************************************************
*Copyright@2009 of ��˳��. 
*All right reserved.
*
*�ļ����� �� dlist.c
*����������  ˫����������ʵ���ļ���ʵ��˫������Ľڵ㶨�����ز���������
*���ߣ�      ��˳��
*���ڣ�      2009-8-4
*
*�޸ļ�¼��
*�޸���           �޸�����                   �޸�����
*
********************************************************************************/

#include "ctype.h"
#include "dlist.h"
#include "Locker.h"
//#include "log.h"

/*
*˫���������ݽڵ�ṹ���塣
*���ԣ�data ����ָ�룬void*����ָ�룬ʵ�������ͨ���ԡ�
*      prev ǰ��ָ��
*      next ����ָ��
*/

struct _node
{
	Locker* locker;
	void* data;
	struct _node* prev;
	struct _node* next;
};

/*
*����������˫�������ʼ����������ʼ��һ��ͷ�ڵ㣬
*          ǰ��ͺ����Լ��ڵ�����ָ�붼Ϊ�ա�
*������    list ��Ҫ��ʼ����˫������
*����ֵ��  0����ʾ�ڴ治�㣬��ʼ��ʧ�ܡ�
*          1����ʾ��ʼ���ɹ���
*/
int init(dlist* list,Locker* locker)
{
	if(NULL == *list)
	{
		*list = malloc(sizeof(node));
		if(NULL == *list)
			return 0;
		(*list)->prev = NULL;
		(*list)->next = NULL;
		(*list)->data = NULL;
		(*list)->locker = locker;
	}
	//log->debug(log,"A dlist inited at %p.\n",*list);
	return 1;
}

/*
*���������������˫����������һ���ڵ㡣
*������    list ��Ҫ�������ݵ�˫������
*          data ���ӵ�����
*����ֵ��  0����ʾ����ʧ��
*          1����ʾ���ӳɹ�
*/
int add(dlist list, void* data)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("���ȳ�ʼ������\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	if(NULL == data)
	{
		printf("�������ӿ����ݵ�����\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	
	p = list->next;
	temp = (node*)malloc(sizeof(node));
	if(NULL == temp)
	{
		list->locker->unlock(list->locker);
		return 0;
	}
	temp->data = data;
	temp->next = NULL;
	temp->prev = NULL;

	if(NULL == p)
	{
		list->next = temp;
		temp->prev = list->next->prev;
	}else
	{
		list->next = temp;
		temp->next = p;
		p->prev = temp;
		temp->prev = list;
	}
	list->locker->unlock(list->locker);
	return 1;
}

/*
*�����������Ӵ����˫������ɾ��һ���ڵ㡣
*������    list ��Ҫɾ�����ݵ�˫������
*          data ɾ��������
*          eq   ���û��ṩ�Ķ�������������ȵ��жϺ���
*����ֵ��  0����ʾɾ��ʧ��
*          1����ʾɾ���ɹ�
*/
int delNode(dlist list, void* data,equal eq)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("���ܴӿ�����ɾ���ڵ㡣\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	if(NULL == data)
	{
		printf("����ɾ�������ݡ�\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	
	p = list->next;

	while(p)
	{
		temp = p;
		if(!eq(temp->data,data))
		{
			if(NULL != temp->prev)
			{
				temp->prev->next = temp->next;
			}
			else
			{
				list->next = temp->next;
			}
			if(NULL != temp->next)
			{
				temp->next->prev = temp->prev;
			}
			else
			{
				
			}
			p=p->next;
			free(temp->data);
			temp->data = NULL;
			free(temp);
			temp = NULL;
		}
		else
		{
			p = p->next;
		}
	}
	list->locker->unlock(list->locker);
	return 1;
}

/*
*��������������˫������
*����ֵ��  0����ʾ����ʧ��
*          1����ʾ���ٳɹ�
*/

void destroy(dlist list)
{
	node* p,*temp;
	p = list;
	
	while(p)
	{
		temp = p;
		p = p->next;
		free(temp->data);
		temp->data = NULL;
		free(temp);
		temp = NULL;
	}
	list->locker->destroy(list->locker);
}

/*
*�������������������ÿһ���ڵ㣬�����û��ṩ�ĺ���ָ����ʽڵ㡣
*������    list  ��Ҫ�������ݵ�˫������
*          visit ���ʺ���
*          ctx   �����Ļ����������з���ֵ�ķ��ʺ������Դ�ŷ���ֵ��
*                ����ִ�е�ǰ���������ִ�к�ķ���ֵ�Ļ���������
*                ͬ���������ں��������������߷���ֵ����չ
*/
void foreach(dlist list,func_ptr visit,void* ctx)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("���ܴӿ�����ɾ���ڵ㡣\n");
		list->locker->unlock(list->locker);
		return ;
	}
	if(NULL == visit)
	{
		printf("���������ڡ�\n");
		list->locker->unlock(list->locker);
		return ;
	}
	if(NULL == ctx)
	{
		//���ô����κ�������
	}
	else
	{
		//��������ת����������������Ĳ�����
	}
	
	p = list->next;

	while(p)
	{
		visit(p->data);
		p = p->next;	
	}
	printf("\n");
	list->locker->unlock(list->locker);
}

