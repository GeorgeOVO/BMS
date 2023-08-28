#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getch.h>
#include <unistd.h>
#include "superoper.h"
#include "manageroper.h"

// 创建读者
Rmanager* create_rmanager(void)
{
	Rmanager* rmanager = malloc(sizeof(Rmanager));
	rmanager->id = 0;
	rmanager->borrowed_book = 0;
	rmanager->order_book = 0;
	rmanager->val = 0;
	strcpy(rmanager->binformation_book[0],"无");
	strcpy(rmanager->oinformation_book[0],"无");
	strcpy(rmanager->binformation_book[1],"无");
	strcpy(rmanager->oinformation_book[1],"无");
	strcpy(rmanager->binformation_book[2],"无");
	strcpy(rmanager->oinformation_book[2],"无");
	rmanager->next = NULL;
	return rmanager;
}

// 创建图书
Bmanager* create_bmanager(void)
{
	Bmanager* bmanager = malloc(sizeof(Bmanager));
	bmanager->id = 0;
	bmanager->price = 0;
	bmanager->borrow_times = 0;
	bmanager->next = NULL;
	bmanager->in_pavilion = 0;
	bmanager->binformation_stu = 0;
	bmanager->oinformation_stu = 0;
	return bmanager;
}

// 创建读者头节点
Rhead* create_rhead()
{
	Rhead* rhead = malloc(sizeof(Rhead));
	rhead->cnt = 0;
	rhead->next = NULL;
	return rhead;
}

// 创建图书头节点
Bhead* create_bhead()
{
	Bhead* bhead = malloc(sizeof(Bhead));
	bhead->cnt = 0;
	bhead->next = NULL;
	return bhead;
}

int hash_reader[10000] = {};
int hash_book[10000] = {};

// 添加读者
void add_reader(Rhead* rhead)
{
	Rmanager* rmanager = create_rmanager();
	bool flag = true;
	printf("请输入读者姓名、密码、电话：");
	scanf("%s %d %s",rmanager->name,&(rmanager->pwd),rmanager->tel);
	if(strlen(rmanager->tel) > 11)
	{
		printf("电话输入有误！\n");
		return;
	}
	printf("添加成功\n");
	for(int i=1;i<10000;i++)
	{
		if(hash_reader[i])
		{
			rmanager->id = i;
			flag = false;
			rhead->cnt++;
			hash_reader[i] = 0;
			break;
		}
	}
	if(flag)
		rmanager->id = ++(rhead->cnt);
	// 找最后一个节点	
	if(NULL == rhead->next)
	{
		rhead->next = rmanager;
		return;
	}
	else
	{
		Rmanager* n = rhead->next;
		while(NULL != n->next) n = n->next;
		n->next = rmanager;
		return;
	}
}


// 添加图书
void add_book(Bhead* bhead)
{
	Bmanager* bmanager = create_bmanager();
	bool flag = true;
	printf("请输入书名、作者、出版日期、出版社、售价、图书状态：");
	scanf("%s %s %s %s %d %s",bmanager->book_name,bmanager->author,bmanager->publication_date,
			bmanager->press,&(bmanager->price),bmanager->book_status);
	printf("添加成功！\n");
	for(int i=1;i<10000;i++)
	{
		if(hash_book[i])
		{
			bmanager->id = i;
			flag = false;
			bhead->cnt++;
			hash_book[i] = 0;
			break;
		}
	}
	if(flag)
		bmanager->id = ++(bhead->cnt);
	// 找最后一个节点
	if(NULL == bhead->next) 
	{
		bhead->next = bmanager;
		return;
	}
	Bmanager* n = bhead->next;
	while(NULL != n->next) n = n->next;
	n->next = bmanager;
	return;
}

