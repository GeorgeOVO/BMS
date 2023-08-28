#ifndef MANAGEROPER_H
#define MANAGEROPER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 读者管理
typedef struct Rmanager
{
    int id;
    char name[20];
    int pwd;
    char tel[12];                   // 电话
    int borrowed_book;              // 已借图书数
    char binformation_book[3][30];    // 已借图书信息
    int order_book;                 // 已预约图书数
    char oinformation_book[3][30];    // 已预约图书信息
    int val;                        // 读者充值
    struct Rmanager* next;
}Rmanager;


// 图书管理
typedef struct Bmanager
{
    int id;
    char book_name[50];
    char author[50];
    char publication_date[11];  // 出版日期
    char press[100];           // 出版社
    int price;                 // 价格
    int borrow_times;          // 借阅次数
    char book_status[20];       // 图书状态
    int in_pavilion;          // 在馆判断
    char binformation_stu;    // 借阅判断
    char oinformation_stu;   // 预约判断
    struct Bmanager* next;
}Bmanager;

// 创建读者
extern Rmanager* create_rmanager(void);



// 创建图书
extern Bmanager* create_bmanager(void);
// 读者头节点
typedef struct Rhead
{
    int cnt;
    Rmanager* next;
}Rhead;

// 图书头节点
typedef struct Bhead
{
    int cnt;
    Bmanager* next;
}Bhead;

extern Rhead* rhead;
extern Bhead* bhead;

// 读者结构体头节点
extern Rhead* create_rhead(void);

// 书本结构体头节点
extern Bhead* create_bhead(void);


// 添加读者
void add_reader(Rhead* rhead);
void _add_reader(Rhead* rhead,Rmanager* rmanager);
// 添加图书
void add_book(Bhead* bhead);
void _add_book(Bhead* bhead,Bmanager* bmanager);
// 删除读者
bool delete_reader(Rhead* rhead);
// 删除图书
bool delete_book(Bhead* bhead);
// 列出所有读者
void show_reader(Rhead* rhead);
// 修改图书信息
bool modify_book(Bhead* bhead);
// 根据图书编号查找
bool _search_num(Bhead* bhead);
// 根据书名查找
void _search_name(Bhead* bhead);
// 根据作者查找
void _search_author(Bhead* bhead);
// 查找图书
bool search_book(Bhead* bhead);
// 列出所有图书
void show_book(Bhead* bhead);

Rmanager*  _reader_id(Rmanager* n,int id);
Rmanager* _reader_name(Rmanager* n,char* name);

// 读者充值
void recharge_val(Rhead* rhead);

// 加载头节点
void load_head();

// 修改密码
bool modify_pwd(ManagerMessage* managers);
// 保存所有数据进文件
void save_all(Rhead* rhead,Bhead* bhead);
bool add_all_reader(Rmanager** rmanager);
bool add_all_book(Bmanager** bmanager);
// 批量导入读者
void batch_import_reader(Rhead* rhead);
// 批量增加读者
void batch_add_reader(Rhead* rhead);
// 批量导入图书
void batch_import_book(Bhead* bhead);
// 批量增加图书
void batch_add_book(Bhead* bhead);
// 导出读者信息
void export_reader(Rhead* rhead);
// 导出图书信息
void export_book(Bhead* bhead);
bool _menu(ManagerMessage* managers,int* id);
// 读者管理界面
void __menu_reader();
void _menu_reader(Rhead* rhead,ManagerMessage* managers);
// 图书管理界面
void __menu_reader();
void _menu_book(Bhead* bhead,ManagerMessage* managers); 
// 界面
void menu_managers(Rhead* rhead,Bhead* bhead,ManagerMessage* managers);

#endif //MANAGEROPER_H
