#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OPSETSIZE 7
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;
#define STACK_INIT_SIZE 1000 //存储空间初始分配量
typedef struct{
        char *base;
        char *top;
        int stacksize;
}StackChar;
typedef struct{
        float *base;
        float *top;
        int stacksize;
}StackFloat;
unsigned char Prior[7][7] = {     // 表3.1  算符间的优先关系
    '>','>','<','<','<','>','>',
  '>','>','<','<','<','>','>',
  '>','>','>','>','<','>','>',
  '>','>','>','>','<','>','>',
  '<','<','<','<','<','=',' ',
  '>','>','>','>',' ','>','>',
  '<','<','<','<','<',' ','='
};
float Operate(float a, unsigned char theta, float b);
char OPSET[OPSETSIZE]={'+' , '-' , '*' , '/' ,'(' , ')' , '#'};
Status In(char Test,char* TestOp);
char precede(char Aop, char Bop);
int atof(char* snum){
    int l=strlen(snum),i=1,sum=snum[l-1]-'0';
    l--;
    while(l--){
         i*=10;
         sum+=(snum[l]-'0')*i;
    }
    return sum;
}

void InitStackChar(StackChar &S){
     //构造一个空栈S
     S.base=(char*)malloc(STACK_INIT_SIZE * sizeof(char));
     if(!S.base) exit(OVERFLOW);
     S.top=S.base;
     S.stacksize=STACK_INIT_SIZE;
}
void InitStackFloat(StackFloat &S){
     //构造一个空栈S
     S.base=(float*)malloc(STACK_INIT_SIZE * sizeof(float));
     if(!S.base) exit(OVERFLOW);
     S.top=S.base;
     S.stacksize=STACK_INIT_SIZE;
}
char GetTopChar(StackChar S){
     //返回S的栈顶元素
     return *(S.top-1);
}
float GetTopFloat(StackFloat S){
     //返回S的栈顶元素
     return *(S.top-1);
}
void PushChar(StackChar &S,char e){
     *S.top++=e;
}
void PushFloat(StackFloat &S,float e){
     *S.top++=e;
}
void PopChar(StackChar &S,char &e){
     e=*--S.top;
}
void PopFloat(StackFloat &S,float &e){
     e=*--S.top;
}
float EvaluateExpression(char* MyExpression) {  // 算法3.4
   // 算术表达式求值的算符优先算法。
   // 设OPTR和OPND分别为运算符栈和运算数栈，OP为运算符集合。
   StackChar  OPTR;    // 运算符栈，字符元素
   StackFloat OPND;    // 运算数栈，实数元素
   char TempData[20];//支持整数位数
   float Data,a,b;
   char theta,*c,x,Dr[2];

   InitStackChar (OPTR);
   PushChar (OPTR, '#');  //#是表达式的结束符
   InitStackFloat (OPND);
   c = MyExpression;
   strcpy(TempData,"/0");
   while (*c!= '#' || GetTopChar(OPTR)!= '#') {
      if (!In(*c, OPSET)) {
       Dr[0]=*c;
       Dr[1]='/0';
         strcat(TempData,Dr);
         c++;
         if(In(*c,OPSET)) {
            Data=(float)atof(TempData);
            PushFloat(OPND, Data);
            strcpy(TempData,"/0");
         }
      } else {   // 是运算符则进栈
         switch (precede(GetTopChar(OPTR), *c)) {
            case '<':   // 栈顶元素优先权低
                 PushChar(OPTR, *c);
                 c++;
                 break;
            case '=':   // 脱括号并接收下一字符
                 PopChar(OPTR, x);
                 c++;
                 break;
            case '>':   // 退栈并将运算结果入栈
                 PopChar(OPTR, theta);
                 PopFloat(OPND, b);
                 PopFloat(OPND, a);
                 PushFloat(OPND, Operate(a, theta, b));
                 break;
         } // switch
      }
   } // while
   return GetTopFloat(OPND);
} // EvaluateExpression
float Operate(float a,unsigned char theta, float b) {
   switch(theta) {
      case '+': return a+b;
      case '-': return a-b;
      case '*': return a*b;
      case '/': return a/b;
      default : return 0;
   }
}
Status In(char Test,char* TestOp) {
   bool Find=false;
   for (int i=0; i< OPSETSIZE; i++) {
      if (Test == TestOp[i]) Find= true;
   }
   return Find;
}
int ReturnOpOrd(char op,char* TestOp) {
   int i;
   for(i=0; i< OPSETSIZE; i++) {
      if (op == TestOp[i]) return i;
   }
   return 0;
}
char precede(char Aop, char Bop) {
   return Prior[ReturnOpOrd(Aop,OPSET)][ReturnOpOrd(Bop,OPSET)];
}
int main()
{
    char s[1001];
    long long result;
    int len;
    printf("输入一行表达式，以#结束：/n");
    while(gets(s)){
          result=(long long)EvaluateExpression(s);
          printf("结果是：%d/n",result);
          printf("继续输入吧：/n");
    }
}