// 删除读者
bool delete_reader(Rhead* rhead)
{
	if(NULL == rhead->next)
	{
		printf("没有读者信息!\n");
		return false;
	}
	int del = 0;
	printf("请输入你想删除的读者ID：");
	scanf("%d",&del);
	for(Rmanager* n = rhead->next; n; n=n->next)
	{
		if(del == n->id)  // 删除的是读者结构体里的头节点
		{
			Rmanager* temp = n;
			rhead->next = temp->next;
			free(temp);
			rhead->cnt--;
			hash_reader[del] = 1;
			printf("删除成功！\n");
			return true;
		}
		else if(NULL != n->next && del == n->next->id)
		{
			Rmanager* temp = n->next;
			n->next = temp->next;
			free(temp);
			rhead->cnt--;
			hash_reader[del] = 1;
			printf("删除成功！\n");
			return true;
		}
	}
	printf("没有你想删除的读者id，删除失败！\n");
	return false;
}

// 删除图书
bool delete_book(Bhead* bhead)
{
	if(NULL == bhead->next)
	{
		printf("没有图书信息!\n");
		return false;
	}
	int del = 0;
	printf("请输入你想删除的图书编号：");
	scanf("%d",&del);
	for(Bmanager* n = bhead->next; n; n=n->next)
	{
		if(del == n->id) // 删除的是书本结构体里的头节点
		{
			Bmanager* temp = n;
			bhead->next = temp->next;
			free(temp);
			bhead->cnt--;
			hash_book[del] = 1;
			printf("删除成功！\n");
			return true;
		}
		else if(NULL != n->next && del == n->next->id)
		{
			Bmanager* temp = n->next;
			n->next = temp->next;
			free(temp);
			bhead->cnt--;
			hash_book[del] = 1;
			printf("删除成功！\n");
			return true;
		}
	}
	printf("没有你想删除的图书编号，删除失败！\n");
	return false;
}

// 读者排序
void sort_reader(Rhead* rhead)
{
	if(NULL == rhead->next) return;
	for(Rmanager* n=rhead->next; NULL!=n->next; n=n->next)
	{
		for(Rmanager* m=n->next; m; m=m->next)
		{
			if(n->id > m->id)
			{
				int id = n->id;
				n->id = m->id;
				m->id = id;
				char name[20];
				strcpy(name,n->name);
				strcpy(n->name,m->name);
				strcpy(m->name,name);
				int pwd = n->pwd;
				n->pwd = m->pwd;
				m->pwd = pwd;
				char tel[12];
				strcpy(tel,n->tel);
				strcpy(n->tel,m->tel);
				strcpy(m->tel,tel);
				int borrowed_book = n->borrowed_book;
				n->borrowed_book = m->borrowed_book;
				m->borrowed_book = borrowed_book;
				char binformation_book[3][30];
				for(int i=0; i<3; i++)
				{
					strcpy(binformation_book[i],n->binformation_book[i]);
					strcpy(n->binformation_book[i],m->binformation_book[i]);
					strcpy(m->binformation_book[i],binformation_book[i]);
				}
				int order_book = n->order_book;
				n->order_book = m->order_book;
				m->order_book = order_book;
				char oinformation_book[3][30];
				for(int i=0; i<3; i++)
				{
					strcpy(oinformation_book[i],n->oinformation_book[i]);
					strcpy(n->oinformation_book[i],m->oinformation_book[i]);
					strcpy(m->oinformation_book[i],oinformation_book[i]);
				}
				int val = n->val;
				n->val = m->val;
				m->val = n->val;
			}
		}
	}
}

