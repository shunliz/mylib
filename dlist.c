/*******************************************************************************
*Copyright@2009 of 周顺利. 
*All right reserved.
*
*文件名称 ： dlist.c
*功能描述：  双向链表数据实现文件。实现双向链表的节点定义和相关操作函数。
*作者：      周顺利
*日期：      2009-8-4
*
*修改记录：
*修改人           修改日期                   修改描述
*
********************************************************************************/

#include "ctype.h"
#include "dlist.h"
#include "Locker.h"
//#include "log.h"

/*
*双向链表数据节点结构定义。
*属性：data 数据指针，void*范型指针，实现链表的通用性。
*      prev 前向指针
*      next 后项指针
*/

struct _node
{
	Locker* locker;
	void* data;
	struct _node* prev;
	struct _node* next;
};

/*
*功能描述：双向链表初始化函数。初始化一个头节点，
*          前向和后向以及节点数据指针都为空。
*参数：    list 需要初始化的双向链表
*返回值：  0，表示内存不足，初始化失败。
*          1，表示初始化成功。
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
*功能描述：向传入的双向链表增加一个节点。
*参数：    list 需要增加数据的双向链表
*          data 增加的数据
*返回值：  0，表示增加失败
*          1，表示增加成功
*/
int add(dlist list, void* data)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("请先初始化链表。\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	if(NULL == data)
	{
		printf("不能增加空数据到链表。\n");
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
*功能描述：从传入的双向链表删除一个节点。
*参数：    list 需要删除数据的双向链表
*          data 删除的数据
*          eq   由用户提供的定义两个数据相等的判断函数
*返回值：  0，表示删除失败
*          1，表示删除成功
*/
int delNode(dlist list, void* data,equal eq)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("不能从空链表删除节点。\n");
		list->locker->unlock(list->locker);
		return 0;
	}
	if(NULL == data)
	{
		printf("不能删除空数据。\n");
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
*功能描述：销毁双向链表
*返回值：  0，表示销毁失败
*          1，表示销毁成功
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
*功能描述：遍历链表的每一个节点，调用用户提供的函数指针访问节点。
*参数：    list  需要访问数据的双向链表
*          visit 访问函数
*          ctx   上下文环境，对于有返回值的访问函数可以存放返回值。
*                函数执行的前传入参数和执行后的返回值的环境变量，
*                同样可以用于后续函数参数或者返回值的扩展
*/
void foreach(dlist list,func_ptr visit,void* ctx)
{
	node* p,*temp;
	list->locker->lock(list->locker);
	if(NULL == list)
	{
		printf("不能从空链表删除节点。\n");
		list->locker->unlock(list->locker);
		return ;
	}
	if(NULL == visit)
	{
		printf("函数不存在。\n");
		list->locker->unlock(list->locker);
		return ;
	}
	if(NULL == ctx)
	{
		//不用传递任何上下文
	}
	else
	{
		//做上下文转化，返回相关上下文操作。
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

