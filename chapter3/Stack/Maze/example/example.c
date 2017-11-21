/***************************************************************************************
 *  @file       example.c
 *
 *  @brief      Brief descriptinon of example.c
 *
 *  @date       2017-11-11 21:39
 *
 ***************************************************************************************/

#include "example.h"

//函数实现

/*构造一个空栈*/
void InitStack(SqStack *S)
{
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);

    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
}

/*判断一个栈是否为空栈,是返回1，不是返回0*/
Status StackEmpty(SqStack *S)
{
    if(S->base==S->top)
        return 1;
    else
        return 0;
}

/*插入e为新的栈顶元素*/
void Push(SqStack *S ,SElemType e)
{
    if((S->top-S->base)>=S->stacksize)
    {
        S->base=(SElemType*)realloc(S->base,(S->stacksize+STACK_INCREMENT)*sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);

        S->top=S->base+S->stacksize;
        S->stacksize+=STACK_INCREMENT;
    }
    *S->top++=e;
  }

/*若栈不为空，则用e删除栈顶元素，并返回OK，否则返回ERROR*/
Status Pop(SqStack *S ,SElemType *e)
{
    if(S->top==S->base)
        return ERROR;

    *e = *--S->top;
    return OK;
}

/*输出走迷宫的路径*/
void FootPrint()
{
    int i,j;
    for(i=0;i<MAX_ROW;i++)
    {   //打印迷宫中留下的足迹
        for(j=0;j<MAX_COLUMN;j++)//i,j为走过的坐标
            printf("%d ",a[i][j]);  //空格为了观看方便
        printf("\n");
    }
}

/*求当前位置的下一步*/
void NextStep(Pos *seat ,int di)
{
    Pos direction[4]={{0,1},{1,0},{0,-1},{-1,0}};  //方向依次为东南西北

    seat->x+=direction[di].x;  //di为方向，朝的方向的x坐标
    seat->y+=direction[di].y;  //不知道为什么x,y不是结构体或者联合体（头文件是申明了的）
} //原来如此，编译器规定*seat必须用seat->x ,而seat只需要用seat.x

/*搜寻迷宫路径，只能搜索一条路径，且不一定是最优路径*/
/*若能求得一条路径则返回TURE，否则返回FALSE*/
Status Path(Pos Begin ,Pos End)
{
	SqStack S;
    Pos CurPos;
    SElemType e;
    InitStack(&S);
    CurPos=Begin;  //将最初位置设定为入口

    do
    {
        if(a[CurPos.x][CurPos.y]==0)  //此时的位置为通路
        {
            a[CurPos.x][CurPos.y]=curstep;
            e.ord=curstep;  //探索步数
            e.seat=CurPos;  //当前坐标
            e.di=0;         //方向

            Push(&S,e);  //压入栈
            curstep++;  //步数+1

            if(CurPos.x==End.x&&CurPos.y==End.y) //已经到了终点
                return TRUE;

            NextStep(&CurPos,e.di);  //下一步
        }  //if(a[CurPos.x][CurPos.y]==0) end
        else  //当前位置不能通过，选择其他方向
        {
            if(!StackEmpty(&S))
            {
                Pop(&S,&e);  //出栈
                curstep--;  //步数-1
                while(e.di==3&&!StackEmpty(&S))//3为最后一个方向
                {
                    a[e.seat.x][e.seat.y]=-1;
                    Pop(&S,&e);
                    curstep--;
                }  //while(e.di==3&&!StackEmpty(S)) end
                if(e.di<3)
                {
                    e.di++;
                    Push(&S,e);
                    curstep++;
                    CurPos=e.seat;
                    NextStep(&CurPos,e.di);
                }  //if(e.di<3)
            }  //if(!StackEmpty(S)) end
        }  //else end
    } while(!StackEmpty(&S)); //do end
    return FALSE;
}

//gcc编译如下，无能为力
// /tmp/ccNhwYR0.o:(.data+0x0): `a'被多次定义
// /tmp/ccj0dGSS.o:(.data+0x0)：第一次在此定义
// /tmp/ccNhwYR0.o:(.data+0xc8): `Begin'被多次定义
// /tmp/ccj0dGSS.o:(.data+0xc8)：第一次在此定义
// /tmp/ccNhwYR0.o:(.data+0xd0): `End'被多次定义
// /tmp/ccj0dGSS.o:(.data+0xd0)：第一次在此定义
// /tmp/ccNhwYR0.o:(.data+0xd8): `curstep'被多次定义
// /tmp/ccj0dGSS.o:(.data+0xd8)：第一次在此定义
// collect2: error: ld returned 1 exit status
