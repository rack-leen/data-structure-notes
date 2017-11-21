/*********************************************************************
*	@program name: stack  
*	@author name : rack
*	@mail	     : 1740234864@qq.com
*	@last date   : 2017.11.2
*	@function    : 栈的顺序存储主函数
**********************************************************************/
#include <stdio.h>
#include "SqStack.h"

int main()
{
	/*变量区*/
	SqStack   a;
	SqStack *s = &a;
	SElemtype e;
	InitStack(s);                                                 //初始化
	int n;
	/*输入区*/
	printf("请输入进栈的个数：");    
	scanf("%d",&n);

	/*数据区*/
	while(n--)                                                    
	{
		int m ; 
		scanf("%d",&m);                                      //输入插入的元素
		Push(s , m);                                         //插入元素
	}

	TraverseStack(s , visit);	
	printf("\n");
	printf("8进栈后：");
	Push(s , 8);
	
	TraverseStack(s , visit);
	printf("\n");
	Pop(s , &e);
	
	printf("出栈的元素：%d\n", e);
	printf("出栈的元素是%d.\n",*s->top);                         //判断出栈的元素是否再内存中
	DestroyStack(s);
	return 0 ;
}
