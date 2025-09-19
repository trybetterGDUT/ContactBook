//
// Created by ASUS on 2025/9/17.
//

#ifndef CDATASTRUCT_SAVECONTACT_H
#define CDATASTRUCT_SAVECONTACT_H

#include "Contact.h"

// 初始化数据库连接并确保数据库与表存在
// 返回0表示成功，非0表示失败
int DB_Init(void);

// 从数据库加载联系人到内存链表/顺序表
// 返回成功加载的记录数，失败返回-1
int DB_LoadContacts(Contact *con);

// 将内存中的联系人保存到数据库（全量覆盖：先清空再插入）
// 返回成功保存的记录数，失败返回-1
int DB_SaveContacts(const Contact *con);

// 关闭数据库连接
void DB_Close(void);

#endif //CDATASTRUCT_SAVECONTACT_H
