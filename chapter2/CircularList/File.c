#include<stdio.h>
#include<stdlib.h>
//线性表的循环链表分配顺序存储结构
#define LIST_INIT_SIZE 100//线性表存储空间的初始分配量
#define LISTINCREMENT 10//线性表存储空间的分配增量
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;//Status是函数的类型，其值是函数结果状态代码
typedef int ElemType;
//线性表的循环链表动态分配顺序存储结构
typedef struct CircleNode{
    ElemType data;//存储空间基址
    struct CircleNode *next;
}CircleNode,*CircleLinkList;
Status InitList_CL(CircleLinkList &L)
{
    //操作结果：返回一个空的线性表L
    L=(CircleLinkList)malloc(sizeof(struct CircleNode));//产生头结点,并使L指向此头结点
    if(!L)               //没有头结点，表示链表为空
        return OVERFLOW;//存储分配失败
    L->next=L;//指针域指向头结点
    printf("初始化线性表成功\n");
    return OK;
}//InitList_CL
//销毁线性表L
Status DestroyList_CL(CircleLinkList &L)
{
    CircleLinkList p=L,q=L->next;
    while(p!=L)//循环一直到表尾
    {
        p->next=q->next;
        free(q);
        q=p->next;
    }
    free(L);
    L=NULL;
    printf("销毁线性表成功\n");
    return OK;
}//DestroyList_CL
Status ClearList_CL(CircleLinkList &L)
{
    //初始条件：线性表L已存在。操作结果：将L重置为空表
    CircleLinkList p=L,q=L->next;//p 指向头结点,q指向第二个节点
    while(p!=L)
    {
        p->next=q->next;
        free(q);
        q=p->next;
    }
    printf("清空线性表成功\n");
    return OK;
}//ClearList_CL
Status ListEmpty_CL(CircleLinkList L)
{
    //初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE
    CircleLinkList p=L->next;
    if(p==L)
        return TRUE;
    else
        return FALSE;
}//ListEmpty_CL
Status ListLength_CL(CircleLinkList L)
{
    //初始条件：L已存在。操作结果：返回L中数据元素个数
    CircleLinkList p=L,q=L->next;
    int i=0;
    while(q!=L)
    {
        ++i;
        q=q->next;
    }
    return i;
}//ListLength_CL
Status GetElem_CL(CircleLinkList L,int i,ElemType &e)
{
    //当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
    CircleLinkList p=L,q=L->next;
    int j=1;
    if(i<1||i>ListLength_CL(L))return ERROR;
    while(j<i)
    {
        ++j;
        q=q->next;
    }
    e=q->data;
    return OK;
}//GetElem_CL
Status LocateElem_CL(CircleLinkList L,ElemType &e,Status (*compare)(ElemType,ElemType))
{
    //初始条件：线性表L已存在，compare()是数据元素判定函数
    //操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。
    //    若这样的数据元素不存在，则返回值为0
    int i=0;
    CircleLinkList p=L->next;
    while(p!=L)
    {
        ++i;
        if((*compare)(p->data,e))
        {
            return i;
        }
        p=p->next;
    }
}//LocateElem_CL
Status compare(ElemType e1,ElemType e2)
{
    if(e1==e2)
        return OK;
}
Status PriorElem_CL(CircleLinkList L,ElemType cur_e,ElemType &pre_e)
{
    //初始条件：线性表L已存在
    //操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱
    //否则操作失败，pre_e无定义
    CircleLinkList p=L->next;
    while(p&&p->next&&p->next!=L)
    {
        if(p->next->data==cur_e)
        {
            pre_e=p->data;
            return TRUE;
        }
        p=p->next;
    }
    return ERROR;
}
//PriorElem_CL
Status NextElem_CL(CircleLinkList L,ElemType cur_e,ElemType &next_e)
{
    // 初始条件：线性表L已存在
    // 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继
    // 否则操作失败，next_e无定义
    CircleLinkList p=L->next;
    while(p&&p->next&&p->next!=L)
    {
        if(p->data==cur_e)
            next_e=p->next->data;
        return TRUE;
    }
    return ERROR;
}//NextElem_CL
Status ListInsert_CL(CircleLinkList &L,int i,ElemType e)
{
    //在L的第i个位置之前插入元素e
    int j=0;
    CircleLinkList q=L;
    if(i<1||i>ListLength_CL(L)+1)return ERROR;
    while(j<i-1)
    {
        ++j;
        q=q->next;
    }
    CircleLinkList s=(CircleLinkList)malloc(sizeof(struct CircleNode));
    s->data=e;
    s->next=q->next;
    q->next=s;
    return OK;
}//ListInsert_CL
Status LinkDelete_CL(CircleLinkList &L,int i,ElemType &e)
{
    //删除L的第i个元素,并由e返回其值
    int j=0;
    CircleLinkList q=L,p;
    if(i<1||i>ListLength_CL(L))return ERROR;
    while(j<i-1)
    {
        ++j;
        q=q->next;
    }
    p=q->next;
    q->next=p->next;
	/*e = q->data*/                                        //应该是少了这个吧
    free(p);
}//LinkDelete_CL
Status ListTraverse_CL(CircleLinkList L,Status (*visit)(ElemType e))
{
    CircleLinkList p=L->next;
    printf("线性表遍历结果:");
    while(p!=L)
    {
        if((*visit)(p->data))
            printf("%d,",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}//ListTraverse_CL
Status visit(ElemType e)
{
    return OK;
}
int main(void)
{
    CircleLinkList L;
    ElemType e,pre_e,next_e;
    InitList_CL(L);
    ListInsert_CL(L,1,1);
    ListInsert_CL(L,2,2);
    ListTraverse_CL(L,visit);
    if(!ListEmpty_CL(L))
        printf("线性表不为空\n");
    GetElem_CL(L,1,e);
    printf("线性表第1个元素为:%d\n",e);
    printf("线性表元素为1的位序为:%d\n",LocateElem_CL(L,e,compare));
    PriorElem_CL(L,2,pre_e);
    printf("线性表元素为2的前驱为:%d\n",pre_e);
    NextElem_CL(L,1,next_e);
    printf("线性表元素为1的后继为:%d\n",next_e);
    //printf("线性表删除位序1后:");
    LinkDelete_CL(L,1,e);
    ListTraverse_CL(L,visit);
    ClearList_CL(L);
    DestroyList_CL(L);
    getchar();
    getchar();
    return 0;
}
