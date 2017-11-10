/*线性表的静态单链表存储结构，一维数组表示*/

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

#define MAXSIZE 100
typedef int Status ;
typedef int Elemtype ;

/*函数体*/
int LocateList(SLinkList S , Elemtype e);     //在链表中查找第i个为e的元素，并返回下标i
void InitList(SLinkList *space);              //初始化
int Maclloc(SLinkList *space);                //为链表分配内存
void FreeList(SLinkList *sapce int k) ;       //释放内存
void Difference(SLinkList *space , int *S);   // 合并链表

/*结构体*/
#typedef struct 
{
	Elemtype data ;
	int cur ;
}component , SLinkList[MAXESIZE] ;                          

/*定位函数，获取下标*/
int LocateList(SLinkList S , Elemtype e)
{
	int i ;
	i = S[0].cur ;                          //S[0].cur表示第一个节点，并将第一个节点给i
	while(i && S[i].data != e)              //i不为最后一个节点时或者S[0].data等于e时，则跳出
		i = S[i].cur ;                      //i代表表中一个节点,S[0].cur表示表中下一个节点，相当于p = p->next
	return 0 ;
}

/*初始化*/
void InitList(SLinkList *space)
{
	int i ;
	for(i = 0 ; i < MAXSIZE - 1 ; ++i)      //将一维数组中的各分量连接成一个备用链表，i+1 ,是因为i从0开始，而链表是从1开始
		space[i].cur = i + 1 ;
	space[MAXSIZE - 1].cur = 0 ;            //最后一个元素指向的下一个为空，表示链表结束
}

/*动态内存分配*/
int MacllocList(SLinkList *space)
{
	int i ;
	i = space[0].cur ;                      //i指向头节点
	if(space[0].cur)                  
		space[0].cur = space[i].cur ; //sapce[0].cur为指针p，p为空，跳出。space[0].cur表示下一个节点，space[i].cur将值付给space[0].cur， 链表长度增加，space[0].cur又指向下一个节点。 
	return i ;                              //返回i
}

/*释放内存*/
void FreeList(SLinkList *sapce , int k)      //space参数为链表，将下标为k的空闲节点回收至备用链表
{
	space[k].cur = space[0].cur ;           //space[0].cur将值赋给space[k].cur，代替space[k].cur，space[k].cur被清空
	space[0].cur = k ;                      //将k挂到备用链表的头指针后面
}

/*合并线性表*/
void Difference(SLinkList *space , int *S)
{
	int r , i , j , k , p , m , n ; 
	InitList(space);                        //初始化   
	S = MacllocList(space);                 //分配内存
	r = S ;                                 //r指向S的当前的最后结点
	scanf(m , n ) ;
	for(j = 0 ; j < m ; ++j)                //输入a链表元素
	{
		i = MacllocList(space);             //为链表分配节点
		scanf(space[i].data);
		space[r].cur = i ;                  //space[r].cur表示r的下一个节点i，但是r为最后一个节点，所以i则是r本身
											//i分配节点，space[r].cur接收节点，则链表增加一个节点
		r = i ;                             //表示i成为最后一个节点，r指向i，r的下一个节点是i，则i没有后继，被插入了表尾。
	}
	space[r].cur = 0 ;                      //尾节点的指针为空
	
	for(j = 0 ; j < n ; ++i)                //输入b链表元素
	{
		scanf(b);
		p = S ;                             //与上一个相同，p指向S的当前最后节点
		k = space[S].cur ;                  //k指向集合A中的第一个节点
		/*第一种情况*/
		while(k != space[r].cur && space[k].data != b) //在当前表中查找，两个集合的数如果相同则删除，不相同则插入
		{	
			p = k ;                         //插入一个元素
			k = space[k].cur ;                  //顺序查找 
		}
		/*第二种情况*/
		if(k == space[r].cur)                   //该表中不存在该元素，插入在r节点之后.且r的位置不变
		{
			i = Maclloc(space) ;                //分配内存
			space[i].data = b ;
			space[i].cur = space[r].cur ;       
			space[r].cur = i ;                  //r节点指向i
		}
		/*第三种情况*/
		else                                    //该元素已在表中，需删除
		{
			space[p].cur = space[k].cur ;       //space[p].cur是指向最后一个节点，它指向space[k].cur表明k被删除
			FreeList(space , k) ;               //将分配的空间释放
			if(r == k)                          //删除的是r指向的节点，也就是尾节点，则修改尾指针
				r  == p ;              
		}
	}
}














