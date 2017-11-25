/***************************************************************************************
 *  file       dlist.c
 *
 *  author     rack
 *
 *  brief      Brief descriptinon of dlist.c
 *
 *  date       2017-10-23 13:51
 *
 *  function   双向链表
 *
 ***************************************************************************************/

/***************************************
 ****应用简介：用双向链表输出长方体*****
 ***************************************/

/*header file*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

/*structure*/
typedef struct Cuboid   //长方体
{
   int length  ;
   int width ;
   int height   ;
}Cuboid ;

/*产生长方体的数据对象*/
Cuboid *cube_instance(const int length , const int width , const int height)
{
  Cuboid *cb_ptr ;                           //Cuboid类的指针
  cb_ptr = (Cuboid *)malloc(sizeof(Cuboid)); //分配存储空间
  if(cb_ptr == NULL)
    return NULL ;
  cb_ptr->length = length ;                  //产生Cuboid类型的数据对象
  cb_ptr->width  = width  ;
  cb_ptr->height = height   ;
  return cb_ptr ;
}

/********销毁**********/
void destroy(void *data)                    //函数头文件中私有部分中的destroy实现
{
	free(data);
	return;
}

/******main函数*******/
int main(int argc , char **argv)           //argc表示命令行中一行命令个数，argv表示命令
{                                          //example: ls -a ,argc=2,argv[]={ls,-a}
	int i ;
	Dlist dlist_exp ;                      //结构体名
	DlistElem *p = NULL ;                  //初始化
	Cuboid *cb1_ptr , *cb2_ptr ,
		   *cb3_ptr , *cb4_ptr , *cb5_ptr ;// 表示5个长方体
	Cuboid *cb_ptr ;                       //函数指针

	/*赋值*/
	cb1_ptr = cube_instance(1,2,3);
	cb2_ptr = cube_instance(6,10,8);
	cb3_ptr = cube_instance(5,20,30);
	cb4_ptr = cube_instance(17,100,25);
	cb5_ptr = cube_instance(3,6,9);

	/*初始化链表*/
	dlist_init(&dlist_exp , destroy);

	/*增加5个元素进链表*/
	dlist_ins_next(&dlist_exp , NULL , (void *)cb1_ptr); //链表开始时是空链表
	p = dlist_head(&dlist_exp);                          //成为链表头结点,得到第一个元素的地址，知道链表首地址
	dlist_ins_next(&dlist_exp , p , (void *)cb2_ptr);    //p本链表元素
	p = dlist_next(p);                                   //将cb2_ptr加入， cb1->cb2
	dlist_ins_pure(&dlist_exp , p , (void *)cb3_ptr);    //将cb3加入cb2的前面（前向插入），cb1->cb3->cb2
	dlist_ins_pure(&dlist_exp , p , (void *)cb4_ptr);    //将cb4插入cb2之前， cb1->cb3->cb4->cb2
	p = dlist_pure(p);                                   //连续前向插入，以连续操作的第一个为基点，都插入第一个之前（cb2）
	dlist_ins_pure(&dlist_exp , p , (void *)cb5_ptr);    //再次前向插入，向前插入的基点元素有cb2变为cb4
														 //cb1->cb3->cb5->cb4->cb2

	//now the sequence is:cb1->cb3->cb5->cb4->cb2
	printf("tranverse and print: \n");
	p = dlist_head(&dlist_exp);                         //得到链表头元素
	for(i = 0 ; i < dlist_size(&dlist_exp) ; i++)
	{
		cb_ptr = (Cuboid *)dlist_data(p);               //得到元素的数据域，每个数据域是Cuboid的指针，examplr.p->data是一个指针
		printf("i = %d :" , i);                         //i是计数
		printf("length = %d , width = %d , height = %d\n." , cb_ptr->length , cb_ptr->width , cb_ptr->height);
		p = dlist_next(p);                              //指针指向下一个，数据域包括了三个元素
	}

	/*删除元素*/
	p = dlist_head(&dlist_exp);                         //指出头结点地址
	p = dlist_next(p);                                  //向表尾浏览,it's likely to p = p->next
	p = dlist_next(p);                                  //接着
	dlist_remove(&dlist_exp , p , (void **)&cb_ptr);    //cb_ptr指向的是一个元素，包括了长宽高.删除第三个
	printf("the data of the third element: length = %d , width = %d , height= %d\n." ,
		   cb_ptr->length , cb_ptr->width , cb_ptr->height);
	destroy(cb_ptr);

	printf("after remove the third elements : \n");
	p = dlist_head(&dlist_exp);
	for(i = 0 ; i < dlist_size(&dlist_exp) ; i++)
	{
		cb_ptr = (Cuboid *)dlist_data(p);
		printf("i = %d :" , i);
		printf("length = %d , width = %d , height = %d\n." , cb_ptr->length , cb_ptr->width , cb_ptr->height);
		p = dlist_next(p);
	}

	/*销毁链表*/
	dlist_destroy(&dlist_exp);
	printf("after destroy the list,its size = %d\n", dlist_size(&dlist_exp));
    return 0;

}
