//
// Created by ASUS on 2025/6/12.
#ifndef CDATASTRUCT_SEQLIST_H
#define CDATASTRUCT_SEQLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Contact.h"



//顺序表的结构定义
//#define N 100
////静态顺序表
//struct SeqList{
//    int arr[N];
//    int size;//顺序表的实际长度
//};
//
//动态顺序表
//typedef int SLDataType;
typedef PerInfo SLDataType;
//自定义数据类型，让数组装的是每一个通讯录的信息，即结构体
//方便以后数据类型修改
typedef struct SeqList{
    SLDataType *arr;//将每个人的信息存入数组中，即结构体类型的数组
    int size;//顺序表的实际长度
    int capacity;//顺序表的最大容量
}SL;

//顺序表的初始化
void SeqInit(SL *psl);


//顺序表的销毁
void SeqDestroy(SL *psl);

//顺序表尾插
void SeqPushBack(SL *psl,SLDataType x);
//顺序表头插
void SeqPushFront(SL *psl,SLDataType x);

//打印顺序表
void SeqPrint(SL psl);
//顺序表尾删
void SeqPopBack(SL *psl);
//顺序表头删
void SeqPopFront(SL *psl);
//指定下标前插入
void SeqInsert(SL *psl,int pos,SLDataType x);
//指定下标删除
void SeqErase(SL *psl,int pos);
//查找
int SeqFind(SL psl,SLDataType x);
#endif // CDATASTRUCT_SEQLIST_H