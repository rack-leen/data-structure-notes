/********************************************************************
 *	@program name : SqQueue.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.24
 *	@function     : 循环队列
 *	@type         : header file
*********************************************************************/

/********************************************************************
*基本操作
*InitSqQueue    初始化队列
*DestroySqQueue 销毁队列
*ClearSqQueue   清空队列
*EmptySqQueue   判断队列是否为空
*LengthSqQueue  队列长度
*GetHead        得到队头元素
*EnSqQueue      插入队尾元素
*DeSqQueue      删除对头元素
*SqQueueTraverse遍历元素
*实现原理：
*
*********************************************************************/

/********************************************************************
 *定义域
*********************************************************************/
#ifndef _SQQUEUE_H
#define _SQQUEUE_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>      //提供realloc malloc exit函数原型

/********************************************************************
 *定义区
*********************************************************************/
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define MAXQSIZE        100 //最大队列长度

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status ;
typedef int SqElemType ;

/********************************************************************
 *结构体
*********************************************************************/
typedef struct
{
  SqElemType *base ;      //初始化动态分配空间
  int front ;
  int rear ;
}SqQueue;

/********************************************************************
 *函数表示
*********************************************************************/
Status InitSqQueue(SqQueue *Q);  //初始化循环队列
Status DestroySqQueue(SqQueue *Q); //销毁循环队列
Status EmptySqQueue(SqQueue *Q); //判断循环队列是否为空
Status ClearSqQueue(SqQueue *Q); //清空循环队列
Status GetHead(SqQueue Q , SqElemType *e); //获得循环队列队头元素
Status LengthSqQueue(SqQueue Q);   //获得循环队列长度
Status EnSqQueue(SqQueue *Q , SqElemType e); //元素e入队
Status DeSqQueue(SqQueue *Q , SqElemType *e); //元素e出队
Status SqQueueTraverse(SqQueue *Q , void(visit)(SqElemType)); //遍历队列

#endif
