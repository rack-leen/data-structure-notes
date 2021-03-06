/********************************************************************
 *	@program name : Hanoi.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.21
 *	@function     : 汉诺塔递归
 *	@type         : source file
*********************************************************************/

/********************************************************************
*基本操作
*Hanoi  汉诺塔实现函数
*move   移动圆盘
*实现原理：
*通过递归，
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "Hanoi.h"

/********************************************************************
 *函数实现
*********************************************************************/
void Hanoi(int n , char x , char y , char z)
{
  //汉诺塔函数表示
  if(n == 1) //如果只有一个盘子
    move(x , 1 , z); //直接进行x移至z的操作
  else
  {   //分为三部分
      Hanoi(n-1 , x , z , y); //把x上的前n-1个圆盘借助z，移至y z辅助塔
      move(x , n , z); //把x上的第n个圆盘移至z
      Hanoi(n-1 , y , x , z);//再把y上的前n-1个圆盘借助x，移至z x辅助塔
  }
}

void move(char x , int n , char z)
{
  //移动汉诺塔的函数
  step++ ;                    //统计步数
  printf("第%d步：第%d个圆盘 %c --> %c\n" , step , x , z);
}
