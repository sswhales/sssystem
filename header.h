#pragma once//��ֹͷ�ļ��������
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS 1//���Ӿ���
#define MAX_num 20//ѧ���Ž̹���
#define MAX_grade 20//�༶
#define MAX_major 20//רҵ
#define MAX_sub 80//��Ŀ����
#define MAX_res 20//�ɼ�
#define MAX_post 20//��ʦְ��
#define MAX_type 20//��Ŀ����
#define MAX_state 60//�Ƿ�
#define MAX 10000
#define LEN sizeof(struct Node)
typedef struct UserInfo
{
	char Name[6];
	char Password[11];
}users;
typedef struct student
{
	char stu_num[MAX_num] ;//ѧ��
	char grade[MAX_grade];  //�༶
	char major[MAX_major];//רҵ
	char sub[MAX_sub];//��Ŀ����
	char result[MAX_res];//�ɼ�
	char tea_num[MAX_num];//�̹���
	char post[MAX_post]; //��ʦְ��
	char type[MAX_type];//��Ŀ����
	char state[MAX_state];// ��/�� 
}student;
struct Node
{
	struct student data;
	struct Node* next;
};
void LoginResult(int flag); //��¼�������
void agin(); //��������
void menu_main();	//���˵�
void menu_user(); // ��¼����
void menu_main_search();//��ѯ����
void menu_main_sort(); //�������
void Register();     //ע��
void logon();		//��¼
void addInfo(struct Node * ListHead,struct student data);//�����Ϣ
struct Node* creatlist();   //��������
struct Node *searchone(struct Node* ListHead ,char *num);//��ѯĳһ��
void printone(struct Node* posNode); //���ĳһ���ڵ����Ϣ
void delete_Num(struct Node* ListHead);//����ѧ��ɾ��

