/********************************************************************
 *	@program name : SquenceString.c
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.27
 *	@function     : 顺序串
 *	@type         : source file
*********************************************************************/

/********************************************************************
 *基本操作
 *StrAssign     生成一个子串T
 *StrCopy       由串S复制得到串T
 *StrEmpty      判断串是否为空
 *StrCompare    串比较
 *StrLength     串长度
 *ClearString   清空串
 *SubString     返回主串的第pos个字符串起长度为len的子串
 *Index         返回S中第pos个字符第一次出现的位置
 *ConCat        返回两个串连接成的新串
 *Replace       替换主串中与T子串相等的不重叠的子串
 *StrInsert     在主串中插入子串T
 *StrDelete     在主串中删除第pos个字符起的len长度的子串
 *DestroyString 销毁串
 *StrPrint      字符串打印
*********************************************************************/

/********************************************************************
 *头文件
*********************************************************************/
#include "SquenceString.h"

/********************************************************************
 *函数实现
*********************************************************************/
Status StrAssign(SString T , const char *chars)                     //生成一个值为chars的T,属于最小操作子集
{
   int i . len ;
   len = strlen(chars) ;                    //chars字符串的长度
   if(len > MAXSTRLEN)  //len大于最大字符长度
      return ERROR ;
    else
    {
      T[0] = len ; //字符串的第一位存储字符串长度
      for(i=1 ; i <= len ; i++)
        T[i]=chars[i-1];   //T[0]存储的是字符串长度，所以需要从1开始，而chars为数组，从0开始所以i-1
      return OK ;
    }
}

Status StrCopy(SString S , SString T)
{
  int i ;
  for(i = 0 ; i <= S[0] ; i++) //S[0]存储的是字符串长度,见头文件自定义类型
    T[i] = S[i] ;                 //将S字符串复制给T串
  return OK ;
}

Status StrEmpty(SString S)
{
  //判断字符串是否为空
  if(S[0] == 0)
    return TRUE ;
  else
    return FALSE ;
}

Status StrCompare(SString S , SString T) //属于最小操作子集
{
  //比较S , T 两个字符串
  //原理,比较S,T，在i时相等则+1，表示匹配，否则将匹配后的字符串删除，重新匹配，直到完全配对
  int i ;
  while(i<=S[0] && i <= T[0])
  {
    if(S[i]==T[i])   //在第i位置S[i]与T[i]匹配
     i++ ;           //开始下一位置匹配
    else
      return S[i]-T[i]; //返回未匹配成功的位置
  }
  return S[0]-T[0]; //S串长度减去T串长度
}

Status StrLength(SString S)
{
  return S[0];
}

Status ClearString(SString S)
{
  S[0] = 0 ;
  return OK ;
}

Status ConCat(SString T , SString S1 , SString S2)
{
  //将S1与S2连接，并放入T串
  int i ;
  for(i = 1 ; i <= S1[0] ; i++)
    T[i] = S1[i];
  if(S1[0]+S2[0] <= MAXSTRLEN)
  { //两个串长度相加在总串长度之内，则将所有串字符连接入 T
    for(i = 1 ; i <= S2[0] ; i++)
      T[S1[0]+1] = S2[i];    //+1是因为S2[0]为存储S2长度的
    T[0] = S1[0] + S2[0] ;  //T的长度等于两个串的长度相加
    return OK ;
  }
  else
  { //两个串连接后的长度大于最大长度，所以S2串不能连接完全，只能将i个S2串的字符连接到S1后面
    //（这里不需要S2[0]可能是因为没有连接完全，不能表示S2长度）
    for(i = 1 ; (S1[0]+i) <= MAXSTRLEN ; i++)
      T[S[0]+i] = S2[i]; //将i个S2中的字符串复制到T中
    T[0] = MAXSTRLEN ;  //T的总长度正好为最大长度
    return ERROR ;
  }
}

Status SubString(SString Sub , SString S , int pos , int len)
{
  //用sub返回S串中第pos个字符起长度为len的子串
  if(pos<1 || pos > S[0] || len < 0 || (pos+len-1)>S[0])  //第pos位置小于1（0为长度位）大于长度，len小于0，
      return ERROR ; //第pos位置+其后len长度-1大于总长度（-1表示为数组从0开始）
  for(i = 1 ; i <= len ; i++)
  {
    Sub[i] = S[pos+i-1] ;           //从pos位置开始循环，-1表示数组从0开始
  }
  Sub[0] = len ;    //Sub长度等于len
  return OK ;
}

int Index(SString S ,SString T , int pos)
{
  //如果主串中第pos字符后存在与T串相等的子串，则返回这个子串在主串中的位置
  int s ,t ;
  SString Sub ;

  if(pos > 0)
  {
    s = StrLength(S);  //S串长度
    t = StrLength(T);  //T串长度

    if(s&&t)
    {
      while(pos+t<=s)  //第pos位置起加上t串长度小等于s串长度
      {
        SubString(Sub , s , pos ,t); //返回子串
        if(!StrCompare(Sub , T))  //比较不成功，返回子串在主串的位置
          return pos ;
        pos++ ;  //比较成功，pos位置+1
      }
    }
  }
  return 0 ;
}

Status Replace(SString S ,SString T , SString V)
{
  //用V替换在主串S中出现的所有T子串
  
}
