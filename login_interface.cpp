#include"header.h"
void LoginResult(int flag)
{
	if(flag == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "��¼ʧ�ܣ��û��������ڻ��������", "ϵͳ��Ϣ", MB_OK);
	}
	else 
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "��¼�ɹ���", "ϵͳ��Ϣ", MB_OK);
	}
}
//������ע��
void Register()
{
	FILE *fp;
	if ((fp = fopen("User.dat","rb")) == NULL)	//��Ϣ�ļ������ھʹ���һ��
	{
		fp = fopen("User.dat","wb+");
		fclose(fp);
	}
	char User_Name[10];
	char User_Password[20];
	users temp; //��ʱ�ṹ�� typedef ����
	InputBox(User_Name, 6 , "����5���ַ�֮�ڵ��û�����");	//�����ַ��� ����+1 ����
	if(strlen(User_Name) == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "�û�������Ϊ�գ�", "ϵͳ��Ϣ", MB_OK);
		return ;
	}
	fp = fopen("User.dat","rb"); //��ȡUser.txt�ļ�
	fread(&temp, sizeof(struct UserInfo), 1, fp);
	//�ж��û����Ƿ����
	while(true)
	{
		if(strcmp(User_Name,temp.Name) == 0) //�û����ظ�
		{
			fclose(fp); //�ر��ļ�
			HWND wnd = GetHWnd();
			MessageBox(wnd, "���û����Ѵ��ڣ�", "ϵͳ��Ϣ", MB_OK);
			return ;		
		}
		else
		{
			if(!feof(fp)) //û���ļ�ĩβ (���ļ�ĩβfeof()����1) 
			fread(&temp, sizeof(struct UserInfo), 1, fp);
			else break;
		}
	}
	end :
	InputBox(User_Password, 11 , "����10���ַ����ڵ����룺");
	if(strlen(User_Password) == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "���벻��Ϊ�գ�", "ϵͳ��Ϣ", MB_OK);
		goto end;
	}
	fp = fopen("User.dat","ab+");//�ļ�β׷������
	strcpy(temp.Name,User_Name);
	strcpy(temp.Password,User_Password);
	fwrite(&temp, sizeof(struct UserInfo), 1, fp);//��Ϣ���浽�ļ�
	fclose(fp);
	HWND wnd = GetHWnd();
	MessageBox(wnd, "ע��ɹ�!", "ϵͳ��Ϣ", MB_OK); 
}
void logon()
{
	FILE *fp;
	fp = fopen("User.dat","rb");//���ļ�
	char User_Name[6];//�û���
	char User_Password[11];//����
	InputBox(User_Name, 6 , "�����û�����");
	InputBox(User_Password, 11 , "�������룺");
	users temp;
	fread(&temp, sizeof(struct UserInfo), 1, fp);//�����Ʒ�ʽ��ȡ�ļ�
	while(true)
	{
		if (strcmp(temp.Name, User_Name) == 0 &&strcmp(temp.Password,User_Password) == 0)//�ж��Ƿ��˺��������ƥ��
		{
				LoginResult(1);//��¼�ɹ�
				fclose(fp);//�ر��ļ�
				return menu_main();//�������˵�����
		}
		else
		{
			if(!feof(fp))//û���ļ�ĩβ���Ŷ�ȡ
			{
				fread(&temp, sizeof(struct UserInfo), 1, fp);
			}
			else
			{
				 LoginResult(0); //��¼ʧ��
				 return ;//���ص�¼
			}
		}
	}
}