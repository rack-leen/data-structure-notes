/*********************************************************************
*	@program name: stack  
*	@author name : rack
*	@mail	     : 1740234864@qq.com
*	@last date   : 2017.11.2
*	@function    : 栈的顺序存储实现
**********************************************************************/

/*********************************************************************
*栈的基本操作
*InitStack    构造空栈
*DestroyStack 销毁栈
*ClearStack   栈置空
*EmptyStack   判断栈空
*Push         插入元素 进栈
*Pop          删除元素 退栈
*TraverseStack遍历栈
**********************************************************************/

/*********************************************************************
*头文件 
**********************************************************************/
#include <string.h>
#include "SqStack.h"


/*********************************************************************
*函数实现
**********************************************************************/

Status InitStack(SqStack *S)        
{
	/*构造一个空栈*/
	S->base = (SElemtype*)malloc(STACK_INIT_SIZE*sizeof(SElemtype));//动态分配内存
	if(!S->base)   exit(OVERFLOW);                                  //存储分配失败
	S->top       = S->base;                                         //初始状态，栈为空
	S->stacksize = STACK_INIT_SIZE;                                 //初始分配量
	return OK;
}

Status ClearStack(SqStack *S)
{
	/*清空栈*/
	S->top = S->base;
	return OK       ;
}

Status DestroyStack(SqStack *S)
{
	/*销毁栈*/
	free(S->base);
	S->base      = NULL;
	S->top       = NULL;
	S->stacksize = 0   ;
	return OK          ;
}

Status EmptyStack(SqStack *S)
{
	/*判断是否为空栈*/
	if(S->top == S->base)
		return TRUE ;
	else
		return FALSE;
}

Status GetTop(SqStack *S , SElemtype *e)
{
	/*得到栈顶元素*/
	if(S->top == S->base) return ERROR;                            //如果栈顶元素等于栈基元素，则为空栈，没有栈顶元素
	e = *(S->top-1)                   ;                            //栈不空，返回栈顶元素S->top-1(S->top是栈顶指针，减一位才是栈顶元素)
	return OK                         ;
}

Status Push(SqStack *S , SElemtype e)                  
{
	/*插入元素*/
	if(S->top - S->base >= S->stacksize)                           //判断是否栈满，因为前面已经判断了是否空栈。栈满，追加存储空间
	{
		S->base = (SElemtype*)realloc(S->base ,
		     (S->stacksize+STACK_INCREMENT)*sizeof(SElemtype));//追加存储空间
		if(!S->base) exit(OVERFLOW);                           //存储分配失败
		S->top        = S->base + S->stacksize;                //栈顶值等于栈基加上栈存储空间值
		S->stacksize += STACK_INCREMENT        ;               //追加的存储空间增量      
	}
	*S->top++ = e;                                                 //将插入的各个元素赋值给栈顶，栈顶++
	return OK ;
}

Status Pop(SqStack *S , SElemtype *e)
{	
	/*删除元素*/ 
	if(S->top == S->base) return ERROR;			       //判断是否空栈
	e = * --S->top;                                                //栈顶元素先减再赋值
	return OK;
}


Status TraverseStack(SqStack *S , Status (*visit)(SElemtype))
{
	/*遍历栈*/
	SElemtype *b = S->base;                                        //不能直接用S->base，不能改变原来的栈结构
	SElemtype *t = S->top ;                                        //use *t replace S->top
	while(t > b)
		visit(*b++);
	printf("\n");
	return OK ;
}

Status visit(SElemtype c)
{	/*输出遍历结果*/
	printf("%d\n",c);
	return OK ;
}
