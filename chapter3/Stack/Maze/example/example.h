/***************************************************************************************
 *  @file       example.h
 *
 *  @brief      Brief descriptinon of example.h
 *
 *  @date       2017-11-11 21:39
 *
 ***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAX_ROW 7  //迷宫最大行数
#define MAX_COLUMN 7  //迷宫最大列数
#define STACK_INIT_SIZE 10
#define STACK_INCREMENT 2

typedef int Status ;
typedef struct{  //迷宫坐标位置
    int x;
    int y;
}Pos;

typedef struct{  //栈的元素
    int ord;  //路径上的序号
    Pos seat;  //坐标位置
    int di;  //下一步行走的方向
}SElemType;

typedef struct{  //栈
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

/*用数组表示数据结构书中的迷宫，1表示墙壁，0表示通道*/
int a[MAX_ROW][MAX_COLUMN] = {
    {2, 2, 2, 2, 2, 2, 2},
    {2, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 2, 0, 2, 2},
    {2, 2, 0, 2, 0, 2, 2},
    {2, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2}
};

Pos Begin={1,1},End={5,5};  //设定迷宫入口和出口
int curstep=1;  //步数
SqStack S;  //定义一个全局顺序栈

//函数原型

//void InitStack(SqStack *S);  //初始化栈
Status StackEmpty(SqStack *S) ; //判断栈空
//void Push(SqStack *S ,SElemType e);  //入栈
Status Pop(SqStack *S ,SElemType *e)  ; //退栈
//void FootPrint();  //留下足迹
//void NextStep(Pos *seat ,int di) ;  //下一步
Status Path(Pos Begin ,Pos End)  ; //探索路径
