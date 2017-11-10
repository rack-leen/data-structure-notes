    #include<stdio.h>
    #include<stdlib.h>

    #define TRUE 1
    #define FALSE 0
    #define OK 1
    #define ERROR 0
    #define OVERFLOW -2
    #define LIST_INIT_SIZE 10
    #define LISTINCREMENT 4

    typedef int Status;
    typedef int ElemType;


    typedef struct
    {
        ElemType *elem;                     //存储机制
        int length;                         //当前线性表的长度
        int listsize;                       //当前分配的存储容量
    }SqList;


    Status InitList_Sq(SqList *L);          //初始化建立线性表

    void DestroyList_Sq(SqList *L);         //销毁线性表

    void ClearList_Sq(SqList *L);           //置空线性表

    Status Listempty_Sq(SqList *L);         //判断线性表是否为空

    Status ListLength_Sq(SqList *L);         //获取线性表的长度（元素个数）

    /*获取线性表第i个个位置的值*/
    Status Getlem(SqList *L, int i, ElemType *e);

    /*求线性表的前继元素*/
    Status PriorElem(SqList *L, ElemType cur_e, ElemType *pre_e);

    /*求线性表的后继元素*/
    Status NextElem(SqList *L, ElemType cur_e, ElemType *next_e);

    /*在第i个位置插入元素e*/
    Status ListInsert_Sq(SqList *L, int i, ElemType e);

    /*删除线性表的第i个元素*/
    Status ListDelete_Sq(SqList *L, int i, ElemType *e);

    /*遍历输出顺序表中所有元素*/
    Status ListTransver_Sq(SqList *L);

    /*对顺序表中元素进行排序*/
    void ListSort_Sq(SqList *L);

    /*倒置顺序表中所有元素*/
    void ListInvert_Sq(SqList *L);


    /*初始化线性表*/
    Status InitList_Sq(SqList *L)
    {
        L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        if(L->elem == NULL)
        {
            printf("内存分配失败！\n");
            return OVERFLOW;
        }
        L->length = 0;      //线性表(空表)的长度为0
        L->listsize =  LIST_INIT_SIZE;      //表的初始存储容量为LIST_INIT_SIZE
        return OK;
    }


    /*销毁线性表*/
    void DestroyList_Sq(SqList *L)
    {
        if(L->elem != NULL)
        {
            L->elem = NULL;     //释放线性表内存空间
            L->length = 0;
            L->listsize = 0;
        }
    }


    /*置空线性表*/
    void ClearList_Sq(SqList *L)
    {
        L->length = 0;
    }


    /*判断线性表是否为空*/
    Status Listempty_Sq(SqList *L)
    {
        if(L->length == 0)
            return TRUE;
        else
            return FALSE;
    }


    /*获取线性表的长度*/
    Status ListLength_Sq(SqList *L)
    {
        return L->length;
    }


    /*获取线性表的第i个元素的值*/
    Status Getlem(SqList *L, int i, ElemType *e)
    {
        if(i < 1 || i > L->length)
        {
            printf("没有第%d个元素！\n", i);
            return ERROR;
        }
        if(L->elem == NULL)
        {
            printf("该线性表为空！\n");
            return ERROR;
        }
        *e = L->elem[i-1];
        return OK;
    }


    /*求线性表的前继元素*/
    Status PriorElem(SqList *L, ElemType cur_e, ElemType *pre_e)
    {
        int i = 2;              //从第二个元素开始
        while(i <= L->length)
        {
            if(L->elem[i-1] == cur_e)
            {
                *pre_e = L->elem[i-2];
                return OK;
            }
            i++;
        }
        return ERROR;
    }


    /*求线性表中的后继元素*/
    Status NextElem(SqList *L, ElemType cur_e, ElemType *next_e)
    {
        int i = 1;
        while(i < L->length - 1)
        {
            if(L->elem[i-1] == cur_e)       //之所以不是i,是因为防止第一个元素没有后继
            {
                *next_e = L->elem[i];
                return OK;
            }
            i++;
        }
        return ERROR;
    }


    /*在线性表的第i个位置插入元素e*/
    Status ListInsert_Sq(SqList *L, int i, ElemType e)
    {
        if(i < 1 ||i > L->length+1)
            return ERROR;
        if(L->length >= L->listsize)
        {
            ElemType *newbase = (ElemType *)realloc(L->elem,sizeof(ElemType)*(L->listsize+LISTINCREMENT));
            if(!newbase)
                return OVERFLOW;        //存储分配失败
            L->elem = newbase;
            L->listsize += LISTINCREMENT;
        }
        ElemType *q = &(L->elem[i-1]);     //q为插入位置
        ElemType *p;                    //是p指向最后一个元素
        for(p = &(L->elem[L->length - 1]); p >=q; p--)
            *(p+1) = *p;
        *q = e;                         //插入e
        L->length ++;
        return OK;
    }


    /*删除线性表的第i个元素*/
    Status ListDelete_Sq(SqList *L, int i, ElemType *e)
    {
        if(i < 1 || i > L->length)
        {
            printf("需要删除的位置不存在！\n");
            return ERROR;
        }
        ElemType *p = &(L->elem[i-1]);      //p为被删除元素的位置
        *e = *p;                             //被删除的元素的值赋给e
        ElemType *q = L->elem + L->length - 1;  //表尾元素的位置
        for(p = p+1; p <= q; p++)
            *(p-1) = *p;                    //被删除元素之后的元素左移
        L->length --;
        return OK;
    }


    /*遍历输出顺序表中所有元素*/
    Status ListTransver_Sq(SqList *L)
    {
        int i;
        if(L->length == 0)
        {
            printf("\t该表为空！\n\n");
            return ERROR;
        }
        else
        {
            printf("\t该线性表为：");
            for(i = 1; i <= L->length ; i++)     //刚才忘记了=，导致使出有问题
                printf("%d ", L->elem[i-1]);
            printf("\n\n");
        }
        return OK;
    }


    /*对顺序表中元素进行排序*/
    void ListSort_Sq(SqList *L)
    {
        int i, j, tmp, max;
        for(i = 0; i < L->length - 1; i++)
        {
            max = i;
            for(j = i; j < L->length; j++)
            {
                if(L->elem[max] < L->elem[j])
                    max = j;
            }
            tmp = L->elem[i];
            L->elem[i] = L->elem[max];
            L->elem[max] = tmp;
        }
    }       /*选择排序法*/


    /*倒置顺序表中所有元素*/
    void ListInvert_Sq(SqList *L)
    {
        int i = 0, j = L->length, tmp;
        while(i < j)
        {
            tmp = L->elem[i];
            L->elem[i] = L->elem[j];
            L->elem[j] = tmp;
            i ++;
            j --;
        }
    }


    int main()
    {
        SqList L;
        ElemType e;
        int i;


        /*初始化列表*/
        if(InitList_Sq(&L) == NULL)
            printf("\t初始化列表失败！\n\n");
        else
            printf("\t初始化列表成功！\n\n");


        /*判断该线性表是否为空*/
        printf("\t列表是否为空？\n");
        if(Listempty_Sq(&L) == NULL)
            printf("\t该线性表是为空！\n\n");
        else
            printf("\t该线性表不为空！\n\n");


        /*该线性表的长度*/
        printf("\t该线性表的长度：%d\n\n", ListLength_Sq(&L));


        /*向线性表中插入元素*/
        for(i = 1; i <= 8; i++)
            ListInsert_Sq(&L, i, i+1);
        ListTransver_Sq(&L);
        printf("\t该线性表的长度：%d\n\n", ListLength_Sq(&L));


        /*查找数的前驱*/
        printf("\t将要查找元素的前驱！\n");
        printf("\t输入要查找的值: ");
        scanf("%d", &i);
        if(PriorElem(&L, i, &e) == 1)
            printf("\t存在前驱，且前驱为：%d\n\n", e);
        else
            printf("\t不存在前驱元素！\n\n");


        /*查找数的后继*/
        printf("\t将要查找元素的后继！\n");
        printf("\t输入要查找的值: ");
        scanf("%d", &i);
        if(NextElem(&L, i, &e) == 1)
            printf("\t存在后继，且后继为：%d\n\n", e);
        else
            printf("\t不存在后继元素！\n\n");


        /*删除线性表中的第i个元素*/
        printf("\t删除元素！\n");
        printf("\t删除前：");
        ListTransver_Sq(&L);
        printf("\t输入要删除的第几个元素：");
        scanf("%d", &i);
        ListDelete_Sq(&L, i, &e);
        printf("\t删除后：");
        ListTransver_Sq(&L);


        /*元素排序*/
        printf("\t排序前：");
        ListTransver_Sq(&L);
        printf("\t排序后：");
        ListSort_Sq(&L);
        ListTransver_Sq(&L);


        /*导致线性表的元素*/
        printf("\t倒置前：");
        ListTransver_Sq(&L);
        printf("\t倒置后：");
        ListInvert_Sq(&L);
        ListTransver_Sq(&L);
        return 0;
    }
