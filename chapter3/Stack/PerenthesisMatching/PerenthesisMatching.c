/*****************************************************************************
*	@program    name : PerenthesisMatching.c
*	@author     name : rack
*	@my         mail : 1740234864@qq.com
*	@last       date : 2017.11.5
*	@fuction         : 括号匹配，必须是成对括号才匹配
*	@type            : source file
******************************************************************************/


/*****************************************************************************
*基本操作
*InitStack  初始化栈
*Push       插入元素，进栈
*Pop        删除元素，退栈
*Conversion 数值转换
*括号匹配方法：
*
******************************************************************************/

/*****************************************************************************
*头文件
******************************************************************************/
#include <stdio.h>
#include "PerenthesisMatching.h"
/*****************************************************************************
*函数的实现
******************************************************************************/
Status InitStack(SqStack *S)
{
	/*初始化栈,并构造一个空栈*/

	S->base = (Elemtype *)malloc(STACK_INIT_SIZE*sizeof(Elemtype)) ;     //动态分配空间
	if(!S->base)                                                         //S栈分配失败
		exit(OVERFLOW)                                               ;
	S->top       = NULL                                            ;
	S->base      = NULL                                            ;
	S->stacksize = 0                                               ;
	return OK                                                      ;
}

Status Push(SqStack *S , Elemtype e)
{
	/*栈的插入元素*/
	if(S->top-S->base >= S->stacksize)                            //栈满
	{
		S->base = (Elemtype *)realloc(S->base ,                     //追加内存
		     (STACK_INCREMENT + S->stacksize)*sizeof(Elemtype));
		if(!S->base) exit(OVERFLOW)                            ;    //追加内存失败
		S->top = S->base + S->stacksize                        ;    //原有的内存
		S->top += STACK_INCREMENT                              ;    //追加的内存
	}
	*S->top++ = e                                            ;    //将e插入栈顶
	return OK                                                ;
}

Status Pop(SqStack *S , Elemtype *e)
{
	/*栈的删除元素*/
	if(S->top == S->base)  return ERROR                            ;    //栈为空
	/*如果不为空，删除*/
	*e = *--S->top                                                 ;    //删除元素
	return OK                                                      ;
}

Status GetTop(SqStack *S , Elemtype *e)
{
	/*获取元素*/
	if(S->top == S->base) return ERROR                             ;
	e = *(S->top - 1)                                              ;    //S->top为栈顶指针，不算元素
	return OK                                                      ;
}

Status Matching(SqStack *S , char *str)
{
	/*括号匹配算法:用选择结构*/
	int i=0 , flag = 0                                             ; //while循环的变量
	Elemtype e                                                     ;
	InitStack(S)                                                   ; //初始化栈
	while(str[i]!='\0')
	{
		switch(str[i])
		{
			case '(':
				Push(S , str[i])                       ; //将元素储存入栈
				break                                  ;
			case '[':
				Push(S , str[i])                       ;
				break                                  ;
			case ')':
				Pop(S , &e)                            ; //对比时出栈
				if(e != '(')                             //e为指针，可以看做是数组,e所代表的)不能与(匹配
					flag = 1                             ; //表示返回错误
				break                                  ;
			case ']':
				Pop(S , &e)	                           ;
				if(e != '[')
					flag = 1 ;
				break                                  ;
			default:
				break                                  ;
		}
		if(flag)                                     //flag=1表示匹配失败
			break;
		i++                                        ; //匹配完一个后再匹配下一个
	}
	if(!flag && (S->top != S->base))
		printf("括号匹配成功！\n");
	else
		printf("括号匹配失败!\n");
	return OK ;
}

/*****************************************************************************
*end
******************************************************************************/