// 列出所有读者
void show_reader(Rhead* rhead)
{
	if(NULL == rhead->next)
	{
		printf("没有读者信息!\n");
		return;
	}
	Rmanager* n = rhead->next;
	int i=0,a=0,c=3;            // c为翻页选项
	printf("分页显示读者的信息！\n");
	while(0 != c)
	{
		while(i < 10)
		{	
			sort_reader(rhead);
			printf("id：%d 姓名：%s 电话：%s 已借图书数：%d 已借图书信息：",
					n->id,n->name,n->tel,n->borrowed_book);
			printf("%s %s %s ",n->binformation_book[0],n->binformation_book[1],n->binformation_book[2]);
			printf("预约图书数：%d 预约图书信息：%s %s %s\n",n->order_book,n->oinformation_book[0],
					n->oinformation_book[1],n->oinformation_book[2]);
			n = n->next;
			a++; // a为翻页变量
			i++;
			if(a == rhead->cnt) i = 10;  //设置输出终点
		}
Show:
		printf("输入1为上一页，输入2为下一页,输入0为结束显示\n");
		printf("请输入你的选择：");
		scanf("%d",&c);
		if(1 == c)
		{
			if(a <= 10)
			{
				n = rhead->next;
				a = 0;
				system("clear");
				printf("本页为第一页！\n");
			}
			else 
			{
				if(0 == a%10)		// 在本页翻上一页时判断本页是否满十个人
					a = a-20;          // 回到上一页开始位置
				else
					a = a-10-a%10;
				n = rhead->next;
				for(i=0; i<a; i++) 
					n = n->next;
				system("clear");
			}
		}
		else if(2 == c)
		{
			if(a == rhead->cnt)
			{
				if(0 == a%10)
					a = a-10;   // 最后一页
				else
					a = a-a%10;
				n = rhead->next;
				for(i=0; i<a; i++)
					n = n->next;
				system("clear");
				printf("本页为最后一页！\n");
			}
		}
		else if(0 == c)
		{
			printf("退出显示成功\n");
			return;
		}
		else
		{
			printf("选择有误，请重新选择\n");
			goto Show;
		}
		i=0;
		system("clear");
	}
}

// 修改图书信息
bool modify_book(Bhead* bhead)
{
	if(NULL == bhead->next)
	{
		printf("没有图书信息!\n");
		return false;
	}
	int mod = 0;
	printf("请输入你想修改的图书编号：");
	scanf("%d",&mod);
	Bmanager* n = bhead->next;
	while(NULL != n)
	{
		if(mod == n->id)
		{
			int num = 0;
			while(1)
			{
				printf("选择你想修改图书的哪项信息：1、书名 2、作者 3、出版日期 4、出版社 5、售价 6、退出\n");
				scanf("%d",&num);
				switch(num)
				{
					case 1:
						printf("请输入新的书名：");
						scanf("%s",n->book_name);
						printf("修改成功！\n");
						break;
					case 2:
						printf("请输入新的作者：");
						scanf("%s",n->author);
						printf("修改成功！\n");
						break;
					case 3:
						printf("请输入新的出版日期：");
						scanf("%s",n->publication_date);
						printf("修改成功！\n");
						break;
					case 4:
						printf("请输入新的出版社：");
						scanf("%s",n->press);
						printf("修改成功！\n");
						break;
					case 5:
						printf("请输入新的售价：");
						scanf("%d",&(n->price));
						printf("修改成功！\n");
						break;
					case 6:
						printf("退出成功！\n");
						return true;
					default:
						printf("输入错误，请重新输入\n");
						break;
				}	
			}
		}
		n = n->next;
	}
	printf("没有你想修改的图书！\n");
	return false;
}

// 根据图书编号查找
bool _search_num(Bhead* bhead)
{
	int num = 0;
	printf("请输入图书编号：");
	scanf("%d",&num);
	if(num > bhead->cnt)
	{
		printf("没有你想查找的图书编号！\n");
		return false;
	}
	for(Bmanager* n = bhead->next; n; n=n->next)
	{
		if(num == n->id)
		{
			printf("编号：%d 书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
					n->id,n->book_name,n->author,n->publication_date,n->press,n->price,n->borrow_times,n->book_status);
			return true;
		}
	}
	printf("没有你想查找的图书编号！\n");
	return false;
}

