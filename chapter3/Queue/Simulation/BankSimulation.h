/********************************************************************
 *	@program name : BankSimulation.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.24
 *	@function     : 银行业务模拟 ， 离散事件模拟
 *	@type         : header file
*********************************************************************/

/********************************************************************
*基本操作
*LinkQueue.h        引用队列结构体和指针
*LinkQueue.c        引用队列函数实现
*BankSimulation     银行模拟函数
*OpenForDay         银行开门
*MoreEvent          判断事件是否为空
*EventDrived        事件驱动
*CustomerArrived    客户到达
*CustomerDeparture  客户离开
*Invalid            事件类型错误
*CloseForDay        银行关门
*cmp                比较两个事件发生的先后次序
*Random             生成随机数，当前业务所务时间和下一个客户达到间隔的时间
*OrderInsert        插入事件
*Minimum            长度最短队列的序号
*Show               显示当前列客户排队情况
*void BankSimulation1 //第二种银行模拟算法
*实现原理：
*建立两个队列，一个是处理客户业务，一个是离开银行
*********************************************************************/


/********************************************************************
 *定义域
*********************************************************************/
#ifndef _BANKSIMULATION_H
#define _BANKSIMULATION_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
#define SleepTime       1   //休眠时间
#define DurationTime    20  //办理业务持续时间
#define IntervalTime    10  //下一个客户到来时间间隔


/********************************************************************
 *
 *单链表
 *
*********************************************************************/
/********************************************************************
 *单链表自定义类型
*********************************************************************/
typedef int ElemType ;
/********************************************************************
 *单链表结构体
*********************************************************************/
typedef struct Lnode{
  ElemType data ;
  struct Lnode *next ;
}Lnode , *LinkList ;

/********************************************************************
 *单链表函数表示
*********************************************************************/
Status InitList(LinkList *L);                                         //初始化链表
void DestroyList(LinkList *L);                                        //销毁线性表
void ClearList(LinkList L);                                          //置空线性表
Status ListEmpty(LinkList L);                                        //判断线性表是否为空
Status ListLength(LinkList L);                                       //获取线性表长度
Status GetElem(LinkList L , int i , ElemType *e);                    //得到线性表第i个元素
Status LocateElem(LinkList L , ElemType e , Status(compare)(ElemType,ElemType));//返回单链表中第一个 与e满足compare关系的元素序列
Status compare(ElemType e , ElemType data);                          //比较大小
Status PriorElem(LinkList L , ElemType cur_e ,ElemType *pur_e);      //求线性表的前驱
Status NextElem(LinkList L , ElemType cur_e , ElemType * next_e);    //求线性表后驱
Status InsertList(LinkList L , int i ,ElemType e);                    //插入数据
Status DeleteList(LinkList L , int i ,ElemType *e);                   //删除数据
Status ListTraverse(LinkList *L);                                     //遍历线性表
void visit(ElemType e);                                               //打印遍历结果
Status CreateList_HL(LinkList  *L , int n);                           //头插法
Status CreateList_TL(LinkList  *L , int n);                           //尾插法


/********************************************************************
 *
 *队列
 *
*********************************************************************/

/********************************************************************
 *队列自定义类型
*********************************************************************/
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
  QNodePtr front ; //队头指针
  QNodePtr rear ; //队尾指针
}LinkedQueue;

/********************************************************************
 *队列函数表示
*********************************************************************/
Status InitQueue(LinkedQueue *Q);                                   //初始化队列
Status DestroyQueue(LinkedQueue *Q);                                //销毁队列
Status ClearQueue(LinkedQueue *Q);                                  //清空队列
Status EmptyQueue(LinkedQueue *Q);                                  //判断队列是否为空
Status LengthQueue(LinkedQueue Q);                                  //队列长度
Status GetHead(LinkedQueue  *Q , QElemType *e);                      //得到对头元素
Status EnQueue(LinkedQueue *Q , QElemType  e);                      //插入新的队尾元素
Status DeQueue(LinkedQueue *Q , QElemType *e);                      //删除队头元素
Status QueueTraverse(LinkedQueue Q , void (visit)(QElemType));      //遍历队列


/********************************************************************
 *
 *银行业务模拟
 *
*********************************************************************/

/********************************************************************
 *银行业务模拟枚举事件类型
*********************************************************************/
typedef enum                                                       //枚举事件类型
{
   Arrive,Leave_1,Leave_2,Leave_3,Leave_4
}EventType;                                                         //事件类型，，0代表到达事件，1-4代表四个窗口离开事件

/********************************************************************
 *银行业务模拟结构体
*********************************************************************/
//事件结构体
typedef struct
(
    int OccurTime ;                                                 //事件发生时刻
    EventType NType ;                                               //事件类型
)Event;

typedef Event LElemType ;                                           //事件元素

//建立事件链表元素的节点
typedef struct LNode
{
  LElemType data ;                                                  //事件链表元素中的数据
  struct LNode *next ;
}LNode;                                                             //事件链表元素的节点建立

typedef LNode *LinkList ;                                           //
typedef LinkList EventList ;                                        //事件链表类型，定义为有序链表

//队列数据元素类型
typedef struct
{
  int ArrivedTime ;                                                 //客户到达时间
  int Duration ;                                                    //办理事件所需时间
  int Count ;                                                       //客户记录
}QElemType;                                                         //队列的数据元素类型


/********************************************************************
 *银行业务模拟全局变量
*********************************************************************/
Event en ;                                                          //事件
EventList ev ;                                                      //事件表
LinkQueue q[5];                                                     //4个客户队列
QElemType customer;                                                 //客户记录
int TotalTime , CustomerNum ;                                       //累计客户逗留时间和客户数
int CloseTime = 480 ;                                               //银行关门时间

/********************************************************************
 *银行业务模拟函数表示
*********************************************************************/
void BankSimulation();                                              //银行模拟函数
void OpenForDay();                                                  //银行开门，初始化变量
void MoreEvent();                                                   //判断事件表是否为空
void EventDrived(char *event);                                      //事件驱动，获取当前事件类型
void CustomerArrived();                                             //处理客户到达时间
void CustomerDeparture();                                           //处理客户离开时间
void Invalid();                                                     //事件类型错误
void CloseForDay();                                                 //银行关门
void cmp(Event a , Event b);                                        //比较两个事件发生的先后次序
void Random(int *durtime , int *intertime);                         //生成随机数，当前办理业务所需时间和下一个客户达到间隔的时间
Status OrderInsert(EventList ev, Event en, int (cmp)(Event,Event)); //将事件插入事件表的正确位置
int Minimum();                                                      //求长度最短队列的序号
void Show();                                                        //显示当前队列客户排队情况
//void BankSimulation1(); //第二种银行模拟算法

#endif
