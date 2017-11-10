/********************************************************************
*	@program name : doubly linked list
*	@anthor  name : rack
*	@mail address : 1740234864@qq.com
*	@function     : doubly linked list
*	@last date    : 2017.10.17 16:30
*********************************************************************/


/*头文件*/
#include<stdio.h>
#include<stdio.h>

/*函数状态码*/
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

/*类型定义*/
typedef int Status ;
typedef int Elemtype ;

/*结构体*/
typedef struct DuNode
{
	Elemtype data ;                                    //数据域
	struct DuNode *prior ;                             //前指针域
	struct DuNode *next  ;                             //后指针域
}DuNode , *DuNodeList ;

/*函数体*/
Status ListInsert(DuNodeList *L , int i , Elemtype e);
Status ListDelete(DuNodeList L , int i , Elemtype e);

/*函数原型*/

/*插入*/
Status ListInsert(DuNodeList *L , int i , Elemtype e)
{
	DuNodeList p , s;
	if(!(p = GetElem(L , i))) return ERROR;
	if(!(s = (DuNodeList)malloc(sizeof(DuNodeList)))) return ERROR ;
	s->data = e ;
	s->prior = p->prior ;                              //s的前指针代替p前指针，p前指针向后移
	p->prior->next = s ;
	s->next = p ;
	return OK ;
}

/*删除*/
Status ListDelete(DuNodeList L , int i , Elemtype e)
{
	DuNodeList p ;
	if(!(p = GetElem(L , i))) return ERROR;
	e = p->data ;
	p->prior->next = p->next ;                          //p的前指针指向的前一个数据域指向p的下一个
	p->next->prior = p->prior ;                         //p的下一个的前指针指向p的前指针，也就是p的前一个元素，忽略了p,p删除
	return OK ;
}


