/*************************************************************
*	name    : circlelist.h
*	anthor 	: rack
*	date   	: 2017.10.16 9:48 PM
*	mail   	: 1740234864@qq.com
*	function: circlelist 循环线性表
**************************************************************/

/********************************************************************
 *定义域
*********************************************************************/

#ifndef _CIRCULARLIST_H
#define _CIRCULARLIST_H

/*头文件*/
#include <stdio.h>
#include <stdlib.h>

/*定义*/
#define LIST_INIT_SIZE 100									   //初始分配量
#define LISTINCREMENT  10                      //分配增量

/*函数状态码*/
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

/*typedef类型*/
typedef int Status ;
typedef int Elemtype ;

/*structure*/
typedef struct CircleNote
{
	Elemtype data ;                                             //存储空间基址
	struct CircleNote *next ;
}CircleNote , *CircleList ;

/*函数表示*/
Status InitList(CircleList *L);                                 //初始化循环链表
Status DestroyList(CircleList *L);                              //销毁循环链表
Status ClearList(CircleList *L);                                //清空循环链表
Status ListEmpty(CircleList *L);                                //判断是否为空
Status ListLength(CircleList *L);                               //得到线性表长度
Status GetElem(CircleList *L , int i , Elemtype *e);            //得到线性表元素
Staus Compare(Elemtype e1 , Elemtype e2);
Status LocateList(CircleList *L , Elemtype e , Status (*compare)(Elemtype , Elemtype) );
Status PriorElem(CircleList L , Elemtype cur_e , Elemtype *pur_e);
Status NextElem(CircleList L , Elemtype cur_e , Elemtype *next_e);

#endif
