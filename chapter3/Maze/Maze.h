/********************************************************************
 *	@program name : Maze.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.11
 *	@function     : 迷宫求解
 *	@type         : header file
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
 *定义域
*********************************************************************/
#ifndef _MAZE_H
#define _MAZE_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/********************************************************************
 *定义区
*********************************************************************/
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define STACK_INCREMENT 10					                                //存储空间的分配增量
#define STACK_INIT_SIZE 100                                         //存储空间的初始分配量
#define MAX_ROW         10
#define MAX_COLUMN      10

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status   ;

/********************************************************************
 *结构体
********************************************************************/
//迷宫坐标结构体
typedef struct{
  int x ;
  int y ;
}PosType;
//迷宫类型结构体
typedef struct{
  int ord ;                                                         //通道块在路径上的序号
  PosType seat ;                                                    //通道块在迷宫中的坐标
  int di ;                                                          //从此通道块走向下一通道块的方向(1:东 , 2:西,3:北[顺时针])
}Elemtype;                                                          //栈的元素类型
//栈结构体
typedef struct {                                                     //构建数制转换栈的结构体
	Elemtype *base    ;                                                //栈基指针
	Elemtype *top     ;                                                //栈顶指针
	int stacksize;                                                     //栈长度
}MazeStack;                                                          //栈类型

/********************************************************************
 *迷宫地图
 *0:墙壁 1：通路 MazeMap[1][1]:入口 MazeMap[]8[8]:出口
*********************************************************************/
int MazeMap[MAX_ROW][MAX_COLUMN] =
{
  //0,1,2,3,4,5,6,7,8,9
   {0,0,0,0,0,0,0,0,0,0}, //0
   {0,1,1,0,1,1,1,0,1,0}, //1
   {0,1,1,0,1,1,1,0,1,0}, //2
   {0,1,1,1,1,0,0,1,1,0}, //3
   {0,1,0,0,0,1,1,1,1,0}, //4
   {0,1,1,1,0,1,1,1,1,0}, //5
   {0,1,0,1,1,1,0,1,1,0}, //6
   {0,1,0,0,0,1,0,0,1,0}, //7
   {0,0,1,1,1,1,1,1,1,0}, //8
   {0,0,0,0,0,0,0,0,0,0}  //9
};

/********************************************************************
 *函数的表示
*********************************************************************/

Status InitStack(MazeStack *S);                                      //初始化栈
Status DestroyStack(MazeStack *S);                                   //销毁栈
Status ClearStack(MazeStack *S);                                     //清空栈
Status EmptyStack(MazeStack *S);                                     //判断栈是否为空
Status LengthStack(MazeStack *S);                                    //判断长度
Status GetTop(MazeStack *S , Elemtype *e);                           //得到栈顶元素
Status Push(MazeStack *S , Elemtype e);                              //插入元素，进栈
Status Pop(MazeStack *S , Elemtype *e);                              //删除元素，退栈
Status TraveseStack(MazeStack *S , Status (*visit)(Elemtype e));     //遍历栈
Status visit(Elemtype e);                                            //输出遍历结果
Status MazePath(PosType start , PosType end);                        //迷宫路径
Status Pass(PosType *pos);                                           //通过的位置
void FootPrint(PosType pos);                                       //打印足迹(经过的坐标)
PosType NextPos(PosType curpos , int i);                             //下一个位置
void   MakePrint(PosType pos);                                       //打印最终路径

#endif
