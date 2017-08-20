#ifndef MYSTACK_H
#define MYSTACK_H


#if defined __cplusplus
extern "C" {
#endif

#define MAXLEN 200

	typedef struct stack{
		int top;
		int bottom;
		void* data[MAXLEN];
	}Stack;

	void init(Stack** stk);
	void* pop(Stack* stk);
	void push(Stack* stk,void* dat);
	void destroy(Stack* stk);



#if defined __cplusplus
}
#endif

#endif