/************************************************************************************//**
 *  @file       example.c
 *
 *  @name       rack                
 *
 *  @brief      Brief descriptinon of example.c 
 *
 *  @date       2017-10-10 20:23
 *
 ***************************************************************************************/
/*头文件*/
#include<stdio.h>
#include<stdlib.h>

/*状态码*/
#define TURE 1 
#define FALSE 0 
#define OK 1 
#define ERROR 0 
#define OVERFOLW -2 
#define INFEASINLE -1 


typedef int Status ;
typedef int Elemtype ;

/*结构体*/
typedef struct Lnode{
  Elemtype data ;
  struct Lnode *next ;
}Lnode , *LinkList ;                                          //Lnode为结构体名，LinkList为结构体的类型

/*函数体*/
Status Getelem(LinkList L , int i , Elemtype *e);
Status InsertList(LinkList *L , int i , Elemtype e);          //L链表中，在第i个位置之前插入e 
Status DeleteList(LinkList *L , int i , Elemtype *e);         //L链表中，删除第i个元素，用*e返回其值
void CreateList(LinkList *L , int n);                         //n为节点数，建立带表头节点的链表L
void MergeList(LinkList *La , LinkList *Lb , LinkList *Lc);   //La Lb 合并到Lc

/*函数实现*/

/*取得元素*/
Status Getelem(LinkList L , int i , Elemtype *e )
{
  int j ;                                             //j为计数器
  LinkList p ;
  
  p = L->next;                                        //p指向第一个节点
  j = 1 ;                                             //从1开始计数
  
  while(p && j < i )                                  //顺着指针查找，直到p为空或者p指向第i个元素为止
  {
    p = p->next ;                                     //顺指针向后查找
    ++j ;                                             //先++再赋值
  }
  
  if(!p || j > i)                                     //第i个元素不存在
    return ERROR ;
  else
    e = p->data ;                                     //取第i个元素
  return OK ;
}

//指针的插入与删除操作只需要改变逻辑关系，只需修改指针域
/*插入操作*/
Status InsertList(LinkList *L , int i , Elemtype e)
{
	int j ;
	LinkList p , s ; 
	
	p = L ; 
	j = 0 ;
	
	while(p && j < i)
	{
		p = p->next ;
		++j ;
	}
	if(!p || j > i) 
		return ERROR ;
	 
	s = (LinkList)maclloc(sizeof(Lnode)) ;           //生成新节点
	s->data = e ;                                    //e为插入的元素，将e赋值给新节点的数据域
	s->next = p->next ;                              //节点s的指针域s->next指向下一个节点p->next
	p->next = s ;                                    //p->next是上一个及节点的指针，指向s
	
	return OK ;
}

/*删除操作*/
Status DeleteList(LinkList *L , int i , Elemtype *e)
{
	int j ;
	LinkList p , q ;
	
	p = L ;
	j = 0 ;
	
	while(p->next && j < i-1)                       //由于最后一个的指针域为NULL，不是p->next，因此，就少一位。
	{
		p = p->next ;
		++j ;
	}
	
	if(!(p->next) || j > i-1) return ERROR ;
	q = p->next ;                                  //下一个节点覆盖q
	p->next = q->next ;                            //删除节点只需要是删除元素前一个节点指向q的下一个节点q->next
	e = q->data ;                                  //将q的数据存放到e中
	
	free(q) ;                                      //释放节点
	return OK ;
}

/*创建链表*/
void CreateList(LinkList *L , int n)
{
	int i ;
	LinkList p ;
	L = (LinkList)maclloc(sizeof(Lnode));          //动态分配空间,分配整个链表空间
	L->next = NULL ;                               //表示没有下一个节点，只有这一个头节点的空表
	for(i = n ; i > 0 ; --i)                       //从n开始，归零操作，建立链表
	{
		p = (LinkList)maclloc(sizeof(Lnode));      //生成新的节点
		scanf("%d" , n);
		p->next = L->next ;                         //由于L->next=NULL , 没有后继，只能通过逆置，用p->next指向L->next
		L->next = p ;                              //插入到表头
	}
}

/*合并链表*/
void MergeList(LinkList *La , LinkList *Lb , LinkList *Lc)
{
	LinkList pa , pb , pc;
	pa = La->next ;
	pb = Lb->next ;
	
	Lc = pc = La ;                                   //用La的头结点作为Lc的头节点
	while(pa && pb)                                  //pa pb非空
	{
		if(pa->data <= pb->data)
		{
			pc->next = pa ;                          //现在头结点为pa
			pc = pa ;                                //记录当前指针
			pa = pa->next ;                          //向后递归处理
		}
		else
		{
			pc->next = pb ;
			pc = pb ;
			pb = pb->next ;
		}
	}
	pc->next = pa ? pa:pb ;                           //插入剩余段，pc->next指向pa或者pb，就是将pa,pb链表连接到后面
	free(Lb);
}

/*
L是头结点
head->1->2->3->4
head就是L所在的位置  
p=L->next->next;     //指向1.next;
q=p->next;           //指向2.next
L->next->next=NULL;  //将1.next设为null
while(p!=null)
{
p->next=L->next;     // 两个结点倒置
L->next=p;           //现在头结点为p
p=q;                 //记录当前的p指针
q=q->next;           //向后递归进行处理
*/
