

# 📒 通讯录管理系统 (C + MySQL)

## 📌 项目简介

本项目是一个基于 **C语言数据结构（链表）** 与 **MySQL 数据库** 的简易通讯录管理系统。
 实现了 **联系人信息的录入、查询、存储、持久化**.

------

## ⚡ 功能清单

-  控制台输入联系人信息并存储到链表
-  将链表数据持久化保存到 MySQL 数据库
-  启动时从数据库加载联系人到链表
-  支持联系人增删查改（CRUD）
-  数据去重、唯一性约束（未来改进）
-  图形化界面（后续计划用 Qt/PyQt 实现）

------

## 🛠 技术栈

- **语言**：C (C99 标准)
- **数据结构**：链表
- **数据库**：MySQL
- **数据库接口**：MySQL Connector/C
- **开发环境**：Visual Studio 2022 / CLion + CMake
- **操作系统**：Windows 11

------

## 🚀 使用方法

### 1. 环境准备

- 安装 **MySQL 数据库**（建议本地安装，或用 phpStudy 等工具包自带的 MySQL）。
- 安装 **MySQL Connector/C**（提供 `libmysql.dll` 与头文件）。
- 将 `libmysql.dll` 放到可执行文件同目录或系统环境变量 PATH 中。

### 2. 编译运行

在 Visual Studio 中：

1. 配置 **包含目录** → MySQL Connector 的 `include`
2. 配置 **库目录** → MySQL Connector 的 `lib`
3. 配置 **附加依赖项** → `libmysql.lib`
4. 编译运行

### 3. 数据库表结构

在 MySQL 中先建表：

```sql
CREATE DATABASE testdb;
USE testdb;

CREATE TABLE contact_persons(
	id INT auto_increment primary key ,
	name VARCHAR(50),
	age INT,
	gender VARCHAR(10),
	phone VARCHAR(11),
	address VARCHAR(50),
	note TEXT)


```



## 🔍 项目不足 & 改进方向

- 当前保存逻辑可能会导致重复插入数据 → **改进：保存前做去重或加唯一约束**
- 仅支持本地 MySQL → **改进：支持远程 MySQL 连接**
- 控制台交互较为基础 → **改进：开发图形界面（Qt / Python GUI）**

------

## 📄 License

本项目采用 [MIT License](https://chatgpt.com/c/LICENSE) 开源。

------

