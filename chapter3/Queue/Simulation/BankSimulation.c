/********************************************************************
 *	@program name : BankSimulation.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.25
 *	@function     : 银行业务模拟 ， 离散事件模拟
 *	@type         : source file
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
 *头文件
*********************************************************************/
#include "BankSimulation.h"


/********************************************************************
 *单链表函数实现
*********************************************************************/
/*初始化单链表表*/
Status InitList(LinkList *L)
{
  //构造空的单链表L
  (*L) = (LinkList)malloc(sizeof(LNode)); //为单链表元素分配内存
  if(!(*L))
    exit(OVERFLOW);
  (*L)->next = NULL ;
  return OK ;
}

//销毁所有节点
void DestroyList(LinkList *L)
{
  LinkList p = *L ;      //p指向当前单链表元素
  while(p)
  {
    p = (*L)->next ;   //现在p指向当前单链表元素的下一个
    free(*L);          //销毁当前单链表元素
    (*L) = p ;
  }
  return OK ;
}

//置空单链表
void ClearList(LinkList L)   //保留头节点
{
  LinkList pre , p ;
  //判断当前元素是否存在
  if(!L)
    return ERROR ;
  pre = L->next ;         //从头节点的下一个开始
  while(pre)
  {
    p = pre->next ;     //现在p指向头节点的下一个的下一个元素
    free(pre);          //释放当前元素
    pre = p ;
  }
  return OK ;
}

//判断单链表是否为空
Status ListEmpty(LinkList L)
{
  if(L!=NULL && L->next == NULL) //链表存在，链表为空
       return TRUE ;
  else
       return FALSE ;
}

//获取单链表长度
Status ListLength(LinkList L)
{
    LinkList p ;
    int i ;         //用来返回长度的

    if(L)        //链表存在
    {
      i = 0 ;
      p = L->next ; //从头节点的下一个，也就是链表首元素开始
      while(p)
      {
        i++ ;
        p = p->next ;  //遍历
      }
    }
    return i ;  //返回长度
}

//获取单链表第i个数据元素
Status GetElem(LinkList L , int i , ElemType *e)
{
  int j=1 ;   //计数器
  LinkList p = L->next ;  //从第一个链表元素开始寻找

  while(p&&j<i)  //p不为空，寻找的元素还没有到达i处
  {
    j++ ;      //计数
    p = p->next ; //下一个
  }
  if(!p || j>i)   //p为空，i不存在
    return ERROR ;

  *e = p->data ;   //用e返回
  return OK ;
}
//返回单链表中第一个 与e满足compare关系的元素序列
Status LocateElem(LinkList L , ElemType e , Status(compare)(ElemType,ElemType))
{
  int i ;
  LinkList p ;
  i = -1 ; //L不存在时返回-1
  if(L)
  {
    i = 0 ;
    p = L->next ;    //p指向头节点

    while(p)
    {
      i++ ;
      if(!compare(e , p->data))  //满足关系
        p = p->next ; //下一个
      else
        break ;
    }
  }
  return i ;
}

//比较大小
Status compare(ElemType e , ElemType data)
{
  return data>e ? TRUE : FALSE ;
}

//求单链表前驱
Status PriorElem(LinkList L ,ElemType cur_e , ElemType *pur_e)
{
  LinkList p , suc ;
  if(L)    //L单链表存在
  {
     p = L->next ; //L为头指针，L->next则为头元素
     if(p->data!=cur_e)//第一个节点没有前驱
     {
       while(p->next) //p节点有后继
       {
         suc = p->next ; //suc指向p的下一个
         if(suc->data==cur_e) //suc有前驱
         {
           *pur_e = p->data ; //p->data为cur_e前驱
           return OK ;
         }
         p = suc ;  //p->data被释放，p指向p的下一个
       }
     }
  }
  return ERROR ;
}

//求单链表的后继
Status NextElem(LinkList L , ElemType cur_e , ElemType *next_e)
{  //求后继，则有前驱
	LinkList p , suc ;
  if(L)
  {
    p=L->next ;
    while(p && p->next)   //p存在，p有后继
    {
      suc = p->next ;   //suc指向p后继
      while(suc&&p->data == cur_e) //suc存在，后继存在
      {
        *next_e = suc->data ; //找出后继
        return OK ;
      }
    }
  }
  return ERROR ;
}

