/********************************************************************
 *	@program name : EvaluateExpression.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.11
 *	@function     : 表达式求值
 *	@type         : header file
*********************************************************************/

/********************************************************************
*基本操作
*InitStackChar 初始化运算符栈
×InitStackFloat初始化运算数栈
*GetTopChar   得到运算符栈顶元素
*GetTopFloat  得到运算数栈顶元素
*PushChar     把字符压栈
*PushFloat    把数值压栈
*PopChar      把字符退栈
*PopFloat     把数值退栈
*Operate(a,theta,b) 根据theta对a和b进行'+' 、'-' 、'*' 、'/' 、'^'操作
*In(Test,*TestOp) 若Test为运算符则返回true，否则返回false
*ReturnOpOrd(op,*TestOp) 若Test为运算符，则返回此运算符在数组中的下标
*precede(Aop,Bop) 根据运算符优先级表返回Aop与Bop之间的优先级
*EvaluateExpression(*MyExpression) 用算符优先法对算术表达式求值
*********************************************************************/
/********************************************************************
 *定义域
*********************************************************************/
#ifndef _EVALUATEEXPRESSION_H
#define _EVALUATEEXPRESSION_H

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
//#define STACK_INCREMENT 10					                              //存储空间的分配增量
#define STACK_INIT_SIZE 100                                         //存储空间的初始分配量,一般不会满栈
#define OPSETSIZE       7                                           //优先级集合最大值

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status   ;

/********************************************************************
 *结构体
********************************************************************/
typedef struct
{
  char *base ;
  char *top  ;
  int stacksize ;
}StackChar;  //运算符栈

typedef struct
{
  float *base ;
  float *top ;
  int stacksize ;
}StackFloat;  //运算数栈

/********************************************************************
 *全局变量
********************************************************************/
unsigned char Prior[7][7] = {
      // 运算符间的优先关系
  	  '>','>','<','<','<','>','>',
	    '>','>','<','<','<','>','>',
	    '>','>','>','>','<','>','>',
	    '>','>','>','>','<','>','>',
	    '<','<','<','<','<','=',' ',
	    '>','>','>','>',' ','>','>',
	    '<','<','<','<','<',' ','='
};
char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};     //运算符选择

/********************************************************************
 *函数原型
********************************************************************/
void InitStackChar(StackChar *S);              //构造运算符栈
void InitStackFloat(StackFloat *S);            //构造运算数栈
char GetTopChar(StackChar *S)；                //返回运算符栈顶元素
char GetTopFloat(StackFloat *S);               //返回运算数栈顶元素
void PushChar(StackChar *S , char e);          //运算符入栈
void PushFloat(StackFloat *S , char e);        //运算数入栈
void PopChar(StackChar *S , char *e);          //运算符出栈
void PopFloat(StackFloat *S , char *e);        //运算数出栈
char EvaluateExpression(char *MyExpression);   //表达式求值函数
Status ReturnOpOrd(char Op , char TestOp);       //返回Aop与Bop的优先
float Operate(float a , char theta , float b); //根据theta对a和b进行'+' 、'-' 、'*' 、'/' 、'^'操作
Status In(char Test , char *TestOp);           //若Test为运算符则返回true，否则返回false
char precede(char Aop,char Bop);               //根据运算符优先级表返回Aop与Bop之间的优先级
int atof(char *snum);                          //将字符串转换为浮点数a代表字符串,f代表浮点数

#endif
