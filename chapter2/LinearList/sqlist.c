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
void Destroylist(Sqlist *L);                                                           //销毁线性表
void Clearlist(Sqlist *L);                                                               //置空线性表
Status Listempty(Sqlist *L);                                                          //判断线性表是否为空
Status Listlength(Sqlist *L);                                                          //获取线性表长度
Status Getelem(Sqlist *L , int i , ElemType *e);                             //得到线性表第i个元素
Status Priorelem(Sqlist *L , ElemType cur_e ,ElemType *pur_e);     //求线性表的前驱
Status Nextelem(Sqlist *L , ElemType cur_e , ElemType * next_e); //求线性表后驱
Status Insertlist(Sqlist *L , int i ,ElemType e);                               //插入数据
Status Deletelist(Sqlist *L , int i ,ElemType *e);                             //删除数据
Status Listtraverse(Sqlist *L);                                                       //遍历线性表
void Listsort(Sqlist *L);                                                               //对线性表元素进行排序
void Listinvert(Sqlist *L);                                                            //倒置线性表中的元素


/*初始化线性表  */
Status Initlist(Sqlist *L)
{
  //构造空的线性表L
  L->elem = (ElemType *)maclloc(LIST_INIT_SIZE*sizeof(ElemType));
  if(!L->elem) exit(OVERFLOW);     //存储分配失败
  L->length = 0 ;                //存储长度
  L->listsize = LIST_INIT_SIZE ; //初始存储容量
  return OK ;
}

