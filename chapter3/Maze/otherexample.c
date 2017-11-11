/************************************************************************************//**
 *  @file       1.c
 *
 *  @brief      Brief descriptinon of 1.c 
 *
 *  @date       2017-11-11 21:39
 *
 ***************************************************************************************/




      
    #define MAX_ROW 7  //迷宫最大行数  
    #define MAX_COLUMN 7  //迷宫最大列数  
    #define STACK_INIT_SIZE 10  
    #define STACK_INCREMENT 2  
      
    typedef struct{  //迷宫坐标位置  
        int x;  
        int y;  
    }Pos;  
      
    typedef struct{  //栈的元素  
        int ord;  //路径上的序号  
        Pos seat;  //坐标位置  
        int di;  //下一步行走的方向  
    }SElemType;  
      
    typedef struct{  //栈  
        SElemType *base;  
        SElemType *top;  
        int stacksize;  
    }SqStack;  
      
    /*用数组表示数据结构书中的迷宫，1表示墙壁，0表示通道*/  
    int a[MAX_ROW][MAX_COLUMN] = {  
        {2, 2, 2, 2, 2, 2, 2},   
        {2, 0, 0, 0, 0, 0, 2},   
        {2, 0, 2, 0, 2, 0, 2},   
        {2, 0, 0, 2, 0, 2, 2},   
        {2, 2, 0, 2, 0, 2, 2},   
        {2, 0, 0, 0, 0, 0, 2},   
        {2, 2, 2, 2, 2, 2, 2}     
    };   
      
    Pos Begin={1,1},End={5,5};  //设定迷宫入口和出口  
    int curstep=1;  //步数  
    SqStack S;  //定义一个全局顺序栈  
      
    /*构造一个空栈*/  
    void InitStack(SqStack &S)  
    {  
        S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));  
        if(!S.base) exit(OVERFLOW);  
      
        S.top=S.base;  
        S.stacksize=STACK_INIT_SIZE;  
    }  
      
    /*判断一个栈是否为空栈,是返回1，不是返回0*/  
    int StackEmpty(SqStack S)  
    {  
        if(S.base==S.top)  
            return 1;  
        else   
            return 0;  
    }  
      
    /*插入e为新的栈顶元素*/  
    void Push(SqStack &S ,SElemType e)  
    {  
        if((S.top-S.base)>=S.stacksize)  
        {  
            S.base=(SElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(SElemType));  
            if(!S.base) exit(OVERFLOW);  
      
            S.top=S.base+S.stacksize;  
            S.stacksize+=STACK_INCREMENT;  
        }  
        *S.top++=e;  
    }  
      
    /*若栈不为空，则用e删除栈顶元素，并返回OK，否则返回ERROR*/  
    int Pop(SqStack &S ,SElemType &e)  
    {  
        if(S.top==S.base)  
            return ERROR;  
      
        e=*--S.top;  
        return OK;  
    }  
      
    /*输出走迷宫的路径*/  
    void FootPrint()  
    {  
        int i,j;  
        for(i=0;i<MAX_ROW;i++)  
        {  
            for(j=0;j<MAX_COLUMN;j++)  
                printf("%d ",a[i][j]);  //空格为了观看方便  
            printf("\n");  
        }  
    }  
      
    /*求当前位置的下一步*/  
    void NextStep(Pos &seat ,int di)  
    {  
        Pos direction[4]={{0,1},{1,0},{0,-1},{-1,0}};  //方向依次为东南西北  
      
        seat.x+=direction[di].x;  
        seat.y+=direction[di].y;  
    }  
      
    /*搜寻迷宫路径，只能搜索一条路径，且不一定是最优路径*/  
    /*若能求得一条路径则返回TURE，否则返回FALSE*/  
    int Path(Pos Begin ,Pos End)  
    {  
        Pos CurPos;  
        SElemType e;  
        InitStack(S);  
        CurPos=Begin;  //将最初位置设定为入口  
      
        do  
        {  
            if(a[CurPos.x][CurPos.y]==0)  //此时的位置为通路  
            {  
                a[CurPos.x][CurPos.y]=curstep;  
                e.ord=curstep;  
                e.seat=CurPos;  
                e.di=0;  
      
                Push(S,e);  
                curstep++;  
      
                if(CurPos.x==End.x&&CurPos.y==End.y)  
                    return TRUE;  
      
                NextStep(CurPos,e.di);  
            }  //if(a[CurPos.x][CurPos.y]==0) end  
            else  
            {  
                if(!StackEmpty(S))  
                {  
                    Pop(S,e);  
                    curstep--;  
                    while(e.di==3&&!StackEmpty(S))  
                    {  
                        a[e.seat.x][e.seat.y]=-1;  
                        Pop(S,e);  
                        curstep--;  
                    }  //while(e.di==3&&!StackEmpty(S)) end  
                    if(e.di<3)  
                    {  
                        e.di++;  
                        Push(S,e);  
                        curstep++;  
                        CurPos=e.seat;  
                        NextStep(CurPos,e.di);  
                    }  //if(e.di<3)  
                }  //if(!StackEmpty(S)) end  
            }  //else end  
        } while(!StackEmpty(S)); //do end  
        return FALSE;  
    }  
      
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

