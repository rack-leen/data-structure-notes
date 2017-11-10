/**************************************************************************
*	@program name : 两个多项式相加
*	@author  name : rack
*	@last data    : 2017.10.26     
***************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#define NULL 0 

/*构建一元多项式结构体*/
typedef struct term
{
	float coef ;                       //一元多项式底数部分
	int expn ;                         //一元多项式指数部分
	struct term *next ;
}term , LinkList ;

typedef LinkList polynomial ;

/*比较项的指数大小*/
int cmp(LinkList qa , LinkList qb)    //qa ,qb分别是两个多项式的指数部分
{
	if(qa->expn > qb->expn)          //qa比qb指数大
		return 1 ;
	else if(qa->expn == qb->expn)    //两者指数相等
		return 0 ;
	else
		return -1 ;
}

/*找寻匹配項的指数*/
bool LocateElem(LinkList L , LinkList t , LinkList &q)
{
	LinkList p1 = L->next ;         //指向表中的下一个
	LinkList p2 = L ;               //总是指向p1前驱
	
	if(t->expn > p1->expn)          //p1小于t，表示p1还在找与t匹配的指数
	{
		p1 = p1->next ;             //p1接着找下一个
		p2 = p2->next ;             //p2表示p1的前驱，与p1一起
	}
	else if(t->expn == p1->expn)
	{
		q = p1 ;                    //表示p1已经找到与t匹配的指数q
		return true ;
	}
	else                            //表示p1->expn > t->expn，表明p1没有找到与t匹配的指数
	{
		q = p2 ;                    //则返回q的前驱节点     
		return false ;
	}
}

/*建立表示一元多项式带有头节点的有序链表p，利用尾插法*/
void CreateList(polynomial &p , int m)    //m代表输入的第m項
{   /*表示建立一个空链表*/                               	   
	p = (polynomial)malloc(sizeof(term)); //建立一个带有头节点的空链表
	p->next = NULL ;                      //表示p为最后一个元素
	LinkList r = p ;                      //r总是指向最后一个元素
	
	printf("请输入系数，指数：\n");
	for(int i = 0 ; i < m ; i++)
	{   
		LinkList t = (LinkList)malloc(sizeof(term));//为新节点分配存储空间
		t->next = NULL ;                            //插在节点尾部，所以新节点的下一个为空
		LinkList q ;                                //定义q
		scanf("(%f,%d)",&t->coef , &t->expn);
		/*判断*/
		if(!LocateElem(P ,t , q))         //本次输入的指数項在链表中没有，将t插入到尾部,q为链表第一个指数t->expn的前驱节点
		{
			t->next = q->next ;           //在t未插入之前，q->next=NULL,t插入之后，q->next赋值给t->next，相当于t->next=NULL
			q->next =  t ;                //q的下一个为t,t的下一个为空，t是链表尾部
		}
		else 
			i-- ;                         //当前链表已有节点元素指数与输入項指数相同，重新输入插入項t，重新比较
	}	
}

/*打印多项式*/
void print(ploynomial p)
{
	LinkList q = p->next ;                //q为p（链表头节点）的下一个
	printf("打印多项式的线性表:[");
	while(q)
	{
		printf("(%.2f,%d)",q->coef , q->expn);
		q = q->next ;                     //遍历链表
	}
	printf("]\n\n");
}

/*多项式相加*/
void AddPloyn(ploynomial &pa , ploynomial &pb)
{
	LinkList qa = pa->next ;              //qa指向pa头结点的下一个
	LinkList qb = pb->next ;              //qb指向pb头结点的下一个
	LinkList qc = pc ;                    //pc总是指向和多项式的最后一项
	
	while(qa&&qb)
	{
		switch(cmp(qa , qb))
		{
			case 1:                      //cmp中的return 1(qa的指数大于qb，qb在前面，就将qb接在qc后面)
				qc->next = qb ;          //qb代替qc->next,就是qb是qc的下一个
				qc = qb ;                //qc指向qb？？？
				qb = qb->next ;          //下一个
				break ;
			case 0:                      //return 0 （两个项指数相等,qa->expn = qb->expn,将qa接在qc后面）
				sumofcoef = qa->coef + qb->coef ; //如果指数相同，两项系数相加
				/*系数之和不为0*/
				if(!sumofcoef != 0.0)    //将两项之和放入qa，将qb释放
				{
					LinkList s = qb ;    //即将释放qb
					qa->coef = sumofcoef ; 
					qc = qa ;            //qc指向qa
					qa = qa->next ;      //qa向后遍历
					qb = qb->next ;      //qb向后遍历
					free(s) ;            //释放s(也就是qb)
				}
				else                     //系数之和为0，则将这个节点的qa,qb都释放掉.
				{
					LinkList s1 = qa ;
					LinkList s2 = qb ;
					/*前提条件是*/
					qc->next = qa->next ;//qc的下一个现在是qa的下一个，将qa free.qc位置不变，qa,qb向后移动
					qa = qa->next ;
					qb = qb->next ;
					free(s1);
					free(s2);
				}
				break ;
			case -1:                    //return -1(两项指数qa<qb，qa在前，将其接入qc)
				qc->next = qa ;
				qc = qa ;
				qa = qa->next ;  
				break ;
		}//end switch
	}//end while
	qc->next = qa?qa:qb ;              //插入剩余段
	free(pb);                          //将链表pb的头结点释放
}

/*主函数*/
void main()
{
	/*初始化pa , pb*/
	ploynomial pa ;
	CreateList(pa , 4);               //初始化并创建多项式pa，创建四项
	print(pa);
	
	ploynomial pb ;
	CreateList(pb , 4);
	print(pb);
	
	printf("执行多项式相加之后：\n");
	AddPloyn(pa , pb);
	print(pa);                        //最终由链表pa输出,pb被释放
}