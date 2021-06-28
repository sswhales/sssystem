
#include"header.h"
struct Node *list;
struct Infonum
{
	char teanum[MAX_num];//教工号
	char gradename[MAX];//班级
	int num_peo;//人数
	int num_excellent;//优人数
	int num_good;//良人数
	int num_medium;//中人数
	int num_pass;//及格人数
}arr[MAX];
struct temp
{
	char stu_num[MAX_num] ;//学号
	char grade[MAX_grade];  //班级
	char major[MAX_major];//专业
	char sub[MAX_sub];//项目
	char result[MAX_res];//成绩
	char tea_num[MAX_num];//教工号
	char post[MAX_post]; //教师职称
	char type[MAX_type];//类型
	char state[MAX_state];// 是/否 
}a[MAX];
struct teacher //抽查信息中教师数据
{
	char te_num[MAX_num];//教工号
	int ecxellent;	//该教工号被抽查的优的人数
	int pass;	//该教工号被抽查的及格的人数
	int isnew;	//是否近三年新进教师
	int check_tnum;//每个教师被抽查的总人数
};
struct Grades
{
	char gradename[MAX_grade];//班级名字
	int num_checkclass;//每个班被抽查人数 
};
struct Spotcheck
{
	int ischecked[MAX];//学生是否被抽查过
	int total_tnum;//教师总数量
	int total_cnum;//班级总数量
	struct teacher t_arr[MAX];
	struct Grades class_arr[MAX];
	int good; //已抽查 良 的人数
	int medium; //已抽查 中 的人数
}spot;
// 判断是不是新进教师  且  判断是否已经抽走一个
int judgenew(char t_num[])
{
	int i;
	for(i = 0 ;i < spot.total_tnum ;i++)
	{//遍历信息找到对应教工号
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0)
		{
			if(spot.t_arr[i].isnew == 1)//如果是新进教师
			{
				if(spot.t_arr[i].check_tnum == 0) return 1;//如果被抽查人数为0 返回1
				else return 0;
			}
			else return 0;
		}
	}
}
//初始化抽查数据
void inispotcheck()
{
	int i,nowyear,pastyear,j,J;
	char Now[4],Past[4];//判断新进教师的年份区间
	struct Node *k = list ->next;
	time_t now;
	time(&now);
	struct tm*p;
	p = gmtime(&now);
	nowyear = 1900+p->tm_year;//当前年份
	pastyear = nowyear - 3;
	nowyear = nowyear + 1;//用于判断当前年份的加工号子
	j = 3;
	while(nowyear != 0)//存入字符数组
	{
			Now[j] = nowyear%10 + 48;
			Past[j] = pastyear%10 + 48;
			nowyear /= 10;
			pastyear /= 10;
			j--;
	}
	//初始化总抽查数据
	spot.good = 0;
	for(i = 0; i < MAX ;i++)
	{
		spot.ischecked[i] = 0;//全部为0表示未被抽查
	}
	spot.medium = 0;//中 被抽人数
	spot.total_cnum = 0;//班级人数
	spot.total_tnum = 0;//教师人数
	//初始化教师数据
	while(k != NULL)
	{//遍历信息 记录每一个2教师
		for(i = 0; i < spot.total_tnum ;i++)
		{
			if(strcmp(spot.t_arr[i].te_num,k->data.tea_num) == 0)
				break;
		}
		if(i == spot.total_tnum)
		{
			strcpy(spot.t_arr[i].te_num,k->data.tea_num);
			spot.t_arr[i].ecxellent = 0;//教师被抽优人数
			spot.t_arr[i].pass = 0;//教师被抽及格人数
			spot.total_tnum ++;//教师数量+1
			spot.t_arr[i].check_tnum = 0;
			if(strcmp(spot.t_arr[i].te_num,Now) == -1 && strcmp(spot.t_arr[i].te_num,Past) == 1 )
			{
				spot.t_arr[i].isnew = 1;//1表示是新进教师
			}
			else spot.t_arr[i].isnew = 0;//0表示不是新进教师
		}
		k = k->next;
	}
	//初始化班级数据
	spot.total_cnum = 0;
	k= list ->next;
	while(k != NULL)
	{//遍历信息 记录所有班级名称
		for(i = 0;i < spot.total_cnum ;i++)
		{
			if(strcmp(spot.class_arr[i].gradename,k->data.grade) == 0)
				break;
		}
		if(i == spot.total_cnum)
		{
			strcpy(spot.class_arr[i].gradename,k->data.grade);
			spot.total_cnum ++;//班级数量+1
			spot.class_arr[i].num_checkclass = 0;//班级被抽人数为0
		}
		k = k->next;
	}
}
int teaexcellent(char t_num[])
{
	int i ;
	for(i = 0;i < spot.total_tnum  ;i++)
	{//遍历信息找到对应教工号 判断该教师被抽查优人数是否为0
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0 && spot.t_arr[i].ecxellent == 0)
		{
			spot.t_arr[i].ecxellent ++;
			return 0;
		}
	}
	return 1;
}
//判断教师是否已经抽走 及格
int teapass(char t_num[])
{
	int i ;
	for(i = 0;i < spot.total_tnum  ;i++)
	{//遍历信息找到对应教工号 判断该教师被抽查及格人数是否为0
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0 && spot.t_arr[i].pass == 0)
		{
			spot.t_arr[i].pass ++;
			return 0;
		}
	}
	return 1;
}
//对应教师数据更新
void addteacher(char result[],char t_num[])
{
	int i;
	for(i = 0;i < spot.total_tnum ;i++)
	{//找到对应教师
		if(strcmp(spot.t_arr[i].te_num,t_num) == 0)
		{
			spot.t_arr[i].check_tnum ++;//该教师被抽查人数+1
			if(strcmp(result,"优") == 0) spot.t_arr[i].ecxellent ++;//该教师被抽优人数+1
			if(strcmp(result,"及格") == 0) spot.t_arr[i].pass ++;//该教师被抽及格人数+1
			if(strcmp(result,"中") == 0) spot.medium++;//中 总体被抽人数+1
			if(strcmp(result,"良") == 0)	spot.good++;//良 总体被抽人数+1
			break;
		}
	}
}
//对应班级人数+1
void addgrade(char gradename[])
{
	int i;
	for(i = 0;i < spot.total_cnum ;i++)
	{//遍历信息找到对应班级
		if(strcmp(gradename,spot.class_arr[i].gradename) == 0)
		{
			spot.class_arr[i].num_checkclass ++;//该班级被抽人数+1
			break;
		}
	}
}
//判断是否是应届班级 是返回1 否返回0
int is_thisyear(char classname[])
{
	int year1;
	time_t now;
	time(&now);
	struct tm*p;
	p = gmtime(&now);
	//班级名字形式前两个字符判断
	year1 = 1900+p->tm_year - 2000 - 4;
	char Year1[2];
	if(p->tm_mon < 7)//根据月份 判断应届班级的年份
	{
		year1 -= 1;
	}
	//printf("%d\n",year1);
	int j = 1;
	while(year1 != 0)
	{
		Year1[j] = year1 % 10 +48;
		year1 /= 10;
		j --;
	}
	//例如16    16计科 前两个字符相同
	if(classname[0] == Year1[0] && classname[1] == Year1[1]) return 1;
	else return 0;
}
//判断该应届班级被抽走数量是否小于最大数量  是返回1 否返回0
int is_lessclass(char classname[])
{
	int i,max_num = 0;//被抽查最大数
	for(i = 0;i < spot.total_cnum ;i++)
	{//遍历信息找到应届班级最大抽查数
		if(is_thisyear(spot.class_arr[i].gradename) == 1)
		{//判断是否是应届班级
			if(max_num < spot.class_arr[i].num_checkclass)
			{
				max_num = spot.class_arr[i].num_checkclass;
			}
		}
	}
	//printf("%d\n",is_thisyear(spot.class_arr[1].gradename));
	for(i = 0;i < spot.total_cnum ;i++)
	{
		if(strcmp(classname,spot.class_arr[i].gradename) == 0)
		{//判断是否小于max_num
			if(spot.class_arr[i].num_checkclass < max_num) return 1;//是
			else return 0;//否
		}
	}
}
//判断教师被抽数量是否小于最大数量  是返回1 否返回0
int is_lessteacher(char t_num[])
{
	int i,max_num = 0;//被抽查最大数
	for(i = 0;i < spot.total_tnum ;i++)//遍历信息
	{
		if(max_num < spot.t_arr[i].check_tnum)
			{
				max_num = spot.t_arr[i].check_tnum;
			}
	}
	for(i = 0;i < spot.total_cnum ;i++)
	{
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0)//找到对应教工号判断是否小于抽查最大数
		{
			if(spot.t_arr[i].check_tnum < max_num) return 1;//是
			else return 0;//否
		}
	}
}
void spotcheck()
{
	FILE * fp;
	fp = fopen("抽查信息.txt","w");//打开此文件
	fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号",
		"指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");//写入标题
	closegraph();//关闭图形
	system("cls");//控制台清屏
	printf("抽查结果如下：    \n");
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号",
		"指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");
	struct Node *k = list;
	k = (k->next)->next; //表头为空 next是标题  再下一个是元素数据
	int i,swapa,swapb;
	int cnt = 0; //从0到cnt-1
	while(k != NULL)//遍历链表 复制信息到结构体变量中
	{
		strcpy(a[cnt].stu_num,k->data.stu_num);
		strcpy(a[cnt].grade,k->data.grade);
		strcpy(a[cnt].major,k->data.major);
		strcpy(a[cnt].sub,k->data.sub);
		strcpy(a[cnt].result,k->data.result);
		strcpy(a[cnt].tea_num,k->data.tea_num);
		strcpy(a[cnt].post,k->data.post);
		strcpy(a[cnt].type,k->data.type);
		strcpy(a[cnt].state,k->data.state);
		cnt++;//信息数量
		k = k->next;
	}
	inispotcheck();//初始化抽查数据
	struct temp c;//临时变量 用于交换两组信息
	for(i = 0;i < MAX ;i++)
	{
		swapa = rand()%cnt;//生成两个随机数用于二者交换
		swapb = rand()%cnt;
		strcpy(c.stu_num,a[swapa].stu_num);
		strcpy(c.grade,a[swapa].grade);
		strcpy(c.major,a[swapa].major);
		strcpy(c.sub,a[swapa].sub);
		strcpy(c.result,a[swapa].result);
		strcpy(c.tea_num,a[swapa].tea_num);
		strcpy(c.post,a[swapa].post);
		strcpy(c.type,a[swapa].type);
		strcpy(c.state,a[swapa].state);
		
		strcpy(a[swapa].stu_num,a[swapb].stu_num);
		strcpy(a[swapa].grade,a[swapb].grade);
		strcpy(a[swapa].major,a[swapb].major);
		strcpy(a[swapa].sub,a[swapb].sub);
		strcpy(a[swapa].result,a[swapb].result);
		strcpy(a[swapa].tea_num,a[swapb].tea_num);
		strcpy(a[swapa].post,a[swapb].post);
		strcpy(a[swapa].type,a[swapb].type);
		strcpy(a[swapa].state,a[swapb].state);

		strcpy(a[swapb].stu_num,c.stu_num);
		strcpy(a[swapb].grade,c.grade);
		strcpy(a[swapb].major,c.major);
		strcpy(a[swapb].sub,c.sub);
		strcpy(a[swapb].result,c.result);
		strcpy(a[swapb].tea_num,c.tea_num);
		strcpy(a[swapb].post,c.post);
		strcpy(a[swapb].type,c.type);
		strcpy(a[swapb].state,c.state);
	}
	float cn = cnt/5.0 +0.5;
	int spotcheck_num = (int) cn;//抽查总人数 全部的20%  四舍五入
	int curr_num = 0; //记录当前抽取的人数
	//抽取教师指导存在  优  的
	for(i = 0;i < cnt ;i++)
	{
		if(curr_num >= spotcheck_num) break;//达到最大抽查数跳出
		if(spot.ischecked[i] == 0 && strcmp(a[i].result,"优") == 0 && teaexcellent(a[i].tea_num) == 0)
		{//满足条件：未被抽查 成绩为优 对应教工号未被抽取优 这三个条件就被抽查
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//被抽查为1
			curr_num ++;//当前抽查数+1
			addteacher(a[i].result,a[i].tea_num);//对应教师抽查数+1 优 +1
			addgrade(a[i].grade); //对应班级人数 +1
		}
	}
	//抽取教师指导存在 及格 的
	for(i = 0;i < cnt ;i++)
	{
		if(curr_num >= spotcheck_num) break;//达到最大抽查数跳出
		if(spot.ischecked[i] == 0 && strcmp(a[i].result,"及格") == 0 && teapass(a[i].tea_num) == 0)
		{//满足条件：未被抽查 成绩为及格 对应教工号未被抽取及格 这三个条件就被抽查
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//被抽查为1
			curr_num ++;//当前人数+1
			addteacher(a[i].result,a[i].tea_num);//对应教师抽查数+1 及格 +1
			addgrade(a[i].grade); //对应班级人数 +1
		}
	}
	//抽取三年新进教师
	for(i = 0 ;i < cnt ;i ++)
	{
		if(curr_num >= spotcheck_num) break;//达到最大抽查数跳出
		if(spot.ischecked[i] == 0 && judgenew(a[i].tea_num) == 1)
		{//满足 未被抽查 是近三年教师且未被抽取 这两个条件就被抽走
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,
				a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,
				a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//被抽取为1
			curr_num ++;//当年抽取人数+1
			addteacher(a[i].result,a[i].tea_num);//更新教师中被抽 优 和 及格 以及总抽查中 良 和 中
			addgrade(a[i].grade); //对应班级人数 +1
		}
	}
	//由最后三个条件 把人数抽够
	while(curr_num < spotcheck_num)
	{
		//保证良 和 中 数量尽量相等
		if(spot.good < spot.medium) //抽良
		{
			for(i = 0 ;i < cnt ;i ++)
			{
				if(spot.good == spot.medium) break;//中与良数量相同则跳出
				if(curr_num >= spotcheck_num) break;//达到最大抽查数则跳出
				if(spot.ischecked[i] == 0 && strcmp(a[i].result,"良") == 0)
				{//未被抽查且成绩为良
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//被抽查为1
					curr_num ++;//当前抽查人数+1
					addteacher(a[i].result,a[i].tea_num);//主要更新教师被抽总数
					addgrade(a[i].grade); //对应班级人数 +1
				}
			}
		}
		else if(spot.good > spot.medium) //抽中
		{
			for(i = 0 ;i < cnt ;i ++)
			{
				if(spot.good == spot.medium) break;//中与良数量相同则跳出
				if(curr_num >= spotcheck_num) break;//达到最大抽查数则跳出
				if(spot.ischecked[i] == 0 && strcmp(a[i].result,"中") == 0)
				{//未被抽查且成绩为中
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//被抽查为1
					curr_num ++;//当前抽查人数+1
					addteacher(a[i].result,a[i].tea_num);//主要更新教师被抽总数
					addgrade(a[i].grade); //对应班级人数 +1
				}
			}
		}
		else if(spot.good == spot.medium && spot.good == 0)//如果二者相同且未被抽取 则任意抽取一个 中或者良
		{
			for(i = 0 ;i < cnt ;i++)
			{
				if(curr_num >= spotcheck_num) break;//达到最大抽查数则跳出
				if(spot.ischecked[i] == 0 &&((strcmp(a[i].result,"中") == 0)||(strcmp(a[i].result,"良") ==0)))
				{//为被抽查 且成绩为中或者良
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//被抽查为1
					curr_num ++;//当前抽查人数+1
					addteacher(a[i].result,a[i].tea_num);//主要更新 教师被抽数量 总抽查数 良和中 被抽数量
					addgrade(a[i].grade); //对应班级人数 +1
					break;//抽取一个即可跳出
				}
			}
		}
		else if(spot.good == spot.medium && spot.good != 0)//中与良数量相同且数量不为0  保证应届班级被抽数相同 以及 保证教师被抽数相同
		{
			//使得各班级抽取人数尽量相同 如果存在一个应届班级被抽数量小于所有应届班级中被抽的最大值 则抽它 每次抽取一个以实现规则的先后顺序
			for(i = 0;i < cnt ;i++)
			{
				
				if(curr_num >= spotcheck_num) break;//达到最大抽查数则跳出
				if(spot.ischecked[i] == 0 && is_thisyear(a[i].grade) == 1 && is_lessclass(a[i].grade) == 1)
				{//未被抽查 是应届班级 且班级被抽数不是最多的
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;
					curr_num ++;
					addteacher(a[i].result,a[i].tea_num);//主要更新 教师被抽数量 总抽查数 良和中 被抽数量
					addgrade(a[i].grade); //对应班级人数 +1
					break;
				}
			}
			//使得每个教师被抽走人数尽量相同
			for(i = 0;i < cnt ;i++)
			{
				if(curr_num >= spotcheck_num) break;//达到最大抽查数则跳出
				if(spot.ischecked[i] == 0 && is_lessteacher(a[i].tea_num) == 1)
				{//未被抽查 且 被抽人数不是最多的
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;
					curr_num ++;
					addteacher(a[i].result,a[i].tea_num);//主要更新 教师被抽数量 总抽查数 良和中 被抽数量
					addgrade(a[i].grade); //对应班级人数 +1
					break;
				}
			}
		}
	}
	fclose(fp);//关闭文件
	printf("按任意键返回！\n");
	char id = getch();//获取一个字符
	if(id != EOF) return;
}
//根据班级名字进行排序，使得数据显示更整齐
int cmpgradename(const void *a,const void *b)
{
	return strcmp((*(struct Infonum *)a).gradename,(*(struct Infonum *)b).gradename);
}
//根据教工号排序，使统计结果更整齐
int cmpteanum(const void *a,const void *b)
{
	return strcmp((*(struct Infonum *)a).teanum,(*(struct Infonum *)b).teanum);
}
void Stat()
{
	int i , cnt = 0;//cnt记录班级数 和 教工号数量
	int totalpeo = 0 ,totalexcellent = 0,totalgood = 0,totalmedium = 0,totalpass = 0;//总人数  总的优 总良 总中 总及格人数
	for(i = 0;i < MAX;i++)//初始化
	{
		arr[i].num_peo = 0;
		arr[i].num_excellent = 0;
		arr[i].num_good = 0;
		arr[i].num_medium = 0;
		arr[i].num_pass = 0;
	}
	struct Node *k = list->next ;
	k = k->next;
	while(k != NULL)//遍历链表
	{
		for(i = 0; i < cnt;i++)
		{
			if(strcmp(arr[i].gradename,k->data.grade) == 0)//判断此班级是否已经记录
			{
				break;
			}
		}
		if(i == cnt)//没有记录的班级
		{
			cnt ++;//班级数+1
			strcpy(arr[i].gradename,k->data.grade);//添加新的班级名称
		}
		arr[i].num_peo ++;//总人数+1
		if(strcmp(k->data.result,"优") == 0) arr[i].num_excellent ++;//对应成绩+1
		if(strcmp(k->data.result,"良") == 0) arr[i].num_good ++;
		if(strcmp(k->data.result,"中") == 0) arr[i].num_medium ++;
		if(strcmp(k->data.result,"及格") == 0) arr[i].num_pass ++;
		k = k->next;
	}
	qsort(arr,cnt,sizeof(Infonum),cmpgradename);//班级名称排序
	closegraph();//关闭图形
	system("cls");//控制台清屏
	printf("统计结果如下:\n");
	printf("-----------------------------------------------------------------------\n");
	printf("%-30s\t%-5s\t%-5s\t%-5s\t%-5s\t%-5s\n","班级","人数","优","良","中","及格");
	for(i = 0;i < cnt ;i++)//输出班级统计结果
	{
		totalpeo += arr[i].num_peo;
		totalexcellent += arr[i].num_excellent;
		totalgood += arr[i].num_good;
		totalmedium += arr[i].num_medium;
		totalpass += arr[i].num_pass;
		printf("%-30s\t%-d\t%-d\t%-d\t%-d\t%-d\n",arr[i].gradename,arr[i].num_peo,arr[i].num_excellent,arr[i].num_good,arr[i].num_medium,arr[i].num_pass);
	}
	printf("%-30s\t%-5d\t%-5d\t%-5d\t%-5d\t%-5d\n","合计",totalpeo,totalexcellent,totalgood,totalmedium,totalpass);//合计结果
	printf("-----------------------------------------------------------------------\n");
	for(i = 0;i < MAX;i++)//再次初始化  用于下面教工号的统计
	{
		arr[i].num_peo = 0;
		arr[i].num_excellent = 0;
		arr[i].num_good = 0;
		arr[i].num_medium = 0;
		arr[i].num_pass = 0;
	}
	cnt = 0;//记录教工号个数
	totalpeo = 0 ,totalexcellent = 0,totalgood = 0,totalmedium = 0,totalpass = 0;//初始化
	k = list->next;
	k = k->next;
	while(k != NULL)//遍历链表
	{
		for(i = 0; i < cnt;i++)
		{	//判断此教工号是否已经添加
			if(strcmp(arr[i].teanum,k->data.tea_num) == 0)
			{
				break;
			}
		}
		if(i == cnt)//未被添加的教工号
		{
			cnt ++;//教工号数量+1
			strcpy(arr[i].teanum,k->data.tea_num);//添加此教工号
		}
		arr[i].num_peo ++;//总人数+1
		if(strcmp(k->data.result,"优") == 0) arr[i].num_excellent ++;//对应成绩人数+1
		if(strcmp(k->data.result,"良") == 0) arr[i].num_good ++;
		if(strcmp(k->data.result,"中") == 0) arr[i].num_medium ++;
		if(strcmp(k->data.result,"及格") == 0) arr[i].num_pass ++;
		k = k->next;
	}
	qsort(arr,cnt,sizeof(Infonum),cmpteanum);//教工号排序
	printf("-----------------------------------------------------------------------\n");
	printf("%-15s\t%-20s\t%-5s\t%-5s\t%-5s\t%-5s\n","教工号","指导学生人数","优","良","中","及格");
	for(i = 0;i < cnt ;i++)
	{
		totalpeo += arr[i].num_peo;//合计结果
		totalexcellent += arr[i].num_excellent;
		totalgood += arr[i].num_good;
		totalmedium += arr[i].num_medium;
		totalpass += arr[i].num_pass;
		//输出排序后的统计结果
		printf("%-15s\t%-20d\t%-5d\t%-5d\t%-5d\t%-5d\n",arr[i].teanum,arr[i].num_peo,arr[i].num_excellent,arr[i].num_good,arr[i].num_medium,arr[i].num_pass);
	}
	printf("%-15s\t%-20d\t%-5d\t%-5d\t%-5d\t%-5d\n","合计",totalpeo,totalexcellent,totalgood,totalmedium,totalpass);
	printf("-----------------------------------------------------------------------\n");
	printf("按任意键返回!\n");
	char id = getch();//获取一个字符
	if(id != EOF) return ;
}
int judge(char s[])
{
	if(strlen(s) <= 0)//s长度小于等于0
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "请按正常格式输入！", "系统消息", MB_OK);
		return 0;
	}
	else return 1;
}
struct Node* creatlist()
{
	struct Node *ListHead = (struct Node * )malloc(LEN); //开辟一个新单元
	ListHead->next = NULL; //初始化结构体变量
	return ListHead;//返回表头
}
struct Node* creatNode(struct student data)
{
	struct Node *New = (struct Node * )malloc(LEN);//分配内存空间 返回一个指向它的指针
	New->data = data;
	New->next = NULL;
	return New;
}
void readfile(struct Node* ListHead)
{
	student tempdata; //临时结构体变量
	FILE *fp = fopen("毕业设计信息.txt","r");
	if (fp == NULL)	//如果不存在就创建一个
	{  
		fp = fopen("毕业设计信息.txt","w+");
		fclose(fp);
	}
	else fclose(fp);
	fp = fopen("毕业设计信息.txt","r");
	char str[200],str2[200];
	//格式化方式读写文件
	while(!feof(fp))
	{
		fgets(str,200,fp);//获取一行的所有字符
		int i;
		for(i = 0;i < strlen(str);i++)
		{
			if(str[i] == '\n') str[i] = '\0';//因为fgets会把末尾的换行符也读取，这里将换行符消除
		}
		char s[2] = "\t";//作为隔开字符串的标志
		char *token = strtok(str,s);//利用strtok函数进行读取复制文件信息
		strncpy(tempdata.stu_num, token ,MAX_num);
		token = strtok(NULL,s);
		strncpy(tempdata.grade, token ,MAX_grade);
		token = strtok(NULL,s);
		strncpy(tempdata.major, token ,MAX_major);
		token = strtok(NULL,s);
		strncpy(tempdata.sub, token ,MAX_sub);
		token = strtok(NULL,s);
		strncpy(tempdata.result, token ,MAX_res);
		token = strtok(NULL,s);
		strncpy(tempdata.tea_num, token ,MAX_num);
		token = strtok(NULL,s);
		strncpy(tempdata.post, token ,MAX_post);
		token = strtok(NULL,s);
		strncpy(tempdata.type, token ,MAX_type);
		token = strtok(NULL,s);
		strncpy(tempdata.state, token ,MAX_state);
		addInfo(list,tempdata); //添加一组信息
	}
	fclose(fp); //关闭文件
}
void savefile(struct Node* ListHead)
{
	FILE *fp = fopen("毕业设计信息.txt","w");//写入文件
	struct Node *k = ListHead->next;//头结点为空 指向next
	while(k)//遍历链表
	{
		//易错点  最后一行不能加换行符  不然下一次打开程序将无法读取文件 从而无法执行
		if(k->next == NULL)
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		else fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		k = k->next;
	}
	fclose(fp);//关闭文件
}
//添加信息 表尾插入
void addInfo(struct Node * ListHead,struct student data)
{
	struct Node *k = ListHead;
	while(k->next != NULL)//遍历链表 使k指向表尾从而表尾插入
	{
		k = k->next;
	}
	struct Node * p = creatNode(data);//插入新的信息
	k->next = p;
	p->next = NULL;
}
//根据学号删除
void delete_Num(struct Node* ListHead)
{
	char num[MAX_num];//学号
	InputBox(num, MAX_num+1 , "输入学号：");
	//前一个front和后一个next连接
	struct Node* posFront = ListHead; //指向表头  从头开始遍历
	struct Node* posNode = ListHead->next;
	while(strcmp(num,posNode->data.stu_num) != 0)//找到指定节点
	{
		posFront = posNode;
		posNode = posFront->next;
		if(posNode == NULL)
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "查无此人！", "系统消息", MB_OK);
			return ;
		}
	}
	posFront->next = posNode->next;//完成删除  前与后相连接 想一想那个图
	free(posNode);//释放内存
	HWND wnd = GetHWnd();
	MessageBox(wnd, "成功删除", "系统消息", MB_OK);
}
//根据学号查询某一个人的信息节点
struct Node *searchone(struct Node* ListHead ,char *num)
{
	struct Node *k = ListHead->next;
	if(k == NULL) return NULL; //很重要！！！，没有此项系统会强制终止
	while(strcmp(num,k->data.stu_num) != 0)//遍历  直至找到
	{
		k = k->next;
		if(k == NULL) break;
	}
	return k; //返回节点  返回NULL则查无此人
}
//根据学号修改某人的信息
void ModifyInfo(struct Node* listHead)
{
	student tempdata;//临时接收要修改后信息
	char s[MAX_num];//要修改的学号学号
	InputBox(s, MAX_num , "输入要修改的信息的学号：");
	if(searchone(list,s) == NULL)//查询结果为NULL
	{
		HWND wnd = GetHWnd();
			MessageBox(wnd, "查无此人！", "系统消息", MB_OK);
			return ;
	}
	int flag = 1;
	struct Node *k = searchone(list,s);
	end :
	do
	{	InputBox(tempdata.stu_num, MAX_num , "输入修改后的学号(不修改此项请输入0)：");
	}while(judge(tempdata.stu_num) == 0);//长度不能为空
	if(searchone(list,tempdata.stu_num) != NULL)
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "该学号已存在，请重新输入！", "系统消息", MB_OK);
			goto end;//跳转，需要重新输入学号
		}
	if(strcmp(tempdata.stu_num,"0") != 0 ) strcpy(k->data.stu_num , tempdata.stu_num);
	do
	{	InputBox(tempdata.grade, MAX_grade , "输入修改后的班级(不修改此项请输入0)：");
	}while(judge(tempdata.grade) == 0);//长度不为0
	if(strcmp(tempdata.grade , "0") != 0) strcpy(k->data.grade , tempdata.grade);//如果不为0则修改信息
	do
	{	InputBox(tempdata.major, MAX_major, "输入修改后的专业(不修改此项请输入0)：");
	}while(judge(tempdata.major) == 0);
	if(strcmp(tempdata.major, "0") != 0) strcpy(k->data.major,tempdata.major);
	do
	{	InputBox(tempdata.sub, MAX_sub , "输入修改后的毕业设计题目(不修改此项请输入0)：");
	}while(judge(tempdata.sub) == 0);
	if(strcmp(tempdata.sub, "0") != 0) strcpy(k->data.sub,tempdata.sub);
	do
	{	InputBox(tempdata.result, MAX_res , "输入修改后的毕业设计成绩(不修改此项请输入0)：");
	}while(judge(tempdata.result) == 0);
	if(strcmp(tempdata.result, "0") != 0) strcpy(k->data.result,tempdata.result);
	do
	{	InputBox(tempdata.tea_num, MAX_num , "输入修改后指导教师教工号(不修改此项请输入0)：");
	}while(judge(tempdata.tea_num) == 0);
	if(strcmp(tempdata.tea_num, "0") != 0) strcpy(k->data.tea_num,tempdata.tea_num);
	do
	{	InputBox(tempdata.post, MAX_post , "输入修改后的指导教师职称(不修改此项请输入0)：");
	}while(judge(tempdata.post) == 0);
	if(strcmp(tempdata.post, "0") != 0) strcpy(k->data.post,tempdata.post);
	do
	{	InputBox(tempdata.type, MAX_type , "输入修改后的题目分类(不修改此项请输入0)：");
	}while(judge(tempdata.type) == 0);
	if(strcmp(tempdata.type, "0") != 0) strcpy(k->data.type,tempdata.type);
	do
	{	InputBox(tempdata.state, MAX_state , "是否在实验、实习、工程实践和社会调查等实践中完成：");
	}while(judge(tempdata.state) == 0);
	if(strcmp(tempdata.state, "0") != 0) strcpy(k->data.state,tempdata.state);
	HWND wnd = GetHWnd();
	MessageBox(wnd, "修改成功！", "系统消息", MB_OK);
	return;
}
//打印某个节点
void printone(struct Node * posNode)
{
	closegraph();//关闭图形
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",posNode->data.stu_num,posNode->data.grade,posNode->data.major,posNode->data.sub,
		posNode->data.result,posNode->data.tea_num,posNode->data.post,posNode->data.type,posNode->data.state);
}
//部分查询
void searchpart()
{
	student tempdata;//临时的结构体变量
	int cnt;
	InputBox(tempdata.stu_num, MAX_num , "输入要查询的学号(不是你想查询的因素则直接点击确定)：\n 注：若填入此项则不能填其他项");
	if(strcmp(tempdata.stu_num,"") != 0)//输入的学号不为空
	{
		if(searchone(list,tempdata.stu_num) == NULL)//如果查询这个学号的返回值为NULL
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "查无此人！", "系统消息", MB_OK);
			return ;
		}
		else 
		{
			system("cls");//控制台清屏
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号","指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");
			printone(searchone(list,tempdata.stu_num));//查询并输出这个学号对应的一组信息
			printf("按任意键返回\n");
			char id = getch();//接收一个字符
			if(id != EOF) return ;
		}
	}
	else
	{
		InputBox(tempdata.grade, MAX_num , "输入要查询的班级(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.major, MAX_major , "输入要查询的专业(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.result, MAX_res , "输入要查询的毕业成绩(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.tea_num, MAX_num , "输入要查询的教工号(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.post, MAX_post , "输入要查询的教工职位(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.type, MAX_type , "输入要查询的题目分类(不是你想查询的因素则直接点击确定)：");
		InputBox(tempdata.state, MAX_state , "输入是否在实验、实习、工程实践和社会调查等实践中完成(不是你想查询的因素则直接点击确定)：");
		system("cls");//控制台清屏
		printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号","指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");
		struct Node *k = list ->next;
		cnt = 0;
		while(k != NULL)//遍历链表
		{
			if((strcmp(tempdata.grade , k->data.grade) == 0|| strcmp(tempdata.grade,"") == 0)
				&&(strcmp(tempdata.major , k->data.major) == 0|| strcmp(tempdata.major,"") == 0)
				&&(strcmp(tempdata.result , k->data.result) == 0|| strcmp(tempdata.result,"") == 0)
				&&(strcmp(tempdata.tea_num , k->data.tea_num) == 0|| strcmp(tempdata.tea_num,"") == 0)
				&&(strcmp(tempdata.post , k->data.post) == 0|| strcmp(tempdata.post,"") == 0)
				&&(strcmp(tempdata.type , k->data.type) == 0|| strcmp(tempdata.type,"") == 0)
				&&(strcmp(tempdata.state , k->data.state) == 0|| strcmp(tempdata.state,"") == 0))
			{
				printone(k);//满足条件的就输出
				cnt ++;
			}
			k = k->next;
		}
			if(cnt == 0)
			{
				HWND wnd = GetHWnd();
				//MessageBox (句柄, 显示内容,标题,MB_OK) ;
				MessageBox(wnd,"查无此人！\n","系统消息",MB_OK);
				
			}
			else
			{	printf("按任意键返回\n");
				char id = getch();//接收一个字符
				if(id != EOF) return ;
			}
	}
}
//输出链表
void print(struct Node* listHead)
{
	closegraph();//关闭图形
	system("cls");//控制台清屏
	struct Node* k = listHead->next;//指针变量指向要输出的链表
	//printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号","指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");
	while(k)
	{
		printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		k = k->next;
	}
	printf("按任意键返回菜单！\n");
	char id = getch();//接收一个字符
	if(id != EOF) return; 
}
//根据学号排序
int cmpstu_num(const void *a,const void *b)
{
	return strcmp((*(struct student *)a).stu_num,(*(struct student *)b).stu_num);
}
//根据教工号排序
int cmptea_num(const void *a,const void *b)
{
	return strcmp((*(struct student *)a).tea_num,(*(struct student *)b).tea_num);
}
//根据成绩排序
int cmpres(const void *a,const void *b)
{
	if(strcmp((*(struct student *)a).result,(*(struct student *)b).result) == 0) return 0;
	else if(strcmp((*(struct student *)a).result,"优") == 0) return 1;
	else if(strcmp((*(struct student *)b).result,"优") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"良") == 0)  return 1;
	else if(strcmp((*(struct student *)b).result,"良") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"中") == 0) return 1;
	else if(strcmp((*(struct student *)b).result,"中") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"及格") == 0) return 1;
	else return -1;
}
//对信息进行排序
void sortInfo(char s)
{
	closegraph();//关闭图片
	system("cls");//清屏
	struct Node *k = list;//k指向list表头
	k = (k->next)->next;
	int cnt = 0;//信息的数量
	while(k != NULL)//将链表信息复制入结构体变量
	{
		strcpy(a[cnt].stu_num,k->data.stu_num);
		strcpy(a[cnt].grade,k->data.grade);
		strcpy(a[cnt].major,k->data.major);
		strcpy(a[cnt].sub,k->data.sub);
		strcpy(a[cnt].result,k->data.result);
		strcpy(a[cnt].tea_num,k->data.tea_num);
		strcpy(a[cnt].post,k->data.post);
		strcpy(a[cnt].type,k->data.type);
		strcpy(a[cnt].state,k->data.state);
		cnt++;
		k = k->next;
	}
	if(s == 'a'|| s == 'A')//学号排序
	{
		qsort(a,cnt,sizeof(temp),cmpstu_num);
	}
	if(s == 'b' || s == 'B')//教工号排序
	{
		qsort(a,cnt,sizeof(temp),cmptea_num);
	}
	if(s == 'c' || s == 'C')//成绩排序
	{
		qsort(a,cnt,sizeof(temp),cmpres);
	}
	int i;
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","学号","班级","专业","毕业设计题目","毕业设计成绩","指导教师教工号","指导教师职称","题目分类","是否在实验、实习、工程实践和社会调查等实践中完成");
	if(s >= 'a'&&  s <= 'z' )//如果是小写字母
	{
		for(i = 0;i < cnt ;i++)//升序输出
		{
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
		}
	}
	else
	{
		for(i = cnt-1;i >= 0 ;i--)//降序输出
		{
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
		}
	}
	printf("按任意键返回菜单！\n");
	char id = getch();//获取一个任意键，以返回菜单
	if(id != EOF) return; 
}
int getyear()
{
	int year;
	time_t now;
	struct tm*p;
	time(&now);
	p = gmtime(&now);
	year = 1900+p->tm_year; //当前年份
	return year; //返回整型年份
	/*char s[5];				
	int i = 0,num = 1000;
	while(a != 0)
	{
		s[i] = a/num+48;
		a = a - a/num*num;
		num = num /10;
		i++;
	}*/
}
void agin()
{
	HWND wnd = GetHWnd();
			//MessageBox (句柄, 显示内容,标题,MB_OK) ;
			MessageBox(wnd,"没有该选项，请重新输入\n","系统消息",MB_OK);
			closegraph();//关闭图片
}
void menu_main_search()
{
	while(true)
	{
		cleardevice();	//清屏
		initgraph(1000, 600);  //初始化界面大小
		loadimage(0,"bkg.jpg");//加载图片作背景图
		setbkmode(TRANSPARENT);//设置字体透明度
		//设置文本字体、颜色、坐标
		setcolor(DARKGRAY);
		setfont(40, 0, "黑体");
		outtextxy(300, 10, "毕业设计管理系统");
		setcolor (YELLOW);
	    setfont(25,0,"宋体");
	    outtextxy(300,100,"请选择功能序号:");
		setcolor(BLACK);
	             setfont(35,0,"微软雅黑");
				 outtextxy(380,150,_T("1.查询所有信息"));
	             outtextxy(380,220,_T("2.查询部分信息"));
	             outtextxy(380,290,_T("0.返回"));
		int id = getch();//获取用户输入的功能序号
		if(id=='0')
		{
			closegraph();//关闭图片
			return ;
		}
		else if(id=='1')
			print(list);//输出所有信息，查询全部
		else if(id=='2')
			searchpart();//组合查询
		else 
			agin();//重新输入序号
	}
}
void menu_main_sort()
{
	while(true)
	{
		cleardevice();   //	清屏
		initgraph(1000, 600);  //初始化界面大小
		loadimage(0,"bkg.jpg");//加载图片作背景
		setbkmode(TRANSPARENT);//设置文本透明度
		//设置文本字体、颜色、坐标完成界面布置
		setcolor(DARKGRAY);
		setfont(40, 0, "黑体");
		outtextxy(300, 10, "毕业设计管理系统");
		setcolor (YELLOW);
	    setfont(25,0,"宋体");
	    outtextxy(300,100,"请选择功能序号(小写升序，大写降序):");
		setcolor(BLACK);
	    setfont(35,0,"微软雅黑");
		outtextxy(380,150,_T("a.按学号"));
	    outtextxy(380,220,_T("b.按教工号"));
		outtextxy(380,290,_T("c.按毕业设计成绩"));
	    outtextxy(380,360,_T("0.返回"));
		char id = getch();//获取用户输入功能序号
		if(id == '0')
		{
			closegraph();//关闭图形界面
			return ;
		}
		else if(id == 'a'||id == 'A'||id == 'b'|| id == 'B'||id == 'c'|| id == 'C')
			sortInfo(id);//排序
		else agin();//重新输入
	}
}
//主菜单
void menu_main()
{	
	while(true)
	{	
		cleardevice(); //清屏
		initgraph(1000, 600);     //初始化界面大小
		loadimage(0,"bkg.jpg"); //加载图片作背景图
		setbkmode(TRANSPARENT);//设置字体透明度
		//依次设置文本颜色、字体、坐标，完成界面布置
		setcolor(DARKGRAY);
		setfont(40, 0, "黑体");
		outtextxy(300, 10, "毕业设计管理系统");
		setcolor (YELLOW);
	    setfont(25,0,"宋体");
	    outtextxy(300,100,"请选择功能序号:");
		setcolor(BLACK);
	             setfont(35,0,"微软雅黑");
	             outtextxy(200,130,_T("1.毕业设计信息查询"));
	             outtextxy(200,200,_T("2.毕业设计信息排序"));
				 outtextxy(200,270,_T("3.毕业设计信息统计"));
				 outtextxy(200,340,_T("4.删除信息"));
				 outtextxy(500,130,_T("5.修改信息"));
				 outtextxy(500,200,_T("6.添加信息"));
				 outtextxy(500,270,_T("7.抽查信息"));
	             outtextxy(500,340,_T("0.返回"));
		end:
		int id = getch();//接收用户选择功能序号
		if(id == '0')
		{
			closegraph();//关闭图片
			return menu_user();//返回用户登录界面
		}
		else if(id == '1')
		{
			menu_main_search();//查询界面
		}
		else if(id == '2')
		{
			menu_main_sort();//排序界面
		}
		else if(id == '3')
		{			
			Stat();//统计信息
		}
		else if(id == '4')
		{
			 delete_Num(list);//删除信息
		}
		else if(id == '5')
		{
			ModifyInfo(list);//修改信息
		}
		else if(id == '6')
		{
			student tempdata;//临时存储一组毕业设计信息
			do
			{	InputBox(tempdata.stu_num, MAX_grade , "输入学号：");
			}while(judge(tempdata.stu_num) == 0);//判断格式
			if (searchone(list,tempdata.stu_num) != NULL)//判断学号是否已存在
			{
				HWND wnd = GetHWnd();
				MessageBox(wnd, "该学号已存在,请重新输入！", "系统消息", MB_OK);
				goto end;
			}
			do
			{	InputBox(tempdata.grade, MAX_grade , "输入班级：");
			}while(judge(tempdata.grade) == 0);
			do
			{	InputBox(tempdata.major, MAX_major, "输入专业：");
			}while(judge(tempdata.major) == 0);
			do
			{	InputBox(tempdata.sub, MAX_sub , "输入毕业设计题目：");
			}while(judge(tempdata.sub) == 0);
			do
			{	InputBox(tempdata.result, MAX_res , "输入毕业设计成绩：");
			}while(judge(tempdata.result) == 0);
			do
			{	InputBox(tempdata.tea_num, MAX_num , "输入指导教师教工号：");
			}while(judge(tempdata.tea_num) == 0);
			do
			{	InputBox(tempdata.post, MAX_post , "输入指导教师职称：");
			}while(judge(tempdata.post) == 0);
			do
			{	InputBox(tempdata.type, MAX_type , "输入题目分类：");
			}while(judge(tempdata.type) == 0);
			do
			{	InputBox(tempdata.state, MAX_state , "是否在实验、实习、工程实践和社会调查等实践中完成：");
			}while(judge(tempdata.state) == 0);
			addInfo(list,tempdata); //添加信息
			HWND wnd = GetHWnd();
			MessageBox(wnd, "添加成功", "系统消息", MB_OK);
		}
		else if(id == '7')
		{
			spotcheck();//抽查信息
		}
		else 
		{
			agin();//按要求重新输入序号
		}
	}
}
void menu_user()
{
				 initgraph(1000, 600);      //初始化
				 loadimage(0,"bkg.jpg");	//加载背景图
				 setbkmode(TRANSPARENT);	//字体背景透明度  去掉底色
				 setlinecolor(BLACK);		//设置线条颜色为黑
				 setcolor(DARKGRAY);		//设置字体颜色为亮灰色
		         setfont(40, 0, "黑体");	//设置字体为黑体
		         outtextxy(300, 10, "毕业设计管理系统");//放置文字
		         setcolor (YELLOW);			//设置字体颜色为黄
	             setfont(25,0,"宋体");		//设置字体为宋体
	             outtextxy(300,100,"请选择功能序号:");//放置文字
	             setcolor(BLACK);	//设置字体颜色为黑
	             setfont(35,0,"微软雅黑");//字体为微软雅黑
	             outtextxy(380,150,_T("1.用户登录"));//放置文字
	             outtextxy(380,220,_T("2.注册"));
	             outtextxy(380,290,_T("0.退出"));
}
int main()
{
	list = creatlist();//创建链表
	readfile(list); //开始的时候读文件   信息改动时写入文件
	char id;//存放功能序号
	do
	{
		menu_user();//用户登录系统
		id = getch();//直接获取一个字符
		if(id == '1')
		{
			logon();//用户登录函数
		}
		else if (id == '2')
		{
			Register();//注册函数
		}
		else if(id == '0')
		{
			system("cls");//清屏
			savefile(list);//写入文件，保存信息
			HWND wnd = GetHWnd();//该函数用于获取图形窗口的句柄。
			//MessageBox (句柄, 显示内容,标题,MB_OK) ;
					MessageBox(wnd,"成功退出系统\n","系统消息",MB_OK);
					closegraph();
					return 0;
		}
		else
		{
			agin();//重新输入序号
		}
	}while(id);
	return 0;
}