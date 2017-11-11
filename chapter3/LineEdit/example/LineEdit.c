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

//函数实现
int InitStack(SqStack *S)
{
  //初始化栈
  S->base = (Elemtype *)malloc(STACK_INIT_SIZE*sizeof(Elemtype));
  if(!S->base) exit(OVERFLOW);
  S->top = S->base ;
  S->stacksize = STACK_INIT_SIZE ;
  return OK ;
}

int ClearStack(SqStack *S)
{
  //清空栈
  S->top = S->base ;
  return OK ;
}

int DestroyStack(SqStack *S)
{
  //销毁栈
  S->top = S->base;
  free(S->base);
  S->top = NULL ;
  S->base = NULL ;
  return OK ;
}

int Push(SqStack *S , Elemtype e)
{
  //入栈
  if((S->top-S->base)>=S->stacksize) //栈满
  {
    S->base = (Elemtype *)realloc(S->base,(STACK_INCREMWNT+S->stacksize)*sizeof(Elemtype));
    if(!S->base) exit(OVERFLOW) ;
    S->top = S->base + S->stacksize ;
    S->stacksize += STACK_INCREMWNT ;
  }
  *S->top++ = e;
  return OK ;
}


int Pop(SqStack *S , Elemtype *e)
{
  //退栈
  if(S->top == S->base) return ERROR ;
  *e = *--S->top ;
  return OK ;
}

void LineEdit(SqStack *S)
{
  //行编辑程序
  Elemtype *p , ch , c ;
  InitStack(S);
  ch = getchar();
  while(ch != EOF)
  {
    while(ch != EOF && ch != '\n')
    {
      switch(ch)
      {
        case '#': Pop(S , &c);
                  break ;
        case '@': ClearStack(S);
                  break ;
        default : Push(S , ch);
                  break ;
      }
      ch = getchar();
    }
    p = S->base ;
    while(p!=S->top)  //输出栈中元素
    {
      printf("%c",*p);
      ++p ;
    }
    ClearStack(S);
    if(ch != EOF) ch = getchar();
  }
}
