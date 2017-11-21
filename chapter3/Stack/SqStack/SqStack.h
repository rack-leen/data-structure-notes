/********************************************************************
*	program name : dlist.h
*	anthor  name : rack
*	mail address : 1740234864@qq.com
*	function     : 栈的顺序存储表示
*	last date    : 2017.10.21 22:59
*********************************************************************/
#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>

/********************************************************************
*基本定义
*********************************************************************/
#define OK                1 
#define ERROR             0
#define TRUE              1
#define FALSE             0
#define INFEASIBLE        -1
#define OVERFLOW          -2
#define STACK_INIT_SIZE   100                                        //存储空间初始分配量
#define STACK_INCREMENT   10                                         //存储空间分配增量

typedef int Status      ;
typedef int SElemtype   ;

typedef struct {
	SElemtype *base ;                                            //栈基指针，指向栈底
	SElemtype *top  ;                                            //栈顶指针，指向栈顶
	int stacksize   ;                                            //当前已分配的存储空间，以元素为单位
}SqStack;

/********************************************************************
*函数原型
*********************************************************************/
Status InitStack(SqStack *S)                                 ;       //初始化栈，并构造空栈，返回S
Status DestroyStack(SqStack *S)                              ;       //销毁栈，返回S
Status ClearStack(SqStack *S)                                ;       //栈置空，返回S
Status EmptyStack(SqStack *S)                                ;       //判断栈空，返回S
Status GetTop(SqStack *S , SElemtype *e)                     ;       //得到栈顶元素
Status Push(SqStack *S , SElemtype e)                        ;       //插入元素e
Status Pop(SqStack *S , SElemtype *e)                        ;       //删除元素e
Status TraverseStack(SqStack *S , Status (*visit)(SElemtype));       //遍历栈
Status visit(SElemtype c)                                    ;       //输出遍历结果

#endif
