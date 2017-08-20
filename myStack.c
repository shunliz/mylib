#include <stdio.h>
#include <malloc.h>

#include "myStack.h"


void init(Stack** stk){
	int i = 0;
	if(NULL == *stk){
		*stk = (Stack*)malloc(sizeof(Stack));
	}
	(*stk)->top=(*stk)->bottom = 0;
	
	for(i=0;i<MAXLEN;i++){
		(*stk)->data[i] = (void**)malloc(MAXLEN*sizeof(void*));
	}

}

void* pop(Stack* stk){
	if(stk->top >=0){
		return stk->data[stk->top-1];
	}else {
		return NULL;
	}
}

void push(Stack* stk,void* dat){
	if(stk == NULL){
		return;
	}
	if(stk->data == NULL){
		int i ;
		for(i=0;i<MAXLEN;i++){
			stk->data[i] = (void**)malloc(MAXLEN*sizeof(void*));
		}

	}
	if(stk->top<MAXLEN -1){
		stk->data[stk->top] = dat;
		stk->top ++;
	}

}
void destroy(Stack* stk){
	if(NULL !=stk){
		if(NULL != stk->data){
			int i;
			for(i=0;i<MAXLEN;i++){
				if(NULL != stk->data[i]){
					free(stk->data[i]);
					stk->data[i] = NULL;
				}
			}
		}
	}
}
