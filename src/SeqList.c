//
// Created by ASUS on 2025/6/12.
//
#define _CRT_SECURE_NO_WARNINGS
#include "SeqList.h"
void SeqInit(SL *psl)
{
    psl->arr=NULL;
    psl->size=0;
    psl->capacity=0;
}
void SeqDestroy(SL *psl)
{
    if(psl->arr)
    {
        free(psl->arr);
    }
    psl->arr=NULL;
    psl->size=0;
    psl->capacity=0;
}
void CheckCapacity(SL *psl)
{
    if(psl->capacity==psl->size)
    {
        //申请空间
        //增容用realloc() 增容一般是倍数增加，一般增加两倍或三倍
        int new_capacity=psl->capacity==0?4:psl->capacity*2;//判断psl->capacity是否为0，如果为0，new_capacity为4，否则new_capacity为psl->capacity的两倍
        SLDataType *temp=(SLDataType*) realloc(psl->arr,new_capacity*sizeof(SLDataType));
        if(temp==NULL)//判断是否申请成功
        {
            perror("realloc fail");
            exit(1);//终止程序
        }
        psl->arr=temp;
        psl->capacity=new_capacity;
    }
}
void SeqPushBack(SL *psl,SLDataType x)
{
    //温柔的解决方式
    //防止psl为空指针
//    if(psl==NULL)
//    {
//        return;
//    }
    //暴力的解决方式
    assert(psl);
    //等价于assert(psl!=NULL); assert()括号为假时会终止程序并报错
    //插入数据之前看数据够不够
    CheckCapacity(psl);
    psl->arr[psl->size]=x;
    psl->size++;
}
void SeqPushFront(SL *psl,SLDataType x)
{
    assert(psl);
    CheckCapacity(psl);
    for(int i=psl->size;i>0;i--)
    {
        psl->arr[i]=psl->arr[i-1];
    }
    psl->arr[0]=x;
    psl->size++;
}
//void SeqPrint(SL psl)
//{
//    for(int i=0;i<psl.size;i++)
//    {
//        printf("%d ",psl.arr[i]);
//    }
//    printf("\n");
//}
void SeqPopBack(SL *psl)
{
    //size不能为零
    assert(psl);
    assert(psl->size);
    psl->size--;
}
void SeqPopFront(SL *psl)
{
    assert(psl);
    assert(psl->size);
    for(int i=0;i<psl->size-1;i++)
    {
        psl->arr[i]=psl->arr[i+1];
    }
    psl->size--;
}
//指定下标前插入
void SeqInsert(SL *psl,int pos,SLDataType x)
{
    assert(psl);
    assert(pos>=0&&pos<=psl->size);
    //检查空间够不够
    CheckCapacity(psl);
    for(int i=psl->size;i>pos;i--)
    {
        psl->arr[i]=psl->arr[i-1];
    }
    psl->arr[pos]=x;
    psl->size++;
}
//指定下标删除
void SeqErase(SL *psl,int pos)
{
    assert(psl);
    assert(pos>=0&&pos<psl->size);
    for(int i=pos;i<psl->size-1;i++)
    {
        psl->arr[i]=psl->arr[i+1];
    }
    psl->size--;
}
//查找
//int SeqFind(SL psl,SLDataType x)
//{
//    assert(psl.arr);
//    for(int i=0;i<psl.size;i++)
//    {
//        if(psl.arr[i]==x)
//        {
//            return i;
//        }
//    }
//    return -1;
//}
