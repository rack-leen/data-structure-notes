/********************************************************************
 *	@program name : LineEdit.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.9
 *	@function     : 栈实现的行编辑
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
*LineEdit     行编辑实现函数
*TraveseStack 遍历栈
*行编辑实现方法：
*如果输入的既不是退格符，也不是退行符，则将该字符压入栈顶；如果是一个
*退格符，则删除前一个字符；如果是退行符，则将字符栈清空。
 ********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "LineEdit.h"

/********************************************************************
 *函数实现
*********************************************************************/
Status InitStack(SqStack *S)
{
  //初始化栈
  S->base = (Elemtype *)malloc(STACK_INIT_SIZE*sizeof(Elemtype));   //为栈分配内存
  if(!S->base) exit(OVERFLOW);                                      //如果分配失败
  S->top = S->base;                                                 //将栈顶与栈基相等，栈置空
  S->stacksize = STACK_INIT_SIZE;                                   //栈长度为初始分配量
  return OK;
}

Status DestroyStack(SqStack *S)
{
  //销毁栈
  S->top = S->base ;
  free(S->base);                                                    //释放栈
  S->top       = NULL;
  S->base      = NULL;
  return OK;
}

Status ClearStack(SqStack *S)
{
  //清空栈
  S->top = S->base;                                                 //清空栈中元素
  return OK;
}

/*
Status EmptyStack(SqStack *S)
{
  //判断栈是否为空
  if(S->top == S->base)
    return TRUE                                                 ;   //也可以用bool
  else
    return FALSE                                                ;
}
*/
/*
Status LengthStack(SqStack *S)
{
  //判断长度
  return S->top - S->base                                       ;   //返回栈顶减去栈基
}
*/
/*Status GetTop(SqStack *S , Elemtype *e)
{
  //得到栈顶元素
  if(S->top == S->base)                                             //先判断栈是否为空，为空，则没有栈顶元素
    return ERROR                                                ;
  *e = *(S->top - 1)                                            ;   //返回栈顶元素（栈顶指针-1）
  return OK                                                     ;
}
*/
Status Push(SqStack *S , Elemtype e)
{
  //插入元素
  if((S->top-S->base)>=S->stacksize)
  {
    S->base = (Elemtype *)realloc(S->base , (S->stacksize+STACK_INCREMENT)*sizeof(Elemtype));
    if(!S->base)
    {
      exit(OVERFLOW);
    }
    S->top = S->base + S->stacksize ;
    S->stacksize += STACK_INCREMENT ;
  }
  *S->top++ = e ;
  return OK ;
}
Status Pop(SqStack *S , Elemtype *e)
{
  //删除元素
  if(S->top == S->base) //如果栈为空
    return ERROR;
    //元a素不为空，则删除
    *e = *--S->top;
  return OK;
}

/*Status TraveseStack(SqStack *S  , Status (*visit)(Elemtype))
{
  Elemtype *b = S->base;
  Elemtype *t = S->top;
 while(b < t)
  {
    visit(*b++);
  }
  printf("\n");
  return OK;
}

Status visit(Elemtype c)
{
  printf("%d",c);   //不能与e相同
  return OK;
}
*/
void LineEdit(SqStack *S)
{
  /*行编辑实现函数*/
  Elemtype *p;
  Elemtype c;
  Elemtype ch;
 ch = getchar();
  //本次循环将输入的数据从缓存区传入数据区
  while(ch != EOF)                                                  //EOF作为全文结束符
  {
    //本次循环将输入的数据存入缓存区
    while(ch != EOF && ch != '\n')
     {
       switch(ch)
       {
          case '#': Pop(S , &c);                                   //仅当栈非空时退栈,遇到#将前面的字符压出栈
                  break;
          case '@': ClearStack(S);                                 //重置S为空栈
                  break;
          default : Push(S,ch);
                  break;
       }
       ch = getchar();                                             //从终端接收下一个字符
    }
    p = S->base ;
    while(p!=S->top)
    {
      printf("%c",*p);
        ++p ;
    }
    ClearStack(S);                                                //清空栈，将数据传入数据区
    if(ch != EOF) ch = getchar();                                 //满足条件下，从栈中取出字符
  }
}

/******************************************************************
 *end
*******************************************************************/
