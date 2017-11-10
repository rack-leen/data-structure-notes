//进制转换：  
#include<stdio.h>  
#include<stdlib.h>  
#define Stack_size 100  
#define Stackincreament 10  
typedef struct{  
    int *base;  
    int top;                   //数组  
    int stacksize;  
}sqstack;  
void initstack(sqstack *la)  
{  
    la->base=(int*)malloc(Stack_size*sizeof(int));  
    la->stacksize=Stack_size;  
    if(!la->base)  
        exit(0);  
    la->top=0;  
}  
void push(sqstack *L,int e)  
{  
    if(L->top>=L->stacksize)  
    {  
        L->base=(int*)realloc(L->base,(Stack_size+Stackincreament)*sizeof(int));    
        if(!L->base)  
           exit(0);  
        L->stacksize+=Stackincreament;  
    }  
    L->base[L->top++]=e;  
}  
void pop(sqstack *l,int *e)  
{  
    if(l->top==0)  
        return ;  
    e=l->base[--l->top];  
      
}  
void trans(int x,int n,sqstack *s)  
{  
    int e;  
    while(x!=0)  
    {     
        e=x%n;  
        x/=n;  
        push(s,e);  
      
    }  
    while(s->top!=0)  
    {  
        pop(s,e);  
        printf("%5d",e);  
    }  
    printf("\n");  
  
}  
  
int main()  
{  
    sqstack m;  
    int x,n;  
    printf("请输入需转换的十进制数及转换后的进制数：\n");  
    scanf("%d",&x);  
    scanf("%d",&n);  
    initstack(&m);  
    trans(x,n,&m);  
    return 0;  
}  
