/********************************************************************
 *	@program name : LinkedQueue.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.21
 *	@function     : 单链队列
 *	@type         : source file
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
*QueueTraverse遍历元素
*实现原理：
*
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "LinkedQueue.h"

/********************************************************************
 *函数实现
*********************************************************************/
Status InitQueue(LinkedQueue *Q)
{
  //初始化队列
  (*Q).front = (*Q).rear = (QNodePtr)malloc(sizeof(QNode));            //为队头队尾分配存储空间
  if(!(*Q).front) exit(OVERFLOW);                                    //队头空间分配失败
  (*Q).front->next = NULL ;                                          //队头指针的下一个为空，表示只有队头
 // (*Q)->front = (*Q)->rear ;                                           //尾指针复位，避免成为野指针
  return OK ;
}

Status DestroyQueue(LinkedQueue *Q)
{
  //销毁队列,队头与队尾一起被释放
  while(!(*Q).front)
  { //先将队头指针志向下一个成员，留出队头
    (*Q).rear = (*Q).front->next ;                //Q->rear指向离队首最近的节点
    free(Q->front);                             //释放队首的节点所在内存单元
    Q->rear = Q->front ;                      //将Q->rear复位会首结点，如果不执行这步，free()后Q->rear也将不复存在并成为野指针
                                                  //现在Q->front和Q->rear都指向离原来队首最近的节点.倘若执行Destoryqueue()前节点的个数>=2,
                                                  //则第一次执行次循环后仍满足循环条件继续循环,最终整个队列的内存全部被释放,队列被销毁.
  }                 //只要有队头元素就执行销毁动作
  return OK ;
}

Status ClearQueue(LinkedQueue *Q)
{
  //清空队列，留下队头
  (*Q).rear = (*Q).front->next ;//队头指针指向下一个，留出队头
  while((*Q).rear)              //用队尾循环，保留队头
  { //队尾指针指向下一个成员，队尾元素留下，等待释放
    (*Q).front->next = (*Q).rear->next ;   //与销毁队列方式相同，用front的下一个元素,指向队尾的下一个，排除队首，为了保留队列。（留出队尾，为了释放队尾）
    free((*Q).rear);                     //释放队尾指针
    (*Q).rear = (*Q).front->next ;
  }
  (*Q).rear = (*Q).front ;      //将Q->rear复位会首结点，如果不执行这步，free()后Q->rear也将不复存在并成为野指针，将留下的队头指针复位
  return OK ;
}
//1、free(Q->front);  // 你把头空节点也删了！清空的话保留头空节点，下次就不用重新建立队列
//2、习惯上：销毁的话是把头空节点也释放掉，下次使用必须重新建立。
//3、while(Q->front->next->next)
//你的清空函数如果连续运行两次，程序就会break！if(Q->front->next==NULL) ???

Status EmptyQueue(LinkedQueue *Q)
{
  //判断队列是否为空
  if(Q->front == Q->rear)   //队头等于队尾
    return TRUE ;
  else
    return FALSE ;
}

Status LengthQueue(LinkedQueue Q)
{
  //返回队列长度
  int lengh = 0 ;   //初始化
  QNodePtr p = Q.front ;
  while(p!=Q.rear) //队列不为空
  {
    lengh ++ ;   //长度加
    p = p->next ; //继续下一个
  }
  return lengh ;  //返回长度
}

Status GetHead(LinkedQueue *Q , QElemType *e)
{
  //获得队首元素
  QNodePtr p ;
  if((*Q).front == (*Q).rear) return ERROR ; //队列为空
  p = (*Q).front->next ;
  *e = p->data ;  //获得队首元素
  return OK ;
}

Status EnQueue(LinkedQueue *Q , QElemType e)
{
  //插入元素
  QNodePtr p ;
  p = (QNodePtr)malloc(sizeof(QNode));
  if(!p)  //分配失败
    exit(OVERFLOW);
  p->data = e ;   //将插入的元素放入p的数据区
  p->next = NULL ; //由于是在队尾插入，所以p的下一个为空
  //修复逻辑链
  (*Q).rear->next = p ; //插入的元素还没有进入队列时，原来的队尾的下一个指向p
  (*Q).rear = p ; //插入元素成为队列一部分后，队尾指针就指向p
  return OK ;
}

Status DeQueue(LinkedQueue *Q , QElemType *e)
{
  //删除元素
  QNodePtr p ;
  if((*Q).front == (*Q).rear)  return ERROR ; //队列为空
  (*Q).front->next = p ; //表示没有删除时的关系，front的下一个就是P
  *e = p->data ; //删除p的数据
  (*Q).front->next = p->next ; //删除元素后的逻辑关系

  if((*Q).rear == p) //删除的是队尾元素，表示队列已经删除完了，因为队列是队首删除，队尾插入
      (*Q).rear = (*Q).front ; //表示已经是空队列
  free(p); //将被删除的元素所占空间释放
  return OK ;
}

Status QueueTraverse(LinkedQueue Q , void (visit)(QElemType))
{
  //遍历队列
  QNodePtr p ;
  p = Q.front->next ; //p为队首元素
  while(p)
  {
    visit(p->data);  //打印遍历的元素
    p=p->next ; //继续遍历
  }
  return OK ;
}

void (visit)(QElemType e)
{
  printf("%d\n", e);    //打印遍历的元素
}