// 根据书名查找
void _search_name(Bhead* bhead)
{
	int i,j,cnt = 0;
	Bmanager* n = bhead->next;
	char name[50];                  // 模糊查找的字符串
	printf("请输入你想查找的书名：");
	scanf("%s",name);
	while(n)
	{
		if(strstr(n->book_name,name))
		{
			printf("编号：%d 书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
				n->id,n->book_name,n->author,n->publication_date,n->press,n->price,n->borrow_times,n->book_status);
			cnt++;
		}
		n = n->next;
	}
	if(0 == cnt)
		printf("没有你想查找的图书\n");
}

// 根据作者查找
void _search_author(Bhead* bhead)
{
	int i,j,cnt = 0;
	Bmanager* n = bhead->next;
	char name[50];                  // 模糊查找的字符串
	printf("请输入你想查找的作者：");
	scanf("%s",name);
	while(n)
	{
		if(strstr(n->author,name))
		{
			printf("编号：%d 书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
			n->id,n->book_name,n->author,n->publication_date,n->press,n->price,n->borrow_times,n->book_status);
			cnt++;
		}
		n = n->next;
	}
	if(0 == cnt)
		printf("没有你想查找的作者\n");
}

// 查找图书
bool search_book(Bhead* bhead)
{
	if(NULL == bhead->next)
	{
		printf("没有图书信息!\n");
		return false;
	}
	int num = 0;
	while(1)
	{
		printf("请选择：1、根据图书编号查找 2、根据书名查找 3、根据作者查找 4、退出\n");
		scanf("%d",&num);
		switch(num)
		{
			case 1:
				_search_num(bhead);
				break;
			case 2:
				_search_name(bhead);
				break;
			case 3:
				_search_author(bhead);
				break;
			case 4:
				return true;
			default:
				printf("选择有误，请重新输入\n");
				break;
		}
	}
}

// 列出所有图书
void show_book(Bhead* bhead)
{
	if(NULL == bhead->next)
	{
		printf("没有图书信息!\n");
		return;
	}
	Bmanager* n = bhead->next;
	int i=0,a=0,c=3;            // c为翻页选项
	printf("分页显示图书的信息！\n");
	while(0 != c)
	{
		while(i < 10)
		{
			printf("编号：%d 书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
					n->id,n->book_name,n->author,n->publication_date,n->press,n->price,n->borrow_times,n->book_status);
			n = n->next;
			a++; // a为翻页变量
			i++;
			if(a == bhead->cnt) i = 10;  //设置输出终点
		}
Show1:
		printf("输入1为上一页，输入2为下一页,输入0为结束显示\n");
		printf("请输入你的选择：");
		scanf("%d",&c);
		if(1 == c)
		{
			if(a <= 10)
			{
				n = bhead->next;
				a = 0;
				printf("本页为第一页！\n");
			}
			else 
			{
				if(0 == a%10)		// 在本页翻上一页时判断本页是否满十个人
					a = a-20;          // 回到上一页开始位置
				else
					a = a-10-a%10;
				n = bhead->next;
				for(i=0; i<a; i++) 
					n = n->next;
			}
		}
		else if(2 == c)
		{
			if(a == bhead->cnt)
			{
				if(0 == a%10)
					a = a-10;   // 最后一页
				else
					a = a-a%10;
				n = bhead->next;
				for(i=0; i<a; i++)
					n = n->next;
				printf("本页为最后一页！\n");
			}
		}
		else if(0 == c)
		{
			printf("退出显示成功\n");
			return;
		}
		else
		{
			printf("选择有误，请重新选择\n");
			goto Show1;
		}
		i=0;
	}
}

Rmanager*  _reader_id(Rmanager* n,int id)
{
	while(n)
	{
		if(id == n->id)
		{
			return n;
		}
		n = n->next;
	}
	return n;
}

Rmanager* _reader_name(Rmanager* n,char* name)
{
	while(n)
	{
		if(0 == strcmp(name,n->name))
			return n;
		n = n->next;
	}
	return n;
}

// 读者充值
void recharge_val(Rhead* rhead)
{
	if(NULL == rhead->next)
	{
		printf("没有读者信息!\n");
		return;
	}
	Rmanager* n = rhead->next;
	int id = 0;
	char name[20];
Choice:	
	printf("请选择你的输入：1、id 2、姓名 0、退出：");
	switch(getch())
	{
		case '1':
			printf("\n请输入你的id：");
			scanf("%d",&id);
			n = _reader_id(n,id);
			break;
		case '2':
			printf("\n请输入你的名字：");
			scanf("%s",name);
			n = _reader_name(n,name);
			break;
		case '0':
			return;
		default:
			printf("选择错误\n");
			goto Choice;
	}
	if(NULL == n)
	{
		printf("没有你的读者信息!\n");
		return;
	}
	int val = 0;
	printf("请输入你想充值的金额：");
	scanf("%d",&val);
	if(val < 0 || val > 1000)
	{
		printf("充值金额有误！\n");
		return;
	}
	n->val += val;
	printf("你的余额为:%d",n->val);	
}

// 修改密码
bool modify_pwd(ManagerMessage* managers)
{
	int id = 0,cnt = 3;
	int pwd;
	printf("请输入你的id：");
	scanf("%d",&id);
	if(id > MAX_MANAGER_NUM) return false;
Pwd:
	printf("你有%d次机会输入旧密码\n",cnt);
	printf("请输入旧密码：");
	scanf("%d",&pwd);
	if(pwd == managers[id-1].pwd)
	{
Pwd1:
		printf("请输入四位数字新密码：");
		scanf("%d",&(managers[id-1].pwd));
		if(managers[id-1].pwd/10000 !=0 || managers[id-1].pwd/1000 == 0)
		{
			printf("密码必须为四位数字!\n");
		   	goto Pwd1;	
		}
		printf("密码修改成功！\n");
		return true;
	}
	else
	{
		if(cnt > 1)
		{
			printf("密码输入有误，请重新输入!\n");
			cnt--;
		}
		else
		{
			printf("密码输入机会已用完\n");
			return false;
		}
		goto Pwd;
	}	
}

// 批量增加读者
void batch_add_reader(Rhead* rhead)
{
	int cnt = 0;
	FILE* R = fopen("add_reader.txt","r");
	if(NULL == R)
	{
		printf("没有可导入的文件！\n");
		return;
	}
	char name[20];
	while(fscanf(R,"%s ",name) > 0)
	{
		Rmanager* rmanager = create_rmanager();
		strcpy(rmanager->name,name);
		fscanf(R,"%d %s\n",&(rmanager->pwd),rmanager->tel);
		rmanager->id = ++(rhead->cnt);
		cnt++;
		_add_reader(rhead,rmanager);
	}
	if(0 == cnt)
		printf("没有可导入信息！\n");
	else
		printf("导入成功！\n");	
}

// 批量增加图书
void batch_add_book(Bhead* bhead)
{
	int cnt = 0;
	FILE* B = fopen("add_book.txt","r");
	if(NULL == B)
	{
		printf("没有可导入的文件！\n");
		return;
	}
	char book_name[20];
	while(fscanf(B,"%s ",book_name) > 0)
	{
		Bmanager* bmanager = create_bmanager();
		strcpy(bmanager->book_name,book_name);
		fscanf(B,"%s %s %s %d\n",bmanager->author,bmanager->publication_date,bmanager->press,&(bmanager->price));
		bmanager->id = ++(bhead->cnt);
		strcpy(bmanager->book_status,"在馆无预约");
		cnt++;
		_add_book(bhead,bmanager);
	}
	if(0 == cnt)
		printf("没有可导入信息！\n");
	else
		printf("导入成功！\n");	
}

void _add_reader(Rhead* rhead,Rmanager* rmanager)
{
	if(NULL == rhead->next)
	{
		rhead->next = rmanager;
		return;
	}
	else
	{
		Rmanager* n = rhead->next;
		while(NULL != n->next) n = n->next;
		n->next = rmanager;
		return;
	}
}


