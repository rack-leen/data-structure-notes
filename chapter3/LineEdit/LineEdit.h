/********************************************************************
 *	@program name : LineEdit.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.9
 *	@function     : 栈实现的行编辑
 *	@type         : header file
*********************************************************************/

/********************************************************************
*基本操作
*InitStack    初始化栈
*DestroyStack 销毁栈
*ClearStack   清空栈
*EmptyStack   判断栈是否为空
*LengthStack  返回栈长度
*GetTop       得到栈顶元素
*Push         插入元素 进栈
*Pop          删除元素 退栈
*LineEdit     行编辑实现函数
*TraveseStack 遍历栈
*行编辑实现方法：
*如果输入的既不是退格符，也不是退行符，则将该字符压入栈顶；如果是一个
*退格符，则删除前一个字符；如果是退行符，则将字符栈清空。
*********************************************************************/

/********************************************************************
 *定义域
*********************************************************************/
#ifndef _LineEdit_H
#define _LineEdit_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/********************************************************************
 *定义区
*********************************************************************/
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define STACK_INCREMENT 10					                                //存储空间的分配增量
#define STACK_INIT_SIZE 100                                         //存储空间的初始分配量

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status   ;
typedef char Elemtype ;

/********************************************************************
 *结构体
********************************************************************/
typedef struct {                                                   //构建数制转换栈的结构体
	Elemtype *base    ;                                              //栈基指针
	Elemtype *top     ;                                              //栈顶指针
	int stacksize;                                                   //栈长度
}SqStack;                                                          //栈类型

/********************************************************************
 *函数的表示
*********************************************************************/

Status InitStack(SqStack *S);                                      //初始化栈
Status DestroyStack(SqStack *S);                                   //销毁栈
Status ClearStack(SqStack *S);                                     //清空栈
//Status EmptyStack(SqStack *S);                                   //判断栈是否为空
//Status LengthStack(SqStack *S);                                  //判断长度
//Status GetTop(SqStack *S , Elemtype *e);                         //
Status Push(SqStack *S , Elemtype e);                              //插入元素，进栈
Status Pop(SqStack *S , Elemtype *e);                              //删除元素，退栈
void   LineEdit(SqStack *S);
//Status TraveseStack(SqStack *S , Status (*visit)(Elemtype e));   //遍历栈
//Status visit(Elemtype e);                                        //输出遍历结果

#endif