//销毁线性表
void Destroylist(Sqlist *L)
{
  if(L->elem != NULL)                                               //线性表中的元素不为空
  {
    //删除线性表中的元素
    L->elem = NULL ;
    L->length = 0 ;
    L->listsize = 0 ;
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
  if(L->length == 0) return TRUE ;
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
  if(i<0 || i > L->length)
  {
    printf("没有第%d个元素。\n", i);
    return ERROR ;
  }
  if(L->length == NULL)
  {
    printf("该线性表为空！\n");
    return ERROR ;
  }
  *e = L->elem[i-1];                                            //将获取到的元素通过e返回
  return OK ;
}

//求线性表前驱
Status Priorelem(Sqlist *L ,ElemType cur_e , ElemType *pur_e)
{
	int i = 2 ;                                                  //线性表中第二个元素开始才有前驱
	while(i <=  L->length)
	{
		if(L->elem[i-1] == cur_e)                         //这个元素是需要的元素
		{
			*pur_e = L->elem[i-2] ;                       //则pur_e是这个元素的前驱
			return OK ;
		}
		i++ ;                                                      //这个操作进行i++次
	}
	return ERROR ;                                        //不满足条件则返回ERROR
}

//求线性表的后继
Status Nextelem(Sqlist *L , ElemType cur_e , ElemType *next_e)
{
	int i = 1 ;
	while(i < L->length - 1)                           //因为最后一个没有后继，所以减一
	{
		if(L->elem[i-1]  == cur_e)
		{
			*next_e = L->elem[i];
			return OK ;
		}
		i++ ;
	}
	return ERROR ;
}

//插入数据到线性表
Status Insertlist(Sqlist *L , int i , ElemType e)
{
  ElemType *q , *p ;                      //q为新增元素，p指针
  if(i<0 || i>L->length+1)                 //L.length+1是因为i是从1开始，而数组是从0开始
    return ERROR ;
  if(L->length > L->listsize)               //线性表长度大于了分配的存储空间
  {
    ElemType *newbase ;
    newbase = (ElemType *)realloc(L->elem , (L->listsize+LIST_INIT_SIZE)*sizeof(ElemType));  //realloc原型是
                                          //extern void *realloc(void *mem_address, unsigned int newsize);
    if(!newbase) exit(OVERFLOW);          //存储分配失败
    L->elem = newbase ;                    //新基址，就是在原来已满的存储空间为基础开始的新基址
    L->listsize += LIST_INIT_SIZE ;        //在初始存储容量的基础上增加
  }
  q = &(L->elem[i-1]) ;                      //q是要插入的元素
  for(p = L->elem[L->length - 1] ; p >= q ; p--)    //当p从最后一位右移到p<q时，找到被插入元素，退出
		*(p+1) = *p ;                         //被插入元素右移
	*q = e ;
	L->length ++ ;
	return OK ;
}

//删除元素
Status Deletelist(Sqlist * L , int i , ElemType *e)
{
	if(i < 0 || i > L->length)
	{
		printf("需要删除的位置不存在！\n");
		return ERROR ;
	}
	ElemType *p , *q ;
	p =  &L->elem[i-1];                          //p为被删除的元素位置
	*e = *p ;                                         //先将被删除的元素删除
	q = &L->elem+L->length - 1 ;         //标尾位置
	for(p = p+1 ; p<= q ; p++)               //再将线性表左移，填补空缺
	{
		*(p-1)= *p ;
	}
	L->length -- ;
	return OK ;
}

//遍历线性表
Status Listtraverse(Sqlist *L)
{
int i ;
	if(L->length == 0)
	{
		printf("\n该线性表为空！\n");
		return ERROR ;
	}
	else
	{
		printf("\n该线性表为： \n");
		for(i = 0 ; i <= L->length ; i++)
			printf("%d" , L->elem[i-1]);            //得出该元素
		printf("\n");
	}
	return OK ;
}

//对线性表进行排序.选择排序
void Listsort(Sqlist *L)
{
	int i  , j ,tmp , max;
	for(i = 0 ; i <= L->length-1 ; i++)
	{
		max = i ;                                   //max代替i
		for(j = i ; j <= L->length ; j++)
		{
			if(L->elem[i] < L->elem[j])
			{
				max = j ;                          //j被代替为j
			}
		}
		tmp = L->elem[max] ;
		L->elem[max] = L->elem[i];
		L->elem[max] = tmp ;
	}
}

//倒置线性表中的所有元素
void Listinvert(Sqlist *L)
{
	int i = 0 , j  = L->length, tmp  ;
	while(i < j)
	{
		tmp = L->elem[i] ;
		L->elem[i]  = L->elem[j] ;
		L->elem[j] = tmp ;
		i++ ;
		j-- ;
	}
}

int main()
{
	Sqlist L ;
	int i ;
	ElemType e;

	/*初始化结构体 */
	if(Initlist(&L) == NULL)
		printf("初始化列表失败！\n");
	else
		printf("初始化列表成功！\n");

	//判断线性表是否为空
	printf("列表是否为空？\n");
	if(Listempty(&L) == NULL)
	{
		printf("该线性表为空！\n");
	}
	else
		printf("该线性表不为空！\n");

	//获取线性表长度
	printf("该线性表长度：%d .\n" , Listlength(&L));

	//插入元素
	for(i =0 ; i <= 8 ; i++)
		Insertlist(&L , i , i + 1);
	Listtraverse(&L);                              //遍历线性表
	printf("该线性表长度：‘\n"  ,  Listlength(&L));

	//查找前驱
	printf("现在要查找的元素的前驱！\n");
	printf("输入将要查找的元素： \n");
	scanf("%d" , &i);
	if(Priorelem(&L , i , &e) == 1)
		printf("元素的前驱是：%d\n" , e);
	else
		printf("元素不存在前驱！\n");

	//查找后继
	printf("现在要查找元素的后继：\n");
	printf("输入将要查找的元素：\n");
	scanf("%d", &i);
	if(Nextelem(&L , i , &e) == 1)             //为真
		printf("元素的后继为：%d\n" , e) ;
	else
		printf("元素不存在后继！\n") ;

	//删除元素
	printf("删除的元素！\n");
	printf("删除前： \n");
	Listtraverse(&L) ;                                    //遍历列表
	printf("需要删除的元素： \n");
	scanf("%d"  , &i) ;
	Deletelist(&L , i , &e) ;
	printf("删除后： \n");
	Listtraverse(&L);

	//元素排序
	printf("排序前： \n");
	Listtraverse(&L);                          //遍历
	printf("排序后：\n");
	Listsort(&L);
	Listtraverse(&L);

	//元素倒置
	printf("倒置前：\n");
	Listtraverse(&L);
	printf("倒置后：\n");
	Listinvert(&L);
	Listtraverse(&L);
	return 0 ;
}
