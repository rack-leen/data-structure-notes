/********************************************************************
*	program name : dlist.h
*	anthor  name : rack
*	mail address : 1740234864@qq.com
*	function     : doubly linked list
*	last date    : 2017.10.21 22:59
*********************************************************************/
/************************************************
***********头文件********************************
*************************************************/
/*header file*/
#ifndef _DLIST_H
#define _DLIST_H
#include <stdio.h>

/*define a structure for the list element*/
typedef struct DlistElem_
{
	void *data ;                                          //数据元素
	struct DlistElem_ *pure ;                             //前指针
	struct DlistElem_ *next ;                              //后指
	}DlistElem;

/*define a structure for the double linked list*/
typedef struct Dlist_
{
	int size ;                                            //链表长度
	void (*destroy)(void *data);                          //销毁链表
	void (*match)(const void *key1 , const void *key2);        //
	DlistElem *head ;
	DlistElem *tail ;
}Dlist;

/*define public interface*/
void dlist_init(Dlist *list , void (*destroy)(void *data));
void dlist_destroy(Dlist *list);
int dlist_ins_pure(Dlist *list , DlistElem *element , const void *data);//data是一个指向任意类型的指针，但指向的值必须是常量
int dlist_ins_next(Dlist *list , DlistElem *element , const void *data);
int dlist_remove(Dlist *list , DlistElem *element , void **data);//data是指向任意类型的指针

#define dlist_size(list) ((list)->size)  //get the size of the list 链表长度
#define dlist_head(list) ((list)->head)  //get the head element   头结点
#define dlist_tail(list) ((list)->tail)  //get the tail element   尾节点
#define dlist_is_head(element) ((element)->pure == NULL ? 1 : 0 ) //数据元素前驱是否为空,为空，则头结点
#define dlist_is_tail(element) ((element)->next == NULL ? 1 : 0 ) //数据元素后继是否为空，为空，则尾节点
#define dlist_pure(element) ((element)->pure) //get the pure of the element 得到这个元素的前指针域
#define dlist_next(element) ((element)->next)//get the next of the element 得到这个元素的后指针域
#define dlist_data(element) ((element)->data)//get the data of the element 得到这个元素的数据域

#endif


