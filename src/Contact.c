//
// Created by ASUS on 2025/6/15.
//
#define _CRT_SECURE_NO_WARNINGS
#include "Contact.h"
#include "SeqList.h"
#include <string.h>
//通讯录的初始化
void ContactInit(Contact *con)
{
    SeqInit(con);
    //通讯录初始化相当于初始化顺序表
}
//通讯录的销毁
void ContactDestroy(Contact *con)
{
    SeqDestroy(con);
}
//通讯录插入数据
void ContactAdd(Contact *con)
{
//    printf("请输入姓名：");
//    scanf("%s",con->arr->name);
//    printf("请输入年龄：");
//    scanf("%d",&con->arr->age);
//    printf("请输入性别：");
//    scanf("%s",con->arr->gander);
//    printf("请输入电话：");
//    scanf("%s",con->arr->telephone);
//    printf("请输入地址：");
//    scanf("%s",con->arr->address);
//错误写法 arr装的是一整个结构体的地址 arr是指针，上面写法相当于arr是一个结构体地址

//正确写法应该是先定义一个结构体变量，再把这个结构体变量的地址赋给arr，即用顺序表的方式插入数据
    //定义一个结构体变量
    PerInfo info;
    printf("请输入姓名：");
    scanf("%s",info.name);
    printf("请输入年龄：");
    scanf("%d",&info.age);
    printf("请输入性别：");
    scanf("%s",info.gender);
    printf("请输入电话：");
    scanf("%s",info.telephone);
    printf("请输入地址：");
    scanf("%s",info.address);
    printf("请输入备注：");
    scanf("%s",info.note);

        // 实际发生的操作：
        // 1. name作为地址常量（如0x7ffe3b...）被传递给scanf
        // 2. scanf将输入内容写入从该地址开始的连续内存
        // 3. 数组名本身的地址（0x7ffe3b...）始终未改变

    //把这个结构体变量的地址赋给arr
    SeqPushBack(con,info);
}
//通讯录打印数据
void ContactPrint(Contact con)
{
    for(int i=0;i<con.size;i++)
    {
        printf("姓名为：%s\n",con.arr[i].name);
        printf("年龄为：%d\n",con.arr[i].age);
        printf("性别为：%s\n",con.arr[i].gender);
        printf("电话为：%s\n",con.arr[i].telephone);
        printf("地址为：%s\n",con.arr[i].address);

    }
}
//通讯录查找数据
int ContactFindByName(Contact con,char *name)
{
    for(int i=0;i<con.size;i++)
    {
        if(strcmp(con.arr[i].name,name)==0)
        {
            return i;
        }
    }
    return -1;
}
//通讯录删除数据
void ContactDel(Contact *con)
{
    printf("请输入要删除的姓名：");
    char name[Max_name];
    //不能写成char *name;没有分配内存会导致程序崩溃的风险，野指针。
    scanf("%s",name);
    int pos=ContactFindByName(*con,name);
    if(pos<0)
    {
        printf("未找到\n");
        return;
    }
    else
    {
        SeqErase(con,pos);
        printf("删除成功\n");
    }
}
//通讯录修改数据
void ContactModify(Contact *con)
{
    char name[Max_name];
    printf("请输入要修改的姓名：");
    scanf("%s",name);
    int pos=ContactFindByName(*con,name);
    if(pos<0)
    {
        printf("未找到\n");
        return;
    }
    else
    {
        printf("请输入新的姓名：");
        scanf("%s",con->arr[pos].name);
        printf("请输入新的年龄：");
        scanf("%d",&con->arr[pos].age);
        printf("请输入新的性别：");
        scanf("%s",con->arr[pos].gender);
        printf("请输入新的电话：");
        scanf("%s",con->arr[pos].telephone);
        printf("请输入新的地址：");
        scanf("%s",con->arr[pos].address);
        printf("请输入新的备注：");
        scanf("%s", con->arr[pos].note);
    }
}
//通讯录查找数据
void ContactFind(Contact con)
{
    char name[Max_name];
    printf("请输入要查找的姓名：");
    scanf("%s",name);
    int pos=ContactFindByName(con,name);
    if(pos<0)
    {
        printf("未找到\n");
        return;
    }
    else
    {
        printf("姓名为：%s\n",con.arr[pos].name);
        printf("年龄为：%d\n",con.arr[pos].age);
        printf("性别为：%s\n",con.arr[pos].gender);
        printf("电话为：%s\n",con.arr[pos].telephone);
        printf("地址为：%s\n",con.arr[pos].address);
    }
}