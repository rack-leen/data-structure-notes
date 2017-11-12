/************************************************************************************//**
 *  @file       otherexample.c
 *
 *  @brief      Brief descriptinon of otherexample.c
 *
 *  @date       2017-11-11 21:39
 *
 ***************************************************************************************/

#include "example.h"

int main()
{
    if(Path(Begin ,End))
    {
        printf("路径如下:\n");
        FootPrint();
    }
    else
    {
        printf("此迷宫走不通\n");
    }
    return 0;
}
