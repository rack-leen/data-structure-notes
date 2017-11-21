/********************************************************************
 *	@program name : LinkedQueue.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.21
 *	@function     : 单链队列
 *	@type         : header file
*********************************************************************/

/********************************************************************
*基本操作
*InitQueue    初始化队列
*DestroyQueue 销毁队列
*ClearQueue   清空队列
*EmptyQueue   判断队列是否为空
*LengthQueue  队列长度
*GetHead      得到队头元素
*EnQueue      插入队尾元素
*DeQueue      删除对头元素
*实现原理：
*
*********************************************************************/
/********************************************************************
 *定义域
*********************************************************************/
#ifndef _LINKEDQUEUE_H
#define _LINKEDQUEUE_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************************************************
 *定义区
*********************************************************************/
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status ;
typedef int QElemType ;

/********************************************************************
 *队列结构体
*********************************************************************/
typedef struct QNode
{
  //表示一个节点
  QElemType data ;
  struct QNode *next ;
}QNode , *QNodePtr;

typedef struct
{
  //表示整个链表
  QNodePtr *front ; //队头指针
  QNodePtr *rear ; //队尾指针
}LinkedQueue;

/********************************************************************
 *函数表示
*********************************************************************/
Status InitQueue(LinkedQueue *Q);                                   //初始化队列
Status DestroyQueue(LinkedQueue *Q);                                //销毁队列
Status ClearQueue(LinkedQueue *Q);                                  //清空队列
Status EmptyQueue(LinkedQueue *Q);                                  //判断队列是否为空
Status LengthQueue(LinkedQueue Q);                                  //队列长度
Status GetHead(LinkedQueue  Q , QElemType *e);                      //得到对头元素
Status EnQueue(LinkedQueue *Q , QElemType  e);                      //插入新的队尾元素
Status DeQueue(LinkedQueue *Q , QElemType *e);                      //删除队头元素

#endif
