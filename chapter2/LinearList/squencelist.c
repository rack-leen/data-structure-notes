/************************************************************************************//**
 *  @file       squencelist.c
 *
 *  @brief      Brief descriptinon of squencelist.c
 *
 *  @date       2017-10-09 20:58
 *
 ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100  //线性表初始空间
#define LISTINCREMENT 10    //线性表存储增量

/*状态码*/
#define TRUE 1              //真
#define FALSE 0             //假
#define OK 1                //真
#define ERROR 0             //假
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status ;
typedef int ElemType ;

/*建立线性表结构体*/

typedef struct
{
  ElemType *elem ;  //存储空间基址
  int length ;      //当前长度
  int listsize ;    //当前分配的存储容量
}Sqlist;


/* *******************************
 *
 *函数原型
 *
 * ********************************/

Status Initlist(Sqlist *L);
void Destroylist(Sqlist *L);                                      //销毁线性表
void Clearlist(Sqlist *L);                                       //置空线性表
Status Listempty(Sqlist *L);                                     //判断线性表是否为空
Status Listlength(Sqlist *L);                                    //获取线性表长度
Status Getelem(Sqlist *L , int i , ElemType *e);                 //得到线性表第i个元素
Status Priorelem(Sqlist *L , ElemType cur_e ,ElemType *pur_e);   //求线性表的前驱
Status Nextelem(Sqlist *L , ElemType cur_e , ElemType * next_e); //求线性表后驱
Status Insertlist(Sqlist *L , int i ,ElemType e);                //插入数据
Status Deletelist(Sqlist *L , int i ,ElemType *e);               //删除数据
Status Listtraverse(Sqlist *L);                                  //遍历线性表
void Listsort(Sqlist *L);                                        //对线性表元素进行排序
void Listinvert(Sqlist *L);                                      //倒置线性表中的元素


/*初始化线性表  */
Status Initlist(Sqlist *L)
{
  //构造空的线性表L
  L.elem = (ElemType *)maclloc(LIST_INIT_SIZE*sizeof(ElemType));
  if(!L.elem) exit(OVERFLOW);     //存储分配失败
  L.length = 0 ;                //存储长度
  L.listsize = LIST_INIT_SIZE ; //初始存储容量
  return OK ;
}

//销毁线性表
void Destroylist(Sqlist *L)
{
  if(L.elem != NULL)                                               //线性表中的元素不为空
  {
    //删除线性表中的元素
    L.elem = NULL ;
    L.length = 0 ;
    L.listsize = 0 ;
  }
}

//置空线性表
void Clearlist(Sqlist *L)                                         //置空则线性表长度为0
{
  L->length = 0 ;
}

//判断线性表是否为空
Status Listempty(Sqlist *L)
{
  if(L->length == 0) return TURE ;
  else return FALSE ;
}

//获取线性表长度
Status Listlength(Sqlist *L)
{
  return L->length ;
}

//获取线性表第i个数据元素
Status Getelem(Sqlist *L , int i , ElemType *e)
{
  if(i<0 || i > L.length)
  {
    printf("没有第%d个元素。\n", i);
    return ERROR ;
  }
  if(L->length == NULL)
  {
    printf("该线性表为空！\n");
    return ERROR ;
  }
  *e = L.elem[i-1];
}

//插入数据到线性表
Status Insertlist(Sqlist *L , int i , ElemType e)
{
  ElemType *q , *p ;                      //q为新增元素，p指针
  if(i<0 || i>L.length+1)                 //L.length+1是因为i是从1开始，而数组是从0开始
    return ERROR ;
  if(L.length > L.listsize)               //线性表长度大于了分配的存储空间
  {
    ElemType *newbase ;
    newbase = (ElemType *)realloc(L.elem , (L.listsize+LIST_INIT_SIZE)*sizeof(ElemType));  //realloc原型是
                                          //extern void *realloc(void *mem_address, unsigned int newsize);
    if(!newbase) exit(OVERFLOW);          //存储分配失败
    L.elem = newbase ;                    //新基址，就是在原来已满的存储空间为基础开始的新基址
    L.listsize += LIST_INIT_SIZE ;        //在初始存储容量的基础上增加
  }
  q = &(L.elem[i]);                     //

}