//插入数据到线性表
Status InsertList(LinkList L , int i , ElemType e)
{
  LinkList p , s;  //s为增加的节点，e为节点中的元素
  int j ; //计数器

  p = L ; //指向头节点
  while(p && j < i-1) //p存在，寻找第i-1个节点 链表从1开始,j从0开始
  {
    p = p->next ;
    ++j ;
  }

  if(!p || j>i-1) return ERROR ; //插入位置不合理
  s = (LinkList)malloc(sizeof(LNode)); //分配新节点
  if(!s) exit(OVERFLOW);  //分配失败

  s->data = e ;
  s->next = p->next ;  //插入前，建立逻辑关系
  p->next = s ;   //插入后，修复逻辑关系

  return OK ;
}

//删除元素
Status DeleteList(LinkList L , int i , ElemType *e)
{
  LinkList p , q;
  int j ;
  p = L ; //p指向头节点
  j = 0 ;

  while(p->next && j < i-1) //寻找第i个节点,并令p指向其前驱
  {
    p = p->next ;  //下一个
    ++j ;  //计数
  }

  if(!(p->next) || j>i-1) return ERROR ; //删除位置不合理

  q = p->next ;  //原来的关系
  p->next = q->next ; //删除后的关系
  *e = q->data ;
  free(q);

  return OK ;
}

//遍历线性表
Status ListTraverse(LinkList L , void(visit)(ElemType))
{
  LinkList p ;
  if(!L)                //单链表不存在
    return ERROR ;
  else
    p = L->next ;     //单链表存在则就让p指向头节点

  while(p)
  {
    visit(p->data);   //输出遍历结果
    p = p->next ;    //下一个
  }

  return OK ;
}

void visit(ElemType e)
{
  //打印遍历结果
  printf("%d", e);
}

Status CreateList_HL(LinkList  *L , int n)   //头插法建立逆向单链表
{
    int i ;
    LinkList p ;
    ElemType tmp ;  //录入的数据

    *L = (LinkList)malloc(sizeof(LNode));
    if(!(*L))
      exit(OVERFLOW);
    (*L)->next = NULL ;           //生成带头节点的单链表

    for(i = 0 ; i<n ; ++i)
    {
      p = (LinkList)malloc(sizeof(LNode));  //生成新节点
      if(!p) exit(OVERFLOW);
      p->data = tmp ;
      p->next = (*L)->next ;  //插入前逻辑关系
      (*L)->next = p ; //插入后逻辑关系
    }
    return OK ;
}

Status CreateList_TL(LinkList  *L , int n)   //尾插法建立逆向单链表
{
    int i ;
    LinkList p , q ;
    ElemType tmp ;  //录入的数据

    *L = (LinkList)malloc(sizeof(LNode));
    if(!(*L))
      exit(OVERFLOW);
    (*L)->next = NULL ;           //生成带头节点的单链表

    for(i = 0 , q=*L; i<n ; ++i)
    {
      p = (LinkList)malloc(sizeof(LNode));  //生成新节点
      if(!p) exit(OVERFLOW);
      p->data = tmp ;
      q->next = p ;  //插入前逻辑关系
      q = q->next; //插入后逻辑关系
    }
    return OK ;
}

/********************************************************************
 *队列函数实现
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



/********************************************************************
 *银行业务模拟函数实现
*********************************************************************/
void BankSimulation()
{
  //银行模拟函数,统计一天内客户在银行逗留的平均时间
  char eventType ;  //事件类型

  OpenForDay();   //初始化
  while(MoreEvent())
  {
    EventDrived(&eventType); //事件驱动
    switch (eventType)
    {
      case 'A':
            CustomerArrived();  //处理客户到达事件
            break ;
      case 'D':
            CustomerDeparture(); //处理客户离开事件
            break ;
      default :
            Invalid();  //事件类型错误
    }
  }
  CloseForDay();       //计算平均逗留时间
}

void OpenForDay()
{
  //银行开门，初始化
  int i ;

  //全局变量
  TotalTime = 0 ;
  CustomerNum = 0 ;     //初始化累计时间和客户数

  InitList(&ev);     //初始化事件链表为空表
  en.OccurTime = 0 ;
  en.NType = 0 ; //设定第一个到达客户事件

  OrderInsert(ev , en , cmp); //插入事件表

  for(i = 0 ; i <= 4 ; ++i) //事件队列
  {
    InitQueue(q[5]);  //置空队列
  }

  Show() ;
}

Status MoreEvent()
{
    //判断事件表是否为空
    if(!ListEmpty(ev))
      return TRUE ;
    else
      return FALSE ;
}

void EventDrived(char *event)  //事件驱动
{
  
}
