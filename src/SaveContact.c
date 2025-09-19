//
// Created by ASUS on 2025/9/17.
//
#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <stdio.h>
#include <string.h>

#include "SaveContact.h"
#include "SeqList.h"

// 可配置：已有的数据库与表名
#define DB_NAME "contact_book"
#define TABLE_NAME "contact_persons"

// 全局的 MySQL 连接句柄，整个程序生命周期内复用
static MYSQL *g_conn = NULL;

// 执行一条简单 SQL 语句的辅助函数
// 参数：
//   sql —— 以'\0'结尾的 SQL 文本，例如 "SELECT ..."、"INSERT ..."。
// 返回：0 表示成功；-1 表示失败（并打印错误）。
static int exec_sql(const char *sql) {
	if (mysql_query(g_conn, sql) != 0) {
		printf("SQL执行失败: %s\n错误: %s\n", sql, mysql_error(g_conn));
		return -1;
	}
	return 0;
}

// 初始化数据库连接，连接到已存在的数据库，并确保表存在
// 连接参数：host=localhost, user=root, password=root, port=3306
// 注意：如你的 MySQL 账号或端口不同，请在此处修改
int DB_Init(void) {
	g_conn = mysql_init(NULL);
	//判断数据库连接是否成功
	if (g_conn == NULL) {
		printf("mysql_init() 失败\n");
		return -1;
	}

	// mysql_real_connect 参数说明：
	//   g_conn     —— 连接句柄（mysql_init 返回值）
	//   "localhost" —— 主机名（也可为 IP）
	//   "root"     —— 用户名
	//   "root"     —— 密码
	//   DB_NAME     —— 连接时选择的数据库名
	//   3306        —— 端口
	//   NULL        —— 本地套接字/命名管道路径（Windows 置 NULL）
	//   0           —— 连接标志位（默认 0）
	if (mysql_real_connect(g_conn, "localhost", "root", "root", DB_NAME, 3306, NULL, 0) == NULL) {
		printf("mysql_real_connect() 失败: %s\n", mysql_error(g_conn));
		mysql_close(g_conn);//关闭数据库连接
		g_conn = NULL;
		return -1;
	}

	// 设置连接字符集为 UTF-8，解决中文乱码问题
	if (mysql_set_character_set(g_conn, "utf8mb4") != 0) {
		printf("设置字符集失败: %s\n", mysql_error(g_conn));
		mysql_close(g_conn);
		g_conn = NULL;
		return -1;
	}

	// 确保当前会话使用目标数据库
	if (exec_sql("USE " DB_NAME ";") != 0) {
		return -1;
	}

	// 创建表（如不存在）
	// 字段长度与 Contact.h 中的 Max_* 定义保持一致，避免截断
	const char *create_table_sql =
		"CREATE TABLE IF NOT EXISTS " TABLE_NAME " (\n"
		"  id INT AUTO_INCREMENT PRIMARY KEY,\n"
		"  name VARCHAR(20) NOT NULL,\n"
		"  gender VARCHAR(10) NOT NULL,\n"
		"  age INT NOT NULL,\n"
		"  telephone VARCHAR(20) NOT NULL,\n"
		"  address VARCHAR(30) NOT NULL,\n"
		"  note VARCHAR(100) NOT NULL\n"
		");";
	if (exec_sql(create_table_sql) != 0) {
		return -1;
	}

	printf("已连接并准备好数据库/表\n");
	return 0;
}

// 从数据库加载联系人到顺序表
// 参数：
//   con —— 输出目标（已初始化的 Contact/SeqList），函数会向其中 push 数据
// 返回：成功加载的条数；失败返回 -1
int DB_LoadContacts(Contact *con) {
	if (g_conn == NULL) {
		printf("数据库未初始化\n");
		return -1;
	}
	if (exec_sql("USE " DB_NAME ";") != 0) {
		return -1;
	}
	const char *sql = "SELECT name, gender, age, telephone, address, note FROM " TABLE_NAME " ORDER BY id;";
	if (mysql_query(g_conn, sql) != 0) {
		printf("查询失败: %s\n", mysql_error(g_conn));
		return -1;
	}
	// mysql_store_result：获取结果集，失败返回 NULL，可结合 mysql_errno 判断是否为错误
	MYSQL_RES *res = mysql_store_result(g_conn);
	if (res == NULL) {
		// 可能是空结果或错误
		if (mysql_errno(g_conn) != 0) {
			printf("获取结果失败: %s\n", mysql_error(g_conn));
			return -1;
		}
		// 空表返回0
		return 0;
	}

	int loaded = 0;
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(res)) != NULL) {
		PerInfo info;
		// 逐列复制，使用 snprintf 保证不会越界
		snprintf(info.name, sizeof(info.name), "%s", row[0] ? row[0] : "");
		snprintf(info.gender, sizeof(info.gender), "%s", row[1] ? row[1] : "");
		info.age = row[2] ? atoi(row[2]) : 0;
		snprintf(info.telephone, sizeof(info.telephone), "%s", row[3] ? row[3] : "");
		snprintf(info.address, sizeof(info.address), "%s", row[4] ? row[4] : "");
		snprintf(info.note, sizeof(info.note), "%s", row[5] ? row[5] : "");
		SeqPushBack(con, info);
		loaded++;
	}
	//释放
	mysql_free_result(res);
	//返回加载了几条信息
	return loaded;
}

