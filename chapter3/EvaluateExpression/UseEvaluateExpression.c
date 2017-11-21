/********************************************************************
 *	@program name : UseEvaluateExpression.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.11
 *	@function     : 表达式求值
 *	@type         : main file
*********************************************************************/

/********************************************************************
*基本操作
*InitStackChar 初始化运算符栈
×InitStackFloat初始化运算数栈
*GetTopChar   得到运算符栈顶元素
*GetTopFloat  得到运算数栈顶元素
*PushChar     把字符压栈
*PushFloat    把数值压栈
*PopChar      把字符退栈
*PopFloat     把数值退栈
*Operate(a,theta,b) 根据theta对a和b进行'+' 、'-' 、'*' 、'/' 、'^'操作
*In(Test,*TestOp) 若Test为运算符则返回true，否则返回false
*ReturnOpOrd(op,*TestOp) 若Test为运算符，则返回此运算符在数组中的下标
*precede(Aop,Bop) 根据运算符优先级表返回Aop与Bop之间的优先级
*EvaluateExpression(*MyExpression) 用算符优先法对算术表达式求值
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "EvaluateExpression.h"

/********************************************************************
 *主函数
*********************************************************************/
int main()
{
  char s[1001]; //输入的表达式
  long long result ; //输出的结果
  while(gets(s)) //用gets函数输入单个的字符
  {
    result = (long long)EvaluateExpression(&s);
    printf("结果是：%d\n", result);
    printf("继续输入！\n");
  }
  return 0 ;
}
