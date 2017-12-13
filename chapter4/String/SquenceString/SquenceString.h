/********************************************************************
 *	@program name : SquenceString.h
 *	@author  name : rack
 *	@my      mail : 1740234864@qq.com
 *	@last    date : 2017.11.27
 *	@function     : 顺序串
 *	@type         : header file
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
 *定义域
*********************************************************************/
#ifndef _SQUENCESTRING_H
#define _SQUENCESTRING_H

/********************************************************************
 *头文件
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************************
 *状态码
*********************************************************************/
#define TURE       1
#define FALSE      0
#define OK         1
#define ERROR      0
#define OVERFOLW   -2
#define INFEASINLE -1
#define MAXSTRLEN  255   //顺序串最大长度

/********************************************************************
 *自定义类型
*********************************************************************/
typedef int Status ;                                                //状态识别码类型,因为Status接受的时return返回值，return返回值为状态码
typedef unsigned char SString[MAXSTRLEN+1] ;                        //从1开始，第0个存储字符串长度

/********************************************************************
 *函数表示
*********************************************************************/
Status StrAssign(SString T , const char *chars);                    //生成一个值等于常量chars的串T
Status StrCopy(SString T , SString S);                              //由串S复制得到T
Status StrEmpty(SString S);                                         //判断串S是否为空
Status StrCompare(SString S ,SString T);                            //比较S串和T串
Status StrLength(SString S);                                        //返回S的长度
Status ClearString(SString S);                                      //清空字符串
Status ConCat(SString T , SString S1 , SString S2);                 //S1.S2连接，用T返回
Status SubString(SString Sub ,SString S , int pos , int len);       //Sub返回S串的第pos个字符起长度为len的子串
int    Index(SString S , SString T , int pos);                      //返回T在第pos个字符后出现的第一次出现的位置，不存在则返回0
int    Index_1(SString S , SString T , int pos);                    //模式匹配字符串
Status Replace(SString S , SString T , SString V);                  //用V替换在主串S中出现的所有T子串
Status StrInsert(SString S , int pos , SString T);                  //在主串S的第pos字符之前插入T子串
Status StrDelete(SString S , int pos , int len);                    //从主串S中删除第pos字符起长度为len的子串
Status DestroyString(SString S);                                    //销毁串
Status StrPrint(SString S);                                         //打印S串

#endif