// 对字符串做转义，避免引号、反斜杠等特殊字符破坏 SQL 语法
// 参数：
//   dest      —— 输出缓冲区指针
//   dest_size —— 输出缓冲区大小（字节数，需 >= 原字符串 2x+1）
//   src       —— 输入原始字符串（以'\0'结尾）
// 注意：目的缓冲区大小应为原长度的 2x+1 以上
static void escape_str(char *dest, size_t dest_size, const char *src) {
	// mysql_real_escape_string 可能需要至多 2x+1 空间
	if (dest_size == 0) return;
	unsigned long escaped_len = mysql_real_escape_string(g_conn, dest, src, (unsigned long)strlen(src));
	if (escaped_len >= dest_size) {
		// 截断以保证以\0 结尾（极端情况下仍保证安全）
		dest[dest_size - 1] = '\0';
	}
}

// 将内存中的联系人全量保存到数据库
// 参数：
//   con —— 输入数据源（内存中的联系人顺序表）
// 策略：开启事务 -> 清空表 -> 逐条插入 -> 提交；若中途失败则回滚
// 返回：成功保存的条数；失败返回 -1
int DB_SaveContacts(const Contact *con) {
	if (g_conn == NULL) {
		printf("数据库未初始化\n");
		return -1;
	}
	if (exec_sql("USE " DB_NAME ";") != 0) {
		return -1;
	}
	// 使用事务保证原子性：要么全部成功，要么全部失败
	if (exec_sql("START TRANSACTION;") != 0) {
		return -1;
	}
	if (exec_sql("DELETE FROM " TABLE_NAME ";") != 0) {
		exec_sql("ROLLBACK;");
		return -1;
	}

	int saved = 0;
	for (int i = 0; i < con->size; i++) {
		const PerInfo *p = &con->arr[i];

		// 预留 2x+1 空间，配合 mysql_real_escape_string 使用
		char name_esc[Max_name * 2 + 1] = {0};
		char gender_esc[Max_gender * 2 + 1] = {0};
		char tel_esc[Max_telephone * 2 + 1] = {0};
		char addr_esc[Max_address * 2 + 1] = {0};
		char note_esc[Max_note * 2 + 1] = {0};
        
		//escape_str 对字符串做转义，避免引号、反斜杠等特殊字符破坏 SQL 语法
		escape_str(name_esc, sizeof(name_esc), p->name);
		escape_str(gender_esc, sizeof(gender_esc), p->gender);
		escape_str(tel_esc, sizeof(tel_esc), p->telephone);
		escape_str(addr_esc, sizeof(addr_esc), p->address);
		escape_str(note_esc, sizeof(note_esc), p->note);

		//用于插入数据的SQL语句
		char sql[1024];
		//snprintf 保证不会越界
		snprintf(sql, sizeof(sql),
			"INSERT INTO " TABLE_NAME "(name, gender, age, telephone, address, note) VALUES ('%s','%s',%d,'%s','%s','%s');",
			name_esc, gender_esc, p->age, tel_esc, addr_esc, note_esc);
		if (exec_sql(sql) != 0) {
			exec_sql("ROLLBACK;");
			return -1;
		}
		saved++;
	}

	if (exec_sql("COMMIT;") != 0) {
		exec_sql("ROLLBACK;");
		return -1;
	}
	return saved;
}

// 关闭数据库连接（可安全重复调用）
// 参数：无
void DB_Close(void) {
	if (g_conn) {
		mysql_close(g_conn);
		g_conn = NULL;
	}
}