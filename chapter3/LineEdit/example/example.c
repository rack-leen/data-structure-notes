/************************************************************************************//**
 *  @file       example.c
 *
 *  @brief      Brief descriptinon of example.c
 *
 *  @date       2017-11-11 11:17
 *
 ***************************************************************************************/
#include "LineEdit.h"
int main()
{
  //主函数
  SqStack s ;
  int f ;
  printf("请用户输入文本：\n");
  LineEdit(&s);
  DestroyStack(&s);
  return 0 ;
}
