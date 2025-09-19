//
// Created by ASUS on 2025/6/12.
//
#define _CRT_SECURE_NO_WARNINGS
#include "SeqList.h"
#include "SaveContact.h"
#include "Contact.h"
#include <stdio.h>
#include <stdlib.h>


// 菜单展示
void mena()
{
	printf("*********************************\n");
	printf("***********1.增加联系人************\n");
	printf("***********2.删除联系人************\n");
	printf("***********3.查找联系人************\n");
	printf("***********4.修改联系人************\n");
	printf("***********5.打印联系人************\n");
	printf("***********0.退出程序**************\n");
	printf("*********************************\n");
}

// 程序入口：
// 1) 初始化顺序表；2) 连接数据库并从表加载已有联系人；
// 3) 根据用户操作修改内存中的通讯录；4) 退出时全量保存到数据库；
int main()
{
	setbuf(stdout,NULL);
	int option=-1;
	Contact con;
	ContactInit(&con);

	// 初始化数据库并加载（失败则仅使用内存数据，不影响使用）
	if (DB_Init() == 0) {
		int loaded = DB_LoadContacts(&con);
		if (loaded >= 0) {
			printf("已从数据库加载 %d 条联系人\n", loaded);
		} else {
			printf("从数据库加载失败，继续使用空通讯录\n");
		}
	} else {
		printf("数据库初始化失败，将只在内存中运行\n");
	}

	do{
		mena();
		printf("请选择：");
		scanf("%d",&option);
		switch(option)
		{
			case 1:
				ContactAdd(&con);
				break;
			case 2:
				ContactDel(&con);
				break;
			case 3:
				ContactFind(con);
				break;
			case 4:
				ContactModify(&con);
				break;
			case 5:
				ContactPrint(con);
				break;
			case 0:
				printf("退出程序...\n");
				break;
			default:
				printf("输入错误，请重新输入\n");
				break;
		}
	} while (option!=0);

	// 退出前保存到数据库（如果初始化成功过）
	int saved = DB_SaveContacts(&con);
	if (saved >= 0) {
		printf("已保存 %d 条联系人到数据库\n", saved);
	} else {
		printf("保存到数据库失败\n");
	}
	DB_Close();//关闭数据库连接

	ContactDestroy(&con);//销毁顺序表
	return 0;
}