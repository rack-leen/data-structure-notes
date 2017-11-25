/*************************************************************
*	name    : circlelist
*	anthor 	: rack
*	date   	: 2017.10.16 9:48 PM
*	mail   	: 1740234864@qq.com
*	function: circlelist 循环线性表
**************************************************************/

/*头文件*/
#include "CircleList.h"

/*函数实现*/

Status InitList(CircleList *L)                                  //初始化循环链表
{
	//操作结果：返回一个空的线性表L
	L = (CircleList)maclloc(sizeof(CircleNote));                //产生头节点，并使L指向头结点
	if(!L) return OVERFLOW ;
	L->next = L ;                                               //将最后一个节点指向头结点
	printf("初始化线性链表成功！")；
	return OK ;
}

/*销毁线性链表*/
Status DestroyList(CircleList *L)
{
	CircleList p = L , q = L->next ;                            //p指向头结点，q指向头结点的下一个
	while(p!=L)
	{
		p->next = q->next ;                                     //p的下一个成为q->next，将q排除了
		free(q);                                                //将排除的q释放
		q = p->next ;                                           //p->next代替q的值，将q移除
	}                                                           //q代表p->next与q->next之间的节点，循环一次，删除一个q，知道链表为空
	free(L);                                                    //释放L
	L = NULL ;
	printf("销毁链表成功！");
	return OK ;
}

/*清空链表*/
Status ClearList(CircleList *L)                                 //与DestroyList相似
{
	CircleList p = L , q = L->next ;
	while(p!=L)
	{
		p->next = q->next;
		free(q);
		q=p->next;                                              //由于q被删除，链表关系被破坏，于是由p->next来覆盖q的位置，修复关系
	}
	free(L);
	L = NULL ;
	printf("清空链表成功！");
	return OK ;
}

/*判断链表是否为空*/
Status ListEmpty(CircleList *L)
{
	CircleList p = L->next ;
	if(p == L)                                                 //因为p=L->next，p则为L的第二个节点。但是p==L，则是链表空
		return TRUE ;
	else
		return ERROR ;
}

/*链表长度*/
Status ListLength(CircleList *L)
{
	CircleList p = L , q = L->next ;
	int i ;
	while(q != L)                                              //链表不为空时循环
	{
		++i;
		q = q->next;                                           //遍历链表
	}
	return i ;
}

/*得到线性表元素*/
Status GetElem(CircleList *L , int i , Elemtype *e)
{//当第i个元素存在时，返回e
	CircleList p = L , q = L->next ;
	int j = 1 ;
	if(i < 1 || i > ListLength(&L)) return ERROR ;            //条件不满足
	while(j < i)                                              //遇到i则退出循环
	{
		++j ;
		q = q->next ;                                         //遍历
	}                                                         //找到元素，跳出
	e = q->data ;                                             //将数据域中的元素赋给e
	return OK ;
}

/*比较数据*/
Staus Compare(Elemtype e1 , Elemtype e2)
{
	if(e1 == e2)
		return OK ;
}

/**/
Status LocateList(CircleList *L , Elemtype e , Status (*compare)(Elemtype , Elemtype) )
{
	int i = 0 ;
	CircleList p = L->next ;
	while(p!=L)
	{
		++i ;
		if((*compare)(p->data , e))                            //满足关系
			return i ;                                         //返回满足关系的元素
		p = p->next ;                                          //接着遍历
	}
}

/*前驱*/
Status PriorElem(CircleList L , Elemtype cur_e , Elemtype *pur_e)
{
	//初始条件：链表存在
	//操作结果：cur_e表示数据元素，且不是第一个，则用pur_e返回前驱
	CircleList p = L->next ;                                   //p为下一个节点
	while(p && p->next && p->next !=  L)                       //p的下一个指向头结点，表示到了表尾
	{
		if(p->data == cur_e)                                   //找到元素
		{                                                      //p指向第一个node，=cur_e有前驱，前驱是p，
			pur_e = p->data ;                                  //p的前驱是头结点L将前驱的元素赋值给pur_e返回
			return TRUE ;
		}
		p = p->next ;                                          //逐个遍历
	}
	return ERROR;                                              //不满足条件
}

/*后继*/
Status NextElem(CircleList L , Elemtype cur_e , Elemtype *next_e)
{
	//初始条件：链表存在
	//操作结果：cur_e表示数据元素，且不是最后一个，则用next_e返回前驱
	CircleList p = L->next ;
	while(p && p->next && p->next != L)
	{
		if(p->data = cur_e)                                 //找到数据元素
		{
			next_e = p->next-data ;                         //将后继的元素赋值给next_e
			return next_e ;
		}
		p = p->next ;                                       //遍历
	}
	return ERROR ;                                          //不满足条件
}

/*插入元素*/
Status ListInsert(CircleList *L , int i , Elemtype *e)
{
	CircleList p = L ;
	int j = 0 ;
	if(i < 1 || i > ListLength(*L)+1)
		return ERROR ;
	while(j < i)                                            //i为插入元素，当没有找到元素时，循环
	{
		++j ;
		p = p->next ;
	}
	/*找到元素*/
	CircleList s = (CircleList)maclloc(sizeof(struct CircleList));
	s->data = e ;                                          //将e赋值给分配好的空间
	s->next = p->next ;                                    //s->next本来指向p，加入s元素,则指向p->next
	p->next = s ;                                          //p->next逆指向s
	return OK ;
}

/*删除元素*/
Status ListDelete(CircleList L , int i , Elemtype *e)
{
	CircleList p = L , q ;                                //p指向头结点，q为表中元素
	int j = 0 ;
	if(i < 1 || i > ListLength(L)+1) return ERROR ;
	while(j < i-1)
	{
		++j ;
		p = p->next ;

	}
	q =  p->next ;                                       //表示q被删除,p->next的值赋给q，q被释放
	p->next = q->next ;                                  //修复链表关系，原本p的下一个为q，现在为q->next
	e = q->data ;
	free(q);
	return OK ;
}

Status visit(Elemtype e)
{
	return OK ;
}

/*遍历链表*/
Status ListTraverse(CircleList L , Status (*visit)(Elemtype))
{
	CircleList p = L->next ;
	printf("线性表遍历的结果：");
	while(p!=L)
	{
		if((*visit)(p->data))                           //表示有这个元素
			printf("%d",p->data);
		p = p->next ;
	}
	printf("\n");
	return OK ;
}