// 批量导入读者
void batch_import_reader(Rhead* rhead)
{
	FILE* R = fopen("reader.txt","r");
	if(NULL == R)
	{
		printf("没有可导入的文件！\n");
		return;
	}
	int cnt = 0;
	int id,pwd,book,obook;
	char name[20],tel[12];
	// 导入文件中已有读者
	while(fscanf(R,"id：%d 姓名：%s 密码：%d 电话：%s 已借图书数：%d 已借图书信息："
					,&id,name,&pwd,tel,&book) > 0)
	{	
		Rmanager* rmanager = create_rmanager();
		rmanager->id = id;
		strcpy(rmanager->name,name);
		rmanager->pwd = ~pwd;
		strcpy(rmanager->tel,tel);
		rmanager->borrowed_book = book;
		fscanf(R,"%s %s %s 预约图书数：%d 预约图书信息：%s %s %s\n",
			rmanager->binformation_book[0],rmanager->binformation_book[1],rmanager->binformation_book[2]
			,&(rmanager->order_book),rmanager->oinformation_book[0],rmanager->oinformation_book[1],rmanager->oinformation_book[2]);
		rhead->cnt++;
		cnt++;
		_add_reader(rhead,rmanager);
	}
	fclose(R);
}

void _add_book(Bhead* bhead,Bmanager* bmanager)
{
	if(NULL == bhead->next) 
	{
		bhead->next = bmanager;
		return;
	}
	Bmanager* n = bhead->next;
	while(NULL != n->next) n = n->next;
	n->next = bmanager;
	return;
}

// 批量导入图书
void batch_import_book(Bhead* bhead)
{	
	FILE* B = fopen("book.txt","r");
	if(NULL == B)
	{
		printf("没有可导入的文件！\n");
		return;
	}
	int id,cnt = 0;
	// 导入文件中已有图书
	while(fscanf(B,"编号：%d ",&id) > 0)
	{
		Bmanager* bmanager = create_bmanager();
		bmanager->id = id;
		fscanf(B,"书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
				bmanager->book_name,bmanager->author,bmanager->publication_date,bmanager->press,
				&(bmanager->price),&(bmanager->borrow_times),bmanager->book_status);
		bhead->cnt++;
		_add_book(bhead,bmanager);
	}
	fclose(B);
}

// 导出读者信息
void export_reader(Rhead* rhead)
{
	if(NULL == rhead->next)
	{
		printf("没有读者信息可以导出\n");
		return;
	}
	FILE* R = fopen("reader.txt","w");
	Rmanager* r = rhead->next;
	while(r != NULL)
	{
		fprintf(R,"id：%d 姓名：%s 密码：%d 电话：%s 已借图书数：%d 已借图书信息：",
				r->id,r->name,~(r->pwd),r->tel,r->borrowed_book);
		fprintf(R,"%s %s %s 预约图书数：%d 预约图书信息：%s %s %s\n",r->binformation_book[0],
					r->binformation_book[1],r->binformation_book[2],
					r->order_book,r->oinformation_book[0],r->oinformation_book[1],r->oinformation_book[2]);
		r = r->next;
	}
	fclose(R);
	return;
}

// 导出图书信息
void export_book(Bhead* bhead)
{
	if(NULL == bhead->next)
	{
		printf("没有图书信息可以导出\n");
		return;
	}
	FILE* B = fopen("book.txt","w");
	Bmanager* b = bhead->next;
	while(b != NULL)
	{
		fprintf(B,"编号：%d 书名：%s 作者：%s 出版日期：%s 出版社：%s 售价：%d 借阅次数：%d 图书状态：%s\n",
				b->id,b->book_name,b->author,b->publication_date,b->press,b->price,b->borrow_times,b->book_status);
		b = b->next;
	}
	fclose(B);
	return;
}

