/********************************************************************
*	program name : dlist.c
*	anthor  name : rack
*	mail address : 1740234864@qq.com
*	function     : doubly linked list 双向链表
*	last date    : 2017.10.21 22:59
*********************************************************************/
/*************************************
************函数实现******************
*************************************/

/*header file*/
#include <stdlib.h>
#include <string.h>
#include "dlist.h"              //自定义的头文件，包括了include<stdio.h>

/*初始化*/
void dlist_init(Dlist *list , void (*destroy)(void *data))
{
	list->size = 0 ;                     //长度为0
	list->destroy = destroy ;
	list->head = NULL ;                  //头结点为空
	list->tail = NULL ;                  //为节点为空

	return ;
}


/*销毁线性表*/
void dlist_destroy(Dlist *list)
{
	void *data ;
	while(dlist_size(list) > 0)         //头文件中定义的list->size
	{
		if(dlist_remove(list , dlist_tail(list) , (void **)&data) == 0  //删除结果为否,没有销毁
		   								&& list->destroy!=NULL)//头文件中定义的函数,(void **)&data)???
			list->destroy(data);          //头文件中的结构体中的元素
	}
	memset(list , 0 , sizeof(Dlist));            //把list所指内存区域的前sizeof(Dlist)个字节设置成0。
	return ;
}

/*元素前向插入*/
int dlist_ins_pure(Dlist *list , DlistElem *element , const void *data)
{
	DlistElem *new_element ;                   //建立一个新的元素
	/*不满足条件*/
	if(element == NULL && dlist_size(list) != 0)  //链表元素为空，但链表长度不为空
		return -1 ;
	/*满足条件*/
	new_element = (DlistElem *)malloc(sizeof(DlistElem));  //分配空间
	/*判断新元素*/
	if(new_element == NULL)
		return -1 ;
	new_element->data = (void *)data ;     //(void *)data表示输入的插入元素
	/*新元素满足条件*/
	if(dlist_size(list) == 0)             //链表长度为空时,链表元素只有插入元素
	{
		list->head = new_element;         //链表头结点为新插入元素
		list->tail = new_element;         //链表尾节点为新插入元素
		new_element->pure = NULL;         //新插入元素前指针指向空
		new_element->next = NULL;         //新插入元素后指针指向空
	}                                     //表明表中只有新插入元素
	else                                  //链表元素不为空，并且长度不为空
	{
		new_element->next = element;      //加入的新元素的下一个是插入地方原来的元素
		new_element->pure = element->pure;//新元素指向的前一位元素是原来元素指向的前一位元素
		/*前指针指向的元素为空*/
		if(element->pure == NULL)
			list->head = new_element;
		else                              //element前指针指向的数据域变为新元素
			element->pure->next = new_element;//
		element->pure = new_element;      //element的前指针指向new_element
	}
	list->size++;                         //链表长度加1
	return 0 ;
}

/*后向插入*/
int dlist_ins_next(Dlist *list , DlistElem *element , const void *data) //const表示插入的数据不能被直接修改
{
	DlistElem *new_element;
	if(element == NULL && dlist_size(list) != 0)
		return -1 ;
	new_element = (DlistElem *)malloc(sizeof(DlistElem));
	if(new_element == NULL)
		return -1 ;
	new_element->data = (void *)data;
	if(dlist_size(list) == 0)                                 //链表为空时
	{
		new_element->pure = NULL ;                           //新元素前指针指向空
		new_element->next = NULL ;                           //新元素后指针指向空
		list->head = new_element ;                           //头结点为新元素
		list->tail = new_element ;                           //尾节点为新元素
	}                                                        //表明整个链表只有新元素一个元素
	else
	{
		if(dlist_next(element) == NULL)                       //相当于element->next，表示新元素插入进去就是尾节点
			list->tail = new_element ;                       //新元素代替尾节点
		else
			new_element->next->pure = new_element ;          //新元素的下一个元素的前指针指向新元素，表示新元素后面有元素
		new_element->next = element->next ;                  //新元素的下一个元素是原来element元素的下一个，修复关系
		new_element->pure = element ;                        //新元素的前指针指向1element,表示新元素向element后面插入
	}
	list->size++;
	return 0 ;
}

/*链表的删除*/
int dlist_remove(Dlist *list , DlistElem *element , void **data)//修改操作中，数据修改的数据需要被删除，被赋值，则可以修改
{
	/*首先判断链表是否为空，不允许链表长度为空或者空链表*/
	if(element == NULL && dlist_size(list) == 0)
		return -1 ;
	*data = element->data ;                                   //移除链表元素
	/*需要移除的元素为表头元素*/
	if(element == list->head)
	{
		list->head = element->next ;                          //表头元素变为element的下一个
		/*如果表头为空*/
		if(list->head == NULL)
			list->tail = NULL ;                              //则只有一个元素，删除这个元素，链表为空
		else                                                 //表头不为空，将删除element元素
			element->next->pure = NULL ;                     //元素下一个元素的前指针指向的元素为空，表示将element元素删除
	}
	else                                                     //需要移除的元素不为表头元素
	{
		element->pure->next = element->next ;                //将element删除，元素的前指针指向的前一个元素现在指向的是element的下一个元素
		if(element->next == NULL)                            //element为表尾元素
			list->tail = element->pure ;                     //表示尾节点变为element的前一个，删除了原来的尾节点element
		else                                                 //元素不是尾节点
			element->next->pure = element->pure ;            //element的下一个元素的前指针指向的是element的前一个，没有指向element，删除
	}
	free(element);
	list->size-- ;
	return 0 ;
}
