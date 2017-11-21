/********************************************************************
 *	@program name : NumberSystemConversion.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.4
 *	@function     : 栈实现的数制转换，十进制转换为其他进制
 *	@type         : source file
*********************************************************************/

/********************************************************************
*基本操作
*InitStack  初始化栈
*Push       插入元素 进栈
*Pop        删除元素 退栈
*Conversion 数制转换
*数制转换方法：
*设n为需要转换的进制,x为转换的进制
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "NumberSystemConversion.h"

/********************************************************************
 *函数的实现
*********************************************************************/
Status ClearStack(SqStack *S)
{
	S->top = S->base ;
	return OK ;
}

Status InitStack(SqStack *S)
{
	/*初始化栈,构造空栈*/
	S->base = (Elemtype *)malloc(STACK_INIT_SIZE*               //分配内存
					sizeof(Elemtype));
	if(!S->base) exit(OVERFLOW)   ;                             //分配失败
	S->top = S->base              ;                             //初始化栈基指针和栈顶指针
	S->stacksize = STACK_INIT_SIZE;                             //初始化栈长度
	return OK                     ;
}

Status Push(SqStack *S , Elemtype e)
{
	/*插入元素*/
	if((S->top-S->base)>=S->stacksize)                                  //判断栈满.如果栈满，则追加存储空间
	{
		S->base = (Elemtype *)realloc(S->base ,
		(STACK_INCREMENT+S->stacksize)*sizeof(Elemtype));   //追加存储空间
		if(!S->base) exit(OVERFLOW)                     ;   //追加存储空间分配失败
		S->top = S->base + S->stacksize                 ;
		S->stacksize += STACK_INCREMENT                 ;   //增加存储空间
	}
	*S->top++ = e                                           ;   //将增加的元素赋值S->base
	return OK                                               ;
}

Status Pop(SqStack *S , Elemtype *e)
{
	/*删除元素*/
	/*判断栈顶指针是否指向0，也就是栈中是否还有元素*/
	if(S->top == S->base) return ERROR                      ;   //栈中没有元素
	*e = *--S->top                                           ;   //将需要删除的元素赋值给e，由e传出
	return OK                                               ;
}

Status DestroyStack(SqStack *S)
{
	if(S->top == S->base) return ERROR ;
	free(S->base);
	S->top = NULL ;
	S->base = NULL ;
	return OK ;
}

Status EmptyStack(SqStack *S)
{
	if(S->top == S->base) return TRUE ;
	else return FALSE ;
	return OK ;
}
void Conversion(SqStack *S , Elemtype n , Elemtype x)
{
	/*数制转换*/
	Elemtype e ;                                                   //保存数制转换的值
	/*数制转换是倒着数的*/
	while(n!=0)
	{  //入栈，计算
		e = n%x ;                                                    //先从余数开始
		Push(S , e)      ;                                     //将转换的数压入栈
		n /= x           ;                                  //再整除，与平常算数相反
	}


	/*计算完后需要释放栈*/
	while(!EmptyStack(S))                                          //如果栈不空
	{
		Pop(S , &e)      ;                                  //退栈，输出
		printf("%d", e)  ;                                  //栈是用来存放正在计算的数据，计算完后需要释放栈
	}
}
