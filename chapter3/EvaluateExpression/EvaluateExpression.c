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
  strcpy(TempData , "\0");            //将"\0"复制给TempData，表示字符串起始(给TempData赋值空，初始化)

  while(*c!='#'|| GetTopChar(OPTR)!='#') //表达式的最后没有传入起始符#或者运算符栈顶没有传入起始符#相当于括号
  {
    //将运算符和运算符分别压入栈
    if(!In(*c , &OPSET)) //如果*c存储的不是运算符，则进栈
    {
      Dr[0] = *c ;  //*c表示输入的表达式字符,表达式是字符一个个输入的
      Dr[1] = '\0';
      strcat(TempData , Dr); //将Dr连接到TempData，将字符一个个链接到TempData中，TempData中全是运算数
      c++ ; //继续接收字符
      if(In(*c , OPSET)) //再将表达式带入判断，如果接收到一个运算符，从TempData中将运算数压入栈
      {
        Data = (float)atof(TempData); //将TempData中的运算数字符转换为浮点数
        PushFloat(OPND , Data);   //将浮点数入运算数栈
        strcpy(TempData , "\0"); //将TempData赋值为空，因为TempData中的数已经入栈
      }
    }
    else  //是运算符则进栈
    {
      switch (precede(GetTopChar(OPTR),*c)) //得到的栈顶运算符与表达式中运算符比较优先级
      {
        case '<':  //栈顶运算符优先级低
              PushChar(&OPTR , *c); //将c压入栈
              c++ ;
              break ;
        case '=': //优先级相等
              PopChar(&OPTR . &x);//优先级相等，则脱括号
              c++ ; //接收下一个字符
              break ;
        case '>':  //栈顶优先级高，则退栈
              PopChar(&OPTR , &theta);//运算符退栈
              PopFloat(&OPND , &a); //运算数a退栈
              PopFloat(&OPND , &b); //运算数b退栈
              PushFloat(&OPND , Operate(a , theta , b)); //将运算结果压入OPND栈
              break ;
      }//switch
    }//if
  }//while
  return GetTopFloat(&OPND); //返回得到的运算结果栈
}//EvaluateExpression

float Operate(float a ,char theta , float b)
{
  //对a,b实行加减乘除
  switch (theta)   //theta为运算符
  {
    case '+': return a+b ;
    case '-': return a-b ;
    case '*': return a*b ;
    case '/': return a/b ;
    default : return 0 ;
  }
}

Status ReturnOpOrd(char Op , char *TestOp )
{
  //返回Op在数组TestOp中的下标
  int i ;
  for(i = 0 ; i < OPSETSIZE ; i++)
  {
    if(Op == TestOp[i]) //如果Op与TestOp数组中的一个元素相等，则返回这个下标
      return i ;
  }
  return 0 ;
}

Status In(char Test , char *TestOp)
{
  //判断是否为运算符
  bool Find = false ; //Find初始定义
  int i ;
  for(i = 0 ; i < OPSETSIZE ; i++)
  {
    if(Test == TestOp[i]) Find = true ; //如果输入的字符是TestOp中的运算符，则返回ture
  }
  return 0 ;
}

char precede(char Aop , char Bop)
{
  //返回两个运算符的优先级
  return Prior[ReturnOpOrd(Aop , OPSET)][ReturnOpOrd(Bop , OPSET)]; //返回运算符之间的优先关系
}

atof(char *snum)
{
  //将字符串转换为浮点数
  int l = strlen(snum),i = 1 , sum = snum[i-1]-'0'; //最后一个是将字符串转换为数组
  l-- ;
  while(l--)
  {
    i*=10 ;
    sum+=(snum[i-1]-'0')*i ;
  }
  return sum ; //返回转换的浮点数
}
