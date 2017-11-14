/********************************************************************
 *	@program name : EvaluateExpression.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.12
 *	@function     : 表达式求值
 *	@type         : source file
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
 *函数实现
*********************************************************************/
void InitStackChar(StackChar *S)
{
  //初始化运算符栈,void没有返回值
  S->base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
  if(!S->base) exit(OVERFLOW);
  S->top = S->base ;
  S->stacksize = 0 ;
}

void InitStackFloat(StackFloat *S)
{
  //初始化运算数栈
  S->base = (float *)malloc(STACK_INIT_SIZE*sizeof(float));
  if(!S->base) exit(OVERFLOW);
  S->top = S->base ;
  S->stacksize = 0 ;
}

char GetTopChar(StackChar *S)
{
  //得到运算符栈的栈顶元素
  return *(S->top-1);      //返回栈顶元素
}

float GetTopFloat(StackFloat *S)
{
  //得到运算数的栈顶元素
  return *(S->top-1);   //返回栈顶元素
}

void PushChar(StackChar *S , char e)
{
  //运算符入栈
  *S->top++ = e ;           //将输入的e赋值给栈顶
}

void PushFloat(StackFloat *S , float e)
{
  //运算数入栈
  *S->top++ = e ;         //将输入的运算数赋值给栈顶
}

void PopChar(StackChar *S , char *e)
{
  //运算符出栈
  *e = *--S->top ;
}

void PopFloat(StackFloat *S , float *e)
{
  //运算数出栈
  *e = *--S->top ;
}

char EvaluateExpression(char *MyExpression)
{
  //表达式求值函数
  StackChar  OPTR ;                    //运算符
  StackFloat OPND ;                    //运算数
  char TempData[20];                   //支持的整数位数
  float Data , a , b;
  char *c , Dr[2] , theta ;

  InitStackChar(OPTR);                //初始化运算符
  PushChar(OPTR , '#');               //将#压入运算符栈，给运算栈赋值空(初始化)
  InitStackFloat(OPND);               //初始化运算数
  c = MyExpression ;                  //将输入的表达式传入c
  strcpy(TempData , "/0");            //将"\0"复制给TempData，表示字符串起始(给TempData赋值空，初始化)

  while(*c!='#'|| GetTopChar(OPTR)!='#') //表达式的最后没有传入起始符#或者运算符栈顶没有传入起始符#
  {
    if(!In(*c ,OPSET)) //如果*c存储的不是运算符，则进栈
    {
      Dr[0] = *c ;  //*c表示输入的表达式字符
      Dr[1] = '/0';
      strcat(TempData , Dr); //将Dr连接到TempData
      c++ ; //继续接收字符
      if(In(*c , OPSET)) //如果是运算数
      {
        Data = (float)atof(TempData); //将TempData中的运算数字符转换为浮点数
        PushFloat(OPND , Data);   //将浮点数入运算数栈
        strcpy(TempData , "/0"); //将TempData赋值为空，因为TempData中的数已经入栈
      }
    }
  }
}
