//
// Created by ASUS on 2025/6/15.
//
#define _CRT_SECURE_NO_WARNINGS
#define Max_name 20
#define Max_gender 10
#define Max_telephone 20
#define Max_address 30
#define Max_note 100
#ifndef CDATASTRUCT_CONTRACT_H
#define CDATASTRUCT_CONTRACT_H
//通讯录中每一个人信息定义
typedef struct PersonInfo
{
    char name[Max_name];//姓名
    char gender[Max_gender];//性别
    int age;//年龄
    char telephone[Max_telephone];//电话
    char address[Max_address];//地址
    char note[Max_note];//备注
}PerInfo;
typedef struct SeqList Contact;//顺序表即为通讯录，此处重新命名便于区分
//通讯录初始化即对顺序表的初始化
void ContactInit(Contact *con);
//通讯录销毁
void ContactDestroy(Contact *con);
//通讯录插入数据
void ContactAdd(Contact *con);
//打印通讯录
void ContactPrint(Contact con);
//通讯录删除数据
void ContactDel(Contact *con );
//通讯录修改数据
void ContactModify(Contact *con);
//通讯录查找数据
void ContactFind(Contact con);

#endif //CDATASTRUCT_CONTRACT_H
