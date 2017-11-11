/********************************************************************
 *	@program name : Maze.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.11
 *	@function     : 迷宫求解
 *	@type         : source file
*********************************************************************/

/********************************************************************
*基本操作
*InitStack    初始化栈
*DestroyStack 销毁栈
*ClearStack   清空栈
*EmptyStack   判断栈是否为空
*LengthStack  返回栈长度
*GetTop       得到栈顶元素
*Push         插入元素 进栈
*Pop          删除元素 退栈
*Maze         迷宫求解方法
*TraveseStack 遍历栈
*visit        输出遍历结果
*MazePath     迷宫路径
*Pass         通过的位置
*FootPrint    打印足迹
*NextPos      下一位置
*MakePrint    打印最终位置
*迷宫求解实现方法：穷举求解
*从入口出发，顺某一方向前进，若能走通，继续往前走；否则沿路退回，换一个方
*向继续探索，直至所有可能的通路都探索完为止。
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "Maze.h"

/********************************************************************
 *函数实现
*********************************************************************/
Status InitStack(MazeStack *S)
{
    //初始化栈
    S->base = (Elemtype *)malloc(STACK_INIT_SIZE*sizeof(Elemtype));  //分配动态内存
    if(!S->base) exit(OVERFLOW);                                     //分配失败
    S->top = S->base ;               //初始化栈顶等于栈基
    S->stacksize = STACK_INIT_SIZE ; //初始化栈长度等于初始分配量
    return OK ;
}

Status DestroyStack(MazeStack *S)
{
  //销毁栈
  S->top = S->base ; //使栈长度为0
  free(S->base) ;//释放栈
  S->top = NULL ;//栈顶为空
  S->base = NULL ;//栈基为空
  return OK ;
}

Status ClearStack(MazeStack *S)
{
  //清空栈
  S->top = S->base ; //栈长度为0
  return OK ;
}

Status EmptyStack(MazeStack *S)
{
  //判断栈空
  if(S->top == S->base) return TRUE ; //如果空返回TRUE
  else return FALSE ;
}

Status LengthStack(MazeStack *S)
{
  //返回栈长度
  return S->top - S->base ; //返回栈长度
}

Status GetTop(MazeStack *S , Elemtype *e)
{
  //得到栈顶元素
  if(S->top == S->base) return ERROR ;
  *e = *(S->top-1);          //返回栈顶元素
  return OK ;
}

Status Push(MazeStack *S , Elemtype e)
{
  //入栈
  if((S->top-S->base)>=S->stacksize) exit(OVERFLOW);   //判断栈是否满栈
  {
    S->base = (Elemtype *)realloc(S->base , (S->stacksize+STACK_INCREMENT)*sizeof(Elemtype)); //追加存储空间
    if(!S->base) exit(OVERFLOW);
    S->top = S->base + S->stacksize ;
    S->stacksize += STACK_INCREMENT ;
  }
  *S->top++ = e ;
  return OK ;
}

Status Pop(MazeStack *S , Elemtype *e)
{
  //退栈
  if(S->top == S->base) return ERROR ;
  *e = *--S->top ;
  return OK ;
}

Status MazePath(PosType start , PosType end)
{
  PosType curpos ;         //当前位置，坐标，x,y
  MazeStack S ;            //栈
  Elemtype e ;            //迷宫类型，坐标，序号，方向
  int curstep ;           //探索步数
  InitStack(&S);          //初始化栈
  curpos = start ;        //设置当前入口位置为start
  curstep = 1 ;           //探索第一步
  printf("起点：（%d,%d）",start.x , end.y); //输入起点
  do
  {
      if(Pass(&curpos)) //当前位置可以通过
      {
        FootPrint(curpos); //留下足迹
        e.ord = curstep ;   //探索步的序号，步数
        e.seat = curpos ;  //当前位置
        e.di = 1 ;          //所走的方向1为东方
        Push(&S , e);       //加入路径
        if(curpos.x == start.x && curpos.y == end.y ) //当前位置是终点
        {
          printf("\n终点：(%d,%d)", start.x , end.y); //打印终点
          return TRUE ; // 到达终点
        }
        curpos = NextPos(curpos , e.di); //下一个位置是当前位置的东部
        ++curstep  ; //探索下一步
      }
      else //当前位置不能通过
      {
        if(!EmptyStack(&S)) //不为空
        {
          Pop(&S,&e);    //将当前位置退栈
          while(e.di == 4 && !EmptyStack(&S)) //顺时针转动方向，到最后一个方向
          {
              MakePrint(e.seat); //留下不能通过的坐标的标记
              Pop(&S , &e); //将这个坐标退栈
              printf("倒退到：(%d,%d)", e.seat.x , e.seat.y);//倒退到不能通过之前的位置
          }
          if(e.di < 4)  //表示可以换下一个方向通过
          {
            ++e.di;     //寻找下一个方向
            Push(&S , e);//将当前位置压入栈
            curpos = NextPos(e.seat , e.di); //设当前位置为该新方向上的相邻块
          }
        }
      }
  }while(!EmptyStack(&S));
  return FALSE;
}

Status Pass(PosType *pos)
{
  //通过的位置
  if(MazeMap[pos->y][pos->x]==0)//地图中的当前位置为开始
    return FALSE ;
  printf("(%d,%d)", pos->y ,pos->x); //打印当前通过的位置
  return TRUE ;
}

void FootPrint(PosType pos)
{
  //留下足迹
  MazeMap[pos.y][pos.x] = 2 ;//将走过的路径设置为2（0为墙,1为通路）
}

PosType NextPos(PosType curpos , int i)
{
  //下一个位置
  switch (i)   //i为方向
  { //东方为x轴的正方向，南方为y轴的正方向
    case 1 :
      ++curpos.x; //东边通,向东（x++）
      if(MazeMap[curpos.y][curpos.x]!=2)  //当前位置没有留下足迹,表示走不通
        break ;//停止向东
      --curpos.x ; //否则向西,x--
    case 2 :
      i = 2;
      ++curpos.y; //南通，向南（y++）
      if(MazeMap[curpos.y][curpos.x]!=2)//走不通
        break ; //停止向南
      --curpos.y ;//否则向北，y--
    case 3 :
      i = 3;
      --curpos.x; //向西，与正方向反向
      if(MazeMap[curpos.y][curpos.x]!=2)
        break ;
      ++curpos.x ;
    case 4 :
      i = 4 ;
      --curpos.y ;//向北，与正方向反向
      if(MazeMap[curpos.y][curpos.x]!=2)
      {   //最后一个方向，也行不通则表示走不通
          ++curpos.y;
          MazeMap[curpos.y][curpos.x]=0;
      }
      break ;
  }
  return curpos ;        //返回得到的下一个位置
}

void MakePrint(PosType pos)
{ //留下不能通过的标记
  printf("\n(%d,%d)走不通！",pos.y , pos.x );
  MazeMap[pos.y][pos.x]=0 ;
}

/********************************************************************
 *end
*********************************************************************/