bool _menu(ManagerMessage* managers,int* id)
{
	int pwd,cnt = 3;
	printf("请输入你的id：");
	scanf("%d",id);
	if(*id > manager_num) 
	{	
		printf("id输入有误\n");
		return false;
	}
ManagerPwd:
	printf("你有%d次机会输入密码\n",cnt);
	printf("请输入你的密码：");
	scanf("%d",&pwd);
	if(pwd == managers[*id-1].pwd)
	{
		printf("欢迎登录！\n");
		return true;
	}
	else
	{	
		if(cnt > 1)
		{
			printf("密码错误\n");
			cnt--;
			goto ManagerPwd;
		}
		else
		{
			printf("机会用完\n");
			return false;
		}
	}
	return false;
}

void __menu_reader()
{
	sleep(1);	
	system("clear");
	puts("1、添加读者");
	puts("2、删除读者");
	puts("3、列出所有读者");
	puts("4、批量增加读者");
	puts("5、读者充值");
	puts("6、修改密码");
	puts("7、退出系统");
	printf("请输入你的选择:");
}

void __menu_book()
{
	sleep(1);
	system("clear");
	puts("1、添加图书");
	puts("2、删除图书");
	puts("3、修改图书信息");
	puts("4、查找图书");
	puts("5、列出所有图书信息");
	puts("6、修改密码");
	puts("7、批量增加图书");
	puts("8、退出系统");
	printf("请输入你的选择:");
}

// 读者管理界面
void _menu_reader(Rhead* rhead,ManagerMessage* managers)
{	
		while(1)
		{
			__menu_reader();
			int cmd = getch();
			stdin->_IO_read_ptr = stdin->_IO_read_ptr;
			printf("%c\n",cmd);    // 为了显示输入
			switch(cmd)
			{
				case '1':
					add_reader(rhead);
					break;
				case '2':
					delete_reader(rhead);
					break;
				case '3':
					show_reader(rhead);
					break;
				case '4':
					batch_add_reader(rhead);
					break;
				case '5':
					recharge_val(rhead);
					break;
				case '6':
					modify_pwd(managers);
					break;
				case '7':
					printf("退出成功\n");
					return;
				default:
					break;
			}
			stdin->_IO_read_ptr = stdin->_IO_read_ptr;			
	}
}

// 图书管理界面
void _menu_book(Bhead* bhead,ManagerMessage* managers)
{
		while(1)
		{
			__menu_book();
			int cmd = getch();
			printf("%c\n",cmd);    // 为了显示输入
			switch(cmd)
			{
				case '1':
					add_book(bhead);
					break;
				case '2':
					delete_book(bhead);
					break;
				case '3':
					modify_book(bhead);
					break;
				case '4':
					search_book(bhead);
					break;
				case '5':
					show_book(bhead);
					break;
				case '6':
					modify_pwd(managers);
					break;
				case '7':
					batch_add_book(bhead);
					break;
				case '8':
					printf("退出系统成功\n");
					return;
				default:
					break;
		}
	}
}

// 界面
void menu_managers(Rhead* rhead,Bhead* bhead,ManagerMessage* managers)
{
//		system("clear");
		int id;
		if(_menu(managers,&id))
		{
			switch(managers[id-1].station)
			{
				case 0:
					_menu_reader(rhead,managers);
					break;
				case 1:
					_menu_book(bhead,managers);
					break;
				default:
					break;
			}
		}
}
Rhead* rhead;
Bhead* bhead;
//	加载头节点
void load_head()
{
	 rhead = create_rhead();
	 bhead = create_bhead();
}

int main()
{
//	Rhead* rhead = create_rhead();
//	Bhead* bhead = create_bhead();
	load_head();
	batch_import_reader(rhead);
	batch_import_book(bhead);
	managers[0].pwd = 1234;
	manager_num++;
	menu_managers(rhead,bhead,managers);
	export_reader(rhead);
	export_book(bhead);
}
