#include"header.h"
void LoginResult(int flag)
{
	if(flag == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "登录失败，用户名不存在或密码错误！", "系统消息", MB_OK);
	}
	else 
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "登录成功！", "系统消息", MB_OK);
	}
}
//升级版注册
void Register()
{
	FILE *fp;
	if ((fp = fopen("User.dat","rb")) == NULL)	//信息文件不存在就创建一个
	{
		fp = fopen("User.dat","wb+");
		fclose(fp);
	}
	char User_Name[10];
	char User_Password[20];
	users temp; //临时结构体 typedef 改名
	InputBox(User_Name, 6 , "输入5个字符之内的用户名：");	//返回字符串 长度+1 内容
	if(strlen(User_Name) == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "用户名不能为空！", "系统消息", MB_OK);
		return ;
	}
	fp = fopen("User.dat","rb"); //读取User.txt文件
	fread(&temp, sizeof(struct UserInfo), 1, fp);
	//判断用户名是否存在
	while(true)
	{
		if(strcmp(User_Name,temp.Name) == 0) //用户名重复
		{
			fclose(fp); //关闭文件
			HWND wnd = GetHWnd();
			MessageBox(wnd, "该用户名已存在！", "系统消息", MB_OK);
			return ;		
		}
		else
		{
			if(!feof(fp)) //没到文件末尾 (到文件末尾feof()返回1) 
			fread(&temp, sizeof(struct UserInfo), 1, fp);
			else break;
		}
	}
	end :
	InputBox(User_Password, 11 , "输入10个字符以内的密码：");
	if(strlen(User_Password) == 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "密码不能为空！", "系统消息", MB_OK);
		goto end;
	}
	fp = fopen("User.dat","ab+");//文件尾追加数据
	strcpy(temp.Name,User_Name);
	strcpy(temp.Password,User_Password);
	fwrite(&temp, sizeof(struct UserInfo), 1, fp);//信息保存到文件
	fclose(fp);
	HWND wnd = GetHWnd();
	MessageBox(wnd, "注册成功!", "系统消息", MB_OK); 
}
void logon()
{
	FILE *fp;
	fp = fopen("User.dat","rb");//打开文件
	char User_Name[6];//用户名
	char User_Password[11];//密码
	InputBox(User_Name, 6 , "输入用户名：");
	InputBox(User_Password, 11 , "输入密码：");
	users temp;
	fread(&temp, sizeof(struct UserInfo), 1, fp);//二进制方式读取文件
	while(true)
	{
		if (strcmp(temp.Name, User_Name) == 0 &&strcmp(temp.Password,User_Password) == 0)//判断是否账号与密码均匹配
		{
				LoginResult(1);//登录成功
				fclose(fp);//关闭文件
				return menu_main();//进入主菜单界面
		}
		else
		{
			if(!feof(fp))//没到文件末尾接着读取
			{
				fread(&temp, sizeof(struct UserInfo), 1, fp);
			}
			else
			{
				 LoginResult(0); //登录失败
				 return ;//返回登录
			}
		}
	}
}