/********************************************************************
 *	@program name : SqQueue.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.24
 *	@function     : 循环队列
 *	@type         : source file
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
 *头文件
*********************************************************************/
#include "SqQueue.h"

/********************************************************************
 *函数实现
*********************************************************************/
Status InitSqQueue(SqQueue *Q)
{
  //初始化循环队列
  (*Q).base = (SqElemType *)malloc(szieof(SqElemType)); //分配存储空间
  if(!(*Q).base) exit(OVERFLOW);      //存储空间分配失败
  (*Q).front = (*Q).rear = 0 ;           //队头队尾指针置0
  return OK ;
}

Status DestroySqQueue(SqQueue *Q)
{
  //销毁循环队列
  if((*Q).base)
    free((*Q).base);   //将存储空间释放
  (*Q).base = NULL ;  //存储空间为空
  (*Q).front = (*Q).rear = 0 ;
  return OK ;
}

Status EmptySqQueue(SqQueue Q)
{
  //判断循环队列是否为空
  if(Q.front == Q.rear)
    return TRUE  ;
  else
    return FALSE ;
}

Status ClearSqQueue(SqQueue *Q)
{
  //清空循环队列
  (*Q).front = (*Q).rear = 0 ;
}

Status GetHead(SqQueue Q , SqElemType *e)
{
  //获得循环队列队头
  if(Q.front == Q.rear)
    return ERROR ;
  *e = Q.base[Q.front];   //队列是存放在分配的存储空间base中，Q.front是存储空间中的队头
  return OK ;
}

Status LengthSqQueue(SqQueue Q)
{
  //返回循环队列长度
  return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE ;
}

Status EnSqQueue(SqQueue *Q , SqElemType e)
{
  //元素入队
  if(((*Q).rear+1)%MAXQSIZE == (*Q).front)    //循环队列中，Q.rear=Q.不能判断空，(Q.rear+1)%MAXQSIZE=0，Q.rear+1表示少用一个存储空间
      return ERROR; //上面的式子表示队列满，尾指针+1就达到最大存储，再与最大值求余为0，表示与队头重合
  (*Q).base[(*Q).rear] = e ; //从队尾插入
  (*Q).rear = ((*Q).rear+1)%MAXQSIZE ; //只要Q.rear%MAXQSIZE不等于0，则余数就是Q.rear本身,相当于Q.rear++
  return OK ;
}

Status DeSqQueue(SqQueue *Q  , SqElemType *e)
{
  //元素出队
  if((*Q).front == (*Q).rear) return ERROR ;  //队列为空
  *e = (*Q).base[(*Q).front];  //从队头删除
  (*Q).front = ((*Q).front+1)%MAXQSIZE ; //当Q.front等于最大值时，归0，不等于是，Q.front++
  return OK ;
}

Status SqQueueTraverse(SqQueue Q , void(visit)(SqElemType))
{
  //遍历队列
  int i = Q.front ;
  while (i!=Q.rear)
  {
    visit(Q.base[i]);  //打印函数
    i = (i+1)%MAXQSIZE ; //相当于i++,但是等于最大值时，归0
  }
  return OK ;
}

void visit(SqElemType e)
{
  //打印队列
  printf("%d", e);
}
