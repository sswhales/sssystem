#pragma once//防止头文件多次引用
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS 1//忽视警告
#define MAX_num 20//学工号教工号
#define MAX_grade 20//班级
#define MAX_major 20//专业
#define MAX_sub 80//项目名称
#define MAX_res 20//成绩
#define MAX_post 20//教师职称
#define MAX_type 20//项目类型
#define MAX_state 60//是否
#define MAX 10000
#define LEN sizeof(struct Node)
typedef struct UserInfo
{
	char Name[6];
	char Password[11];
}users;
typedef struct student
{
	char stu_num[MAX_num] ;//学号
	char grade[MAX_grade];  //班级
	char major[MAX_major];//专业
	char sub[MAX_sub];//项目名称
	char result[MAX_res];//成绩
	char tea_num[MAX_num];//教工号
	char post[MAX_post]; //教师职称
	char type[MAX_type];//项目类型
	char state[MAX_state];// 是/否 
}student;
struct Node
{
	struct student data;
	struct Node* next;
};
void LoginResult(int flag); //登录结果弹窗
void agin(); //重新输入
void menu_main();	//主菜单
void menu_user(); // 登录界面
void menu_main_search();//查询界面
void menu_main_sort(); //排序界面
void Register();     //注册
void logon();		//登录
void addInfo(struct Node * ListHead,struct student data);//添加信息
struct Node* creatlist();   //创建链表
struct Node *searchone(struct Node* ListHead ,char *num);//查询某一个
void printone(struct Node* posNode); //输出某一个节点的信息
void delete_Num(struct Node* ListHead);//根据学号删除

