
#include"header.h"
struct Node *list;
struct Infonum
{
	char teanum[MAX_num];//�̹���
	char gradename[MAX];//�༶
	int num_peo;//����
	int num_excellent;//������
	int num_good;//������
	int num_medium;//������
	int num_pass;//��������
}arr[MAX];
struct temp
{
	char stu_num[MAX_num] ;//ѧ��
	char grade[MAX_grade];  //�༶
	char major[MAX_major];//רҵ
	char sub[MAX_sub];//��Ŀ
	char result[MAX_res];//�ɼ�
	char tea_num[MAX_num];//�̹���
	char post[MAX_post]; //��ʦְ��
	char type[MAX_type];//����
	char state[MAX_state];// ��/�� 
}a[MAX];
struct teacher //�����Ϣ�н�ʦ����
{
	char te_num[MAX_num];//�̹���
	int ecxellent;	//�ý̹��ű������ŵ�����
	int pass;	//�ý̹��ű����ļ��������
	int isnew;	//�Ƿ�������½���ʦ
	int check_tnum;//ÿ����ʦ������������
};
struct Grades
{
	char gradename[MAX_grade];//�༶����
	int num_checkclass;//ÿ���౻������� 
};
struct Spotcheck
{
	int ischecked[MAX];//ѧ���Ƿ񱻳���
	int total_tnum;//��ʦ������
	int total_cnum;//�༶������
	struct teacher t_arr[MAX];
	struct Grades class_arr[MAX];
	int good; //�ѳ�� �� ������
	int medium; //�ѳ�� �� ������
}spot;
// �ж��ǲ����½���ʦ  ��  �ж��Ƿ��Ѿ�����һ��
int judgenew(char t_num[])
{
	int i;
	for(i = 0 ;i < spot.total_tnum ;i++)
	{//������Ϣ�ҵ���Ӧ�̹���
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0)
		{
			if(spot.t_arr[i].isnew == 1)//������½���ʦ
			{
				if(spot.t_arr[i].check_tnum == 0) return 1;//������������Ϊ0 ����1
				else return 0;
			}
			else return 0;
		}
	}
}
//��ʼ���������
void inispotcheck()
{
	int i,nowyear,pastyear,j,J;
	char Now[4],Past[4];//�ж��½���ʦ���������
	struct Node *k = list ->next;
	time_t now;
	time(&now);
	struct tm*p;
	p = gmtime(&now);
	nowyear = 1900+p->tm_year;//��ǰ���
	pastyear = nowyear - 3;
	nowyear = nowyear + 1;//�����жϵ�ǰ��ݵļӹ�����
	j = 3;
	while(nowyear != 0)//�����ַ�����
	{
			Now[j] = nowyear%10 + 48;
			Past[j] = pastyear%10 + 48;
			nowyear /= 10;
			pastyear /= 10;
			j--;
	}
	//��ʼ���ܳ������
	spot.good = 0;
	for(i = 0; i < MAX ;i++)
	{
		spot.ischecked[i] = 0;//ȫ��Ϊ0��ʾδ�����
	}
	spot.medium = 0;//�� ��������
	spot.total_cnum = 0;//�༶����
	spot.total_tnum = 0;//��ʦ����
	//��ʼ����ʦ����
	while(k != NULL)
	{//������Ϣ ��¼ÿһ��2��ʦ
		for(i = 0; i < spot.total_tnum ;i++)
		{
			if(strcmp(spot.t_arr[i].te_num,k->data.tea_num) == 0)
				break;
		}
		if(i == spot.total_tnum)
		{
			strcpy(spot.t_arr[i].te_num,k->data.tea_num);
			spot.t_arr[i].ecxellent = 0;//��ʦ����������
			spot.t_arr[i].pass = 0;//��ʦ���鼰������
			spot.total_tnum ++;//��ʦ����+1
			spot.t_arr[i].check_tnum = 0;
			if(strcmp(spot.t_arr[i].te_num,Now) == -1 && strcmp(spot.t_arr[i].te_num,Past) == 1 )
			{
				spot.t_arr[i].isnew = 1;//1��ʾ���½���ʦ
			}
			else spot.t_arr[i].isnew = 0;//0��ʾ�����½���ʦ
		}
		k = k->next;
	}
	//��ʼ���༶����
	spot.total_cnum = 0;
	k= list ->next;
	while(k != NULL)
	{//������Ϣ ��¼���а༶����
		for(i = 0;i < spot.total_cnum ;i++)
		{
			if(strcmp(spot.class_arr[i].gradename,k->data.grade) == 0)
				break;
		}
		if(i == spot.total_cnum)
		{
			strcpy(spot.class_arr[i].gradename,k->data.grade);
			spot.total_cnum ++;//�༶����+1
			spot.class_arr[i].num_checkclass = 0;//�༶��������Ϊ0
		}
		k = k->next;
	}
}
int teaexcellent(char t_num[])
{
	int i ;
	for(i = 0;i < spot.total_tnum  ;i++)
	{//������Ϣ�ҵ���Ӧ�̹��� �жϸý�ʦ������������Ƿ�Ϊ0
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0 && spot.t_arr[i].ecxellent == 0)
		{
			spot.t_arr[i].ecxellent ++;
			return 0;
		}
	}
	return 1;
}
//�жϽ�ʦ�Ƿ��Ѿ����� ����
int teapass(char t_num[])
{
	int i ;
	for(i = 0;i < spot.total_tnum  ;i++)
	{//������Ϣ�ҵ���Ӧ�̹��� �жϸý�ʦ����鼰�������Ƿ�Ϊ0
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0 && spot.t_arr[i].pass == 0)
		{
			spot.t_arr[i].pass ++;
			return 0;
		}
	}
	return 1;
}
//��Ӧ��ʦ���ݸ���
void addteacher(char result[],char t_num[])
{
	int i;
	for(i = 0;i < spot.total_tnum ;i++)
	{//�ҵ���Ӧ��ʦ
		if(strcmp(spot.t_arr[i].te_num,t_num) == 0)
		{
			spot.t_arr[i].check_tnum ++;//�ý�ʦ���������+1
			if(strcmp(result,"��") == 0) spot.t_arr[i].ecxellent ++;//�ý�ʦ����������+1
			if(strcmp(result,"����") == 0) spot.t_arr[i].pass ++;//�ý�ʦ���鼰������+1
			if(strcmp(result,"��") == 0) spot.medium++;//�� ���屻������+1
			if(strcmp(result,"��") == 0)	spot.good++;//�� ���屻������+1
			break;
		}
	}
}
//��Ӧ�༶����+1
void addgrade(char gradename[])
{
	int i;
	for(i = 0;i < spot.total_cnum ;i++)
	{//������Ϣ�ҵ���Ӧ�༶
		if(strcmp(gradename,spot.class_arr[i].gradename) == 0)
		{
			spot.class_arr[i].num_checkclass ++;//�ð༶��������+1
			break;
		}
	}
}
//�ж��Ƿ���Ӧ��༶ �Ƿ���1 �񷵻�0
int is_thisyear(char classname[])
{
	int year1;
	time_t now;
	time(&now);
	struct tm*p;
	p = gmtime(&now);
	//�༶������ʽǰ�����ַ��ж�
	year1 = 1900+p->tm_year - 2000 - 4;
	char Year1[2];
	if(p->tm_mon < 7)//�����·� �ж�Ӧ��༶�����
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
	//����16    16�ƿ� ǰ�����ַ���ͬ
	if(classname[0] == Year1[0] && classname[1] == Year1[1]) return 1;
	else return 0;
}
//�жϸ�Ӧ��༶�����������Ƿ�С���������  �Ƿ���1 �񷵻�0
int is_lessclass(char classname[])
{
	int i,max_num = 0;//����������
	for(i = 0;i < spot.total_cnum ;i++)
	{//������Ϣ�ҵ�Ӧ��༶�������
		if(is_thisyear(spot.class_arr[i].gradename) == 1)
		{//�ж��Ƿ���Ӧ��༶
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
		{//�ж��Ƿ�С��max_num
			if(spot.class_arr[i].num_checkclass < max_num) return 1;//��
			else return 0;//��
		}
	}
}
//�жϽ�ʦ���������Ƿ�С���������  �Ƿ���1 �񷵻�0
int is_lessteacher(char t_num[])
{
	int i,max_num = 0;//����������
	for(i = 0;i < spot.total_tnum ;i++)//������Ϣ
	{
		if(max_num < spot.t_arr[i].check_tnum)
			{
				max_num = spot.t_arr[i].check_tnum;
			}
	}
	for(i = 0;i < spot.total_cnum ;i++)
	{
		if(strcmp(t_num,spot.t_arr[i].te_num) == 0)//�ҵ���Ӧ�̹����ж��Ƿ�С�ڳ�������
		{
			if(spot.t_arr[i].check_tnum < max_num) return 1;//��
			else return 0;//��
		}
	}
}
void spotcheck()
{
	FILE * fp;
	fp = fopen("�����Ϣ.txt","w");//�򿪴��ļ�
	fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���",
		"ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");//д�����
	closegraph();//�ر�ͼ��
	system("cls");//����̨����
	printf("��������£�    \n");
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���",
		"ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");
	struct Node *k = list;
	k = (k->next)->next; //��ͷΪ�� next�Ǳ���  ����һ����Ԫ������
	int i,swapa,swapb;
	int cnt = 0; //��0��cnt-1
	while(k != NULL)//�������� ������Ϣ���ṹ�������
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
		cnt++;//��Ϣ����
		k = k->next;
	}
	inispotcheck();//��ʼ���������
	struct temp c;//��ʱ���� ���ڽ���������Ϣ
	for(i = 0;i < MAX ;i++)
	{
		swapa = rand()%cnt;//����������������ڶ��߽���
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
	int spotcheck_num = (int) cn;//��������� ȫ����20%  ��������
	int curr_num = 0; //��¼��ǰ��ȡ������
	//��ȡ��ʦָ������  ��  ��
	for(i = 0;i < cnt ;i++)
	{
		if(curr_num >= spotcheck_num) break;//�ﵽ�����������
		if(spot.ischecked[i] == 0 && strcmp(a[i].result,"��") == 0 && teaexcellent(a[i].tea_num) == 0)
		{//����������δ����� �ɼ�Ϊ�� ��Ӧ�̹���δ����ȡ�� �����������ͱ����
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//�����Ϊ1
			curr_num ++;//��ǰ�����+1
			addteacher(a[i].result,a[i].tea_num);//��Ӧ��ʦ�����+1 �� +1
			addgrade(a[i].grade); //��Ӧ�༶���� +1
		}
	}
	//��ȡ��ʦָ������ ���� ��
	for(i = 0;i < cnt ;i++)
	{
		if(curr_num >= spotcheck_num) break;//�ﵽ�����������
		if(spot.ischecked[i] == 0 && strcmp(a[i].result,"����") == 0 && teapass(a[i].tea_num) == 0)
		{//����������δ����� �ɼ�Ϊ���� ��Ӧ�̹���δ����ȡ���� �����������ͱ����
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//�����Ϊ1
			curr_num ++;//��ǰ����+1
			addteacher(a[i].result,a[i].tea_num);//��Ӧ��ʦ�����+1 ���� +1
			addgrade(a[i].grade); //��Ӧ�༶���� +1
		}
	}
	//��ȡ�����½���ʦ
	for(i = 0 ;i < cnt ;i ++)
	{
		if(curr_num >= spotcheck_num) break;//�ﵽ�����������
		if(spot.ischecked[i] == 0 && judgenew(a[i].tea_num) == 1)
		{//���� δ����� �ǽ������ʦ��δ����ȡ �����������ͱ�����
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,
				a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,
				a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
			spot.ischecked[i] = 1;//����ȡΪ1
			curr_num ++;//�����ȡ����+1
			addteacher(a[i].result,a[i].tea_num);//���½�ʦ�б��� �� �� ���� �Լ��ܳ���� �� �� ��
			addgrade(a[i].grade); //��Ӧ�༶���� +1
		}
	}
	//������������� �������鹻
	while(curr_num < spotcheck_num)
	{
		//��֤�� �� �� �����������
		if(spot.good < spot.medium) //����
		{
			for(i = 0 ;i < cnt ;i ++)
			{
				if(spot.good == spot.medium) break;//������������ͬ������
				if(curr_num >= spotcheck_num) break;//�ﵽ�������������
				if(spot.ischecked[i] == 0 && strcmp(a[i].result,"��") == 0)
				{//δ������ҳɼ�Ϊ��
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//�����Ϊ1
					curr_num ++;//��ǰ�������+1
					addteacher(a[i].result,a[i].tea_num);//��Ҫ���½�ʦ��������
					addgrade(a[i].grade); //��Ӧ�༶���� +1
				}
			}
		}
		else if(spot.good > spot.medium) //����
		{
			for(i = 0 ;i < cnt ;i ++)
			{
				if(spot.good == spot.medium) break;//������������ͬ������
				if(curr_num >= spotcheck_num) break;//�ﵽ�������������
				if(spot.ischecked[i] == 0 && strcmp(a[i].result,"��") == 0)
				{//δ������ҳɼ�Ϊ��
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//�����Ϊ1
					curr_num ++;//��ǰ�������+1
					addteacher(a[i].result,a[i].tea_num);//��Ҫ���½�ʦ��������
					addgrade(a[i].grade); //��Ӧ�༶���� +1
				}
			}
		}
		else if(spot.good == spot.medium && spot.good == 0)//���������ͬ��δ����ȡ �������ȡһ�� �л�����
		{
			for(i = 0 ;i < cnt ;i++)
			{
				if(curr_num >= spotcheck_num) break;//�ﵽ�������������
				if(spot.ischecked[i] == 0 &&((strcmp(a[i].result,"��") == 0)||(strcmp(a[i].result,"��") ==0)))
				{//Ϊ����� �ҳɼ�Ϊ�л�����
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;//�����Ϊ1
					curr_num ++;//��ǰ�������+1
					addteacher(a[i].result,a[i].tea_num);//��Ҫ���� ��ʦ�������� �ܳ���� ������ ��������
					addgrade(a[i].grade); //��Ӧ�༶���� +1
					break;//��ȡһ����������
				}
			}
		}
		else if(spot.good == spot.medium && spot.good != 0)//������������ͬ��������Ϊ0  ��֤Ӧ��༶��������ͬ �Լ� ��֤��ʦ��������ͬ
		{
			//ʹ�ø��༶��ȡ����������ͬ �������һ��Ӧ��༶��������С������Ӧ��༶�б�������ֵ ����� ÿ�γ�ȡһ����ʵ�ֹ�����Ⱥ�˳��
			for(i = 0;i < cnt ;i++)
			{
				
				if(curr_num >= spotcheck_num) break;//�ﵽ�������������
				if(spot.ischecked[i] == 0 && is_thisyear(a[i].grade) == 1 && is_lessclass(a[i].grade) == 1)
				{//δ����� ��Ӧ��༶ �Ұ༶��������������
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;
					curr_num ++;
					addteacher(a[i].result,a[i].tea_num);//��Ҫ���� ��ʦ�������� �ܳ���� ������ ��������
					addgrade(a[i].grade); //��Ӧ�༶���� +1
					break;
				}
			}
			//ʹ��ÿ����ʦ����������������ͬ
			for(i = 0;i < cnt ;i++)
			{
				if(curr_num >= spotcheck_num) break;//�ﵽ�������������
				if(spot.ischecked[i] == 0 && is_lessteacher(a[i].tea_num) == 1)
				{//δ����� �� ����������������
					printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
					spot.ischecked[i] = 1;
					curr_num ++;
					addteacher(a[i].result,a[i].tea_num);//��Ҫ���� ��ʦ�������� �ܳ���� ������ ��������
					addgrade(a[i].grade); //��Ӧ�༶���� +1
					break;
				}
			}
		}
	}
	fclose(fp);//�ر��ļ�
	printf("����������أ�\n");
	char id = getch();//��ȡһ���ַ�
	if(id != EOF) return;
}
//���ݰ༶���ֽ�������ʹ��������ʾ������
int cmpgradename(const void *a,const void *b)
{
	return strcmp((*(struct Infonum *)a).gradename,(*(struct Infonum *)b).gradename);
}
//���ݽ̹�������ʹͳ�ƽ��������
int cmpteanum(const void *a,const void *b)
{
	return strcmp((*(struct Infonum *)a).teanum,(*(struct Infonum *)b).teanum);
}
void Stat()
{
	int i , cnt = 0;//cnt��¼�༶�� �� �̹�������
	int totalpeo = 0 ,totalexcellent = 0,totalgood = 0,totalmedium = 0,totalpass = 0;//������  �ܵ��� ���� ���� �ܼ�������
	for(i = 0;i < MAX;i++)//��ʼ��
	{
		arr[i].num_peo = 0;
		arr[i].num_excellent = 0;
		arr[i].num_good = 0;
		arr[i].num_medium = 0;
		arr[i].num_pass = 0;
	}
	struct Node *k = list->next ;
	k = k->next;
	while(k != NULL)//��������
	{
		for(i = 0; i < cnt;i++)
		{
			if(strcmp(arr[i].gradename,k->data.grade) == 0)//�жϴ˰༶�Ƿ��Ѿ���¼
			{
				break;
			}
		}
		if(i == cnt)//û�м�¼�İ༶
		{
			cnt ++;//�༶��+1
			strcpy(arr[i].gradename,k->data.grade);//����µİ༶����
		}
		arr[i].num_peo ++;//������+1
		if(strcmp(k->data.result,"��") == 0) arr[i].num_excellent ++;//��Ӧ�ɼ�+1
		if(strcmp(k->data.result,"��") == 0) arr[i].num_good ++;
		if(strcmp(k->data.result,"��") == 0) arr[i].num_medium ++;
		if(strcmp(k->data.result,"����") == 0) arr[i].num_pass ++;
		k = k->next;
	}
	qsort(arr,cnt,sizeof(Infonum),cmpgradename);//�༶��������
	closegraph();//�ر�ͼ��
	system("cls");//����̨����
	printf("ͳ�ƽ������:\n");
	printf("-----------------------------------------------------------------------\n");
	printf("%-30s\t%-5s\t%-5s\t%-5s\t%-5s\t%-5s\n","�༶","����","��","��","��","����");
	for(i = 0;i < cnt ;i++)//����༶ͳ�ƽ��
	{
		totalpeo += arr[i].num_peo;
		totalexcellent += arr[i].num_excellent;
		totalgood += arr[i].num_good;
		totalmedium += arr[i].num_medium;
		totalpass += arr[i].num_pass;
		printf("%-30s\t%-d\t%-d\t%-d\t%-d\t%-d\n",arr[i].gradename,arr[i].num_peo,arr[i].num_excellent,arr[i].num_good,arr[i].num_medium,arr[i].num_pass);
	}
	printf("%-30s\t%-5d\t%-5d\t%-5d\t%-5d\t%-5d\n","�ϼ�",totalpeo,totalexcellent,totalgood,totalmedium,totalpass);//�ϼƽ��
	printf("-----------------------------------------------------------------------\n");
	for(i = 0;i < MAX;i++)//�ٴγ�ʼ��  ��������̹��ŵ�ͳ��
	{
		arr[i].num_peo = 0;
		arr[i].num_excellent = 0;
		arr[i].num_good = 0;
		arr[i].num_medium = 0;
		arr[i].num_pass = 0;
	}
	cnt = 0;//��¼�̹��Ÿ���
	totalpeo = 0 ,totalexcellent = 0,totalgood = 0,totalmedium = 0,totalpass = 0;//��ʼ��
	k = list->next;
	k = k->next;
	while(k != NULL)//��������
	{
		for(i = 0; i < cnt;i++)
		{	//�жϴ˽̹����Ƿ��Ѿ����
			if(strcmp(arr[i].teanum,k->data.tea_num) == 0)
			{
				break;
			}
		}
		if(i == cnt)//δ����ӵĽ̹���
		{
			cnt ++;//�̹�������+1
			strcpy(arr[i].teanum,k->data.tea_num);//��Ӵ˽̹���
		}
		arr[i].num_peo ++;//������+1
		if(strcmp(k->data.result,"��") == 0) arr[i].num_excellent ++;//��Ӧ�ɼ�����+1
		if(strcmp(k->data.result,"��") == 0) arr[i].num_good ++;
		if(strcmp(k->data.result,"��") == 0) arr[i].num_medium ++;
		if(strcmp(k->data.result,"����") == 0) arr[i].num_pass ++;
		k = k->next;
	}
	qsort(arr,cnt,sizeof(Infonum),cmpteanum);//�̹�������
	printf("-----------------------------------------------------------------------\n");
	printf("%-15s\t%-20s\t%-5s\t%-5s\t%-5s\t%-5s\n","�̹���","ָ��ѧ������","��","��","��","����");
	for(i = 0;i < cnt ;i++)
	{
		totalpeo += arr[i].num_peo;//�ϼƽ��
		totalexcellent += arr[i].num_excellent;
		totalgood += arr[i].num_good;
		totalmedium += arr[i].num_medium;
		totalpass += arr[i].num_pass;
		//���������ͳ�ƽ��
		printf("%-15s\t%-20d\t%-5d\t%-5d\t%-5d\t%-5d\n",arr[i].teanum,arr[i].num_peo,arr[i].num_excellent,arr[i].num_good,arr[i].num_medium,arr[i].num_pass);
	}
	printf("%-15s\t%-20d\t%-5d\t%-5d\t%-5d\t%-5d\n","�ϼ�",totalpeo,totalexcellent,totalgood,totalmedium,totalpass);
	printf("-----------------------------------------------------------------------\n");
	printf("�����������!\n");
	char id = getch();//��ȡһ���ַ�
	if(id != EOF) return ;
}
int judge(char s[])
{
	if(strlen(s) <= 0)//s����С�ڵ���0
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, "�밴������ʽ���룡", "ϵͳ��Ϣ", MB_OK);
		return 0;
	}
	else return 1;
}
struct Node* creatlist()
{
	struct Node *ListHead = (struct Node * )malloc(LEN); //����һ���µ�Ԫ
	ListHead->next = NULL; //��ʼ���ṹ�����
	return ListHead;//���ر�ͷ
}
struct Node* creatNode(struct student data)
{
	struct Node *New = (struct Node * )malloc(LEN);//�����ڴ�ռ� ����һ��ָ������ָ��
	New->data = data;
	New->next = NULL;
	return New;
}
void readfile(struct Node* ListHead)
{
	student tempdata; //��ʱ�ṹ�����
	FILE *fp = fopen("��ҵ�����Ϣ.txt","r");
	if (fp == NULL)	//��������ھʹ���һ��
	{  
		fp = fopen("��ҵ�����Ϣ.txt","w+");
		fclose(fp);
	}
	else fclose(fp);
	fp = fopen("��ҵ�����Ϣ.txt","r");
	char str[200],str2[200];
	//��ʽ����ʽ��д�ļ�
	while(!feof(fp))
	{
		fgets(str,200,fp);//��ȡһ�е������ַ�
		int i;
		for(i = 0;i < strlen(str);i++)
		{
			if(str[i] == '\n') str[i] = '\0';//��Ϊfgets���ĩβ�Ļ��з�Ҳ��ȡ�����ｫ���з�����
		}
		char s[2] = "\t";//��Ϊ�����ַ����ı�־
		char *token = strtok(str,s);//����strtok�������ж�ȡ�����ļ���Ϣ
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
		addInfo(list,tempdata); //���һ����Ϣ
	}
	fclose(fp); //�ر��ļ�
}
void savefile(struct Node* ListHead)
{
	FILE *fp = fopen("��ҵ�����Ϣ.txt","w");//д���ļ�
	struct Node *k = ListHead->next;//ͷ���Ϊ�� ָ��next
	while(k)//��������
	{
		//�״��  ���һ�в��ܼӻ��з�  ��Ȼ��һ�δ򿪳����޷���ȡ�ļ� �Ӷ��޷�ִ��
		if(k->next == NULL)
		fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		else fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		k = k->next;
	}
	fclose(fp);//�ر��ļ�
}
//�����Ϣ ��β����
void addInfo(struct Node * ListHead,struct student data)
{
	struct Node *k = ListHead;
	while(k->next != NULL)//�������� ʹkָ���β�Ӷ���β����
	{
		k = k->next;
	}
	struct Node * p = creatNode(data);//�����µ���Ϣ
	k->next = p;
	p->next = NULL;
}
//����ѧ��ɾ��
void delete_Num(struct Node* ListHead)
{
	char num[MAX_num];//ѧ��
	InputBox(num, MAX_num+1 , "����ѧ�ţ�");
	//ǰһ��front�ͺ�һ��next����
	struct Node* posFront = ListHead; //ָ���ͷ  ��ͷ��ʼ����
	struct Node* posNode = ListHead->next;
	while(strcmp(num,posNode->data.stu_num) != 0)//�ҵ�ָ���ڵ�
	{
		posFront = posNode;
		posNode = posFront->next;
		if(posNode == NULL)
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "���޴��ˣ�", "ϵͳ��Ϣ", MB_OK);
			return ;
		}
	}
	posFront->next = posNode->next;//���ɾ��  ǰ��������� ��һ���Ǹ�ͼ
	free(posNode);//�ͷ��ڴ�
	HWND wnd = GetHWnd();
	MessageBox(wnd, "�ɹ�ɾ��", "ϵͳ��Ϣ", MB_OK);
}
//����ѧ�Ų�ѯĳһ���˵���Ϣ�ڵ�
struct Node *searchone(struct Node* ListHead ,char *num)
{
	struct Node *k = ListHead->next;
	if(k == NULL) return NULL; //����Ҫ��������û�д���ϵͳ��ǿ����ֹ
	while(strcmp(num,k->data.stu_num) != 0)//����  ֱ���ҵ�
	{
		k = k->next;
		if(k == NULL) break;
	}
	return k; //���ؽڵ�  ����NULL����޴���
}
//����ѧ���޸�ĳ�˵���Ϣ
void ModifyInfo(struct Node* listHead)
{
	student tempdata;//��ʱ����Ҫ�޸ĺ���Ϣ
	char s[MAX_num];//Ҫ�޸ĵ�ѧ��ѧ��
	InputBox(s, MAX_num , "����Ҫ�޸ĵ���Ϣ��ѧ�ţ�");
	if(searchone(list,s) == NULL)//��ѯ���ΪNULL
	{
		HWND wnd = GetHWnd();
			MessageBox(wnd, "���޴��ˣ�", "ϵͳ��Ϣ", MB_OK);
			return ;
	}
	int flag = 1;
	struct Node *k = searchone(list,s);
	end :
	do
	{	InputBox(tempdata.stu_num, MAX_num , "�����޸ĺ��ѧ��(���޸Ĵ���������0)��");
	}while(judge(tempdata.stu_num) == 0);//���Ȳ���Ϊ��
	if(searchone(list,tempdata.stu_num) != NULL)
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "��ѧ���Ѵ��ڣ����������룡", "ϵͳ��Ϣ", MB_OK);
			goto end;//��ת����Ҫ��������ѧ��
		}
	if(strcmp(tempdata.stu_num,"0") != 0 ) strcpy(k->data.stu_num , tempdata.stu_num);
	do
	{	InputBox(tempdata.grade, MAX_grade , "�����޸ĺ�İ༶(���޸Ĵ���������0)��");
	}while(judge(tempdata.grade) == 0);//���Ȳ�Ϊ0
	if(strcmp(tempdata.grade , "0") != 0) strcpy(k->data.grade , tempdata.grade);//�����Ϊ0���޸���Ϣ
	do
	{	InputBox(tempdata.major, MAX_major, "�����޸ĺ��רҵ(���޸Ĵ���������0)��");
	}while(judge(tempdata.major) == 0);
	if(strcmp(tempdata.major, "0") != 0) strcpy(k->data.major,tempdata.major);
	do
	{	InputBox(tempdata.sub, MAX_sub , "�����޸ĺ�ı�ҵ�����Ŀ(���޸Ĵ���������0)��");
	}while(judge(tempdata.sub) == 0);
	if(strcmp(tempdata.sub, "0") != 0) strcpy(k->data.sub,tempdata.sub);
	do
	{	InputBox(tempdata.result, MAX_res , "�����޸ĺ�ı�ҵ��Ƴɼ�(���޸Ĵ���������0)��");
	}while(judge(tempdata.result) == 0);
	if(strcmp(tempdata.result, "0") != 0) strcpy(k->data.result,tempdata.result);
	do
	{	InputBox(tempdata.tea_num, MAX_num , "�����޸ĺ�ָ����ʦ�̹���(���޸Ĵ���������0)��");
	}while(judge(tempdata.tea_num) == 0);
	if(strcmp(tempdata.tea_num, "0") != 0) strcpy(k->data.tea_num,tempdata.tea_num);
	do
	{	InputBox(tempdata.post, MAX_post , "�����޸ĺ��ָ����ʦְ��(���޸Ĵ���������0)��");
	}while(judge(tempdata.post) == 0);
	if(strcmp(tempdata.post, "0") != 0) strcpy(k->data.post,tempdata.post);
	do
	{	InputBox(tempdata.type, MAX_type , "�����޸ĺ����Ŀ����(���޸Ĵ���������0)��");
	}while(judge(tempdata.type) == 0);
	if(strcmp(tempdata.type, "0") != 0) strcpy(k->data.type,tempdata.type);
	do
	{	InputBox(tempdata.state, MAX_state , "�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ������ɣ�");
	}while(judge(tempdata.state) == 0);
	if(strcmp(tempdata.state, "0") != 0) strcpy(k->data.state,tempdata.state);
	HWND wnd = GetHWnd();
	MessageBox(wnd, "�޸ĳɹ���", "ϵͳ��Ϣ", MB_OK);
	return;
}
//��ӡĳ���ڵ�
void printone(struct Node * posNode)
{
	closegraph();//�ر�ͼ��
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",posNode->data.stu_num,posNode->data.grade,posNode->data.major,posNode->data.sub,
		posNode->data.result,posNode->data.tea_num,posNode->data.post,posNode->data.type,posNode->data.state);
}
//���ֲ�ѯ
void searchpart()
{
	student tempdata;//��ʱ�Ľṹ�����
	int cnt;
	InputBox(tempdata.stu_num, MAX_num , "����Ҫ��ѯ��ѧ��(���������ѯ��������ֱ�ӵ��ȷ��)��\n ע�����������������������");
	if(strcmp(tempdata.stu_num,"") != 0)//�����ѧ�Ų�Ϊ��
	{
		if(searchone(list,tempdata.stu_num) == NULL)//�����ѯ���ѧ�ŵķ���ֵΪNULL
		{
			HWND wnd = GetHWnd();
			MessageBox(wnd, "���޴��ˣ�", "ϵͳ��Ϣ", MB_OK);
			return ;
		}
		else 
		{
			system("cls");//����̨����
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���","ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");
			printone(searchone(list,tempdata.stu_num));//��ѯ��������ѧ�Ŷ�Ӧ��һ����Ϣ
			printf("�����������\n");
			char id = getch();//����һ���ַ�
			if(id != EOF) return ;
		}
	}
	else
	{
		InputBox(tempdata.grade, MAX_num , "����Ҫ��ѯ�İ༶(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.major, MAX_major , "����Ҫ��ѯ��רҵ(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.result, MAX_res , "����Ҫ��ѯ�ı�ҵ�ɼ�(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.tea_num, MAX_num , "����Ҫ��ѯ�Ľ̹���(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.post, MAX_post , "����Ҫ��ѯ�Ľ̹�ְλ(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.type, MAX_type , "����Ҫ��ѯ����Ŀ����(���������ѯ��������ֱ�ӵ��ȷ��)��");
		InputBox(tempdata.state, MAX_state , "�����Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������(���������ѯ��������ֱ�ӵ��ȷ��)��");
		system("cls");//����̨����
		printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���","ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");
		struct Node *k = list ->next;
		cnt = 0;
		while(k != NULL)//��������
		{
			if((strcmp(tempdata.grade , k->data.grade) == 0|| strcmp(tempdata.grade,"") == 0)
				&&(strcmp(tempdata.major , k->data.major) == 0|| strcmp(tempdata.major,"") == 0)
				&&(strcmp(tempdata.result , k->data.result) == 0|| strcmp(tempdata.result,"") == 0)
				&&(strcmp(tempdata.tea_num , k->data.tea_num) == 0|| strcmp(tempdata.tea_num,"") == 0)
				&&(strcmp(tempdata.post , k->data.post) == 0|| strcmp(tempdata.post,"") == 0)
				&&(strcmp(tempdata.type , k->data.type) == 0|| strcmp(tempdata.type,"") == 0)
				&&(strcmp(tempdata.state , k->data.state) == 0|| strcmp(tempdata.state,"") == 0))
			{
				printone(k);//���������ľ����
				cnt ++;
			}
			k = k->next;
		}
			if(cnt == 0)
			{
				HWND wnd = GetHWnd();
				//MessageBox (���, ��ʾ����,����,MB_OK) ;
				MessageBox(wnd,"���޴��ˣ�\n","ϵͳ��Ϣ",MB_OK);
				
			}
			else
			{	printf("�����������\n");
				char id = getch();//����һ���ַ�
				if(id != EOF) return ;
			}
	}
}
//�������
void print(struct Node* listHead)
{
	closegraph();//�ر�ͼ��
	system("cls");//����̨����
	struct Node* k = listHead->next;//ָ�����ָ��Ҫ���������
	//printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���","ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");
	while(k)
	{
		printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",k->data.stu_num,k->data.grade,k->data.major,k->data.sub,k->data.result,k->data.tea_num,k->data.post,k->data.type,k->data.state);
		k = k->next;
	}
	printf("����������ز˵���\n");
	char id = getch();//����һ���ַ�
	if(id != EOF) return; 
}
//����ѧ������
int cmpstu_num(const void *a,const void *b)
{
	return strcmp((*(struct student *)a).stu_num,(*(struct student *)b).stu_num);
}
//���ݽ̹�������
int cmptea_num(const void *a,const void *b)
{
	return strcmp((*(struct student *)a).tea_num,(*(struct student *)b).tea_num);
}
//���ݳɼ�����
int cmpres(const void *a,const void *b)
{
	if(strcmp((*(struct student *)a).result,(*(struct student *)b).result) == 0) return 0;
	else if(strcmp((*(struct student *)a).result,"��") == 0) return 1;
	else if(strcmp((*(struct student *)b).result,"��") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"��") == 0)  return 1;
	else if(strcmp((*(struct student *)b).result,"��") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"��") == 0) return 1;
	else if(strcmp((*(struct student *)b).result,"��") == 0) return -1;
	else if(strcmp((*(struct student *)a).result,"����") == 0) return 1;
	else return -1;
}
//����Ϣ��������
void sortInfo(char s)
{
	closegraph();//�ر�ͼƬ
	system("cls");//����
	struct Node *k = list;//kָ��list��ͷ
	k = (k->next)->next;
	int cnt = 0;//��Ϣ������
	while(k != NULL)//��������Ϣ������ṹ�����
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
	if(s == 'a'|| s == 'A')//ѧ������
	{
		qsort(a,cnt,sizeof(temp),cmpstu_num);
	}
	if(s == 'b' || s == 'B')//�̹�������
	{
		qsort(a,cnt,sizeof(temp),cmptea_num);
	}
	if(s == 'c' || s == 'C')//�ɼ�����
	{
		qsort(a,cnt,sizeof(temp),cmpres);
	}
	int i;
	printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n","ѧ��","�༶","רҵ","��ҵ�����Ŀ","��ҵ��Ƴɼ�","ָ����ʦ�̹���","ָ����ʦְ��","��Ŀ����","�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ�������");
	if(s >= 'a'&&  s <= 'z' )//�����Сд��ĸ
	{
		for(i = 0;i < cnt ;i++)//�������
		{
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
		}
	}
	else
	{
		for(i = cnt-1;i >= 0 ;i--)//�������
		{
			printf("%-12s\t%-20s\t%-20s\t%-60s\t%-10s\t%-10s\t%-20s\t%-20s\t%-15s\n",a[i].stu_num,a[i].grade,a[i].major,a[i].sub,a[i].result,a[i].tea_num,a[i].post,a[i].type,a[i].state);
		}
	}
	printf("����������ز˵���\n");
	char id = getch();//��ȡһ����������Է��ز˵�
	if(id != EOF) return; 
}
int getyear()
{
	int year;
	time_t now;
	struct tm*p;
	time(&now);
	p = gmtime(&now);
	year = 1900+p->tm_year; //��ǰ���
	return year; //�����������
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
			//MessageBox (���, ��ʾ����,����,MB_OK) ;
			MessageBox(wnd,"û�и�ѡ�����������\n","ϵͳ��Ϣ",MB_OK);
			closegraph();//�ر�ͼƬ
}
void menu_main_search()
{
	while(true)
	{
		cleardevice();	//����
		initgraph(1000, 600);  //��ʼ�������С
		loadimage(0,"bkg.jpg");//����ͼƬ������ͼ
		setbkmode(TRANSPARENT);//��������͸����
		//�����ı����塢��ɫ������
		setcolor(DARKGRAY);
		setfont(40, 0, "����");
		outtextxy(300, 10, "��ҵ��ƹ���ϵͳ");
		setcolor (YELLOW);
	    setfont(25,0,"����");
	    outtextxy(300,100,"��ѡ�������:");
		setcolor(BLACK);
	             setfont(35,0,"΢���ź�");
				 outtextxy(380,150,_T("1.��ѯ������Ϣ"));
	             outtextxy(380,220,_T("2.��ѯ������Ϣ"));
	             outtextxy(380,290,_T("0.����"));
		int id = getch();//��ȡ�û�����Ĺ������
		if(id=='0')
		{
			closegraph();//�ر�ͼƬ
			return ;
		}
		else if(id=='1')
			print(list);//���������Ϣ����ѯȫ��
		else if(id=='2')
			searchpart();//��ϲ�ѯ
		else 
			agin();//�����������
	}
}
void menu_main_sort()
{
	while(true)
	{
		cleardevice();   //	����
		initgraph(1000, 600);  //��ʼ�������С
		loadimage(0,"bkg.jpg");//����ͼƬ������
		setbkmode(TRANSPARENT);//�����ı�͸����
		//�����ı����塢��ɫ��������ɽ��沼��
		setcolor(DARKGRAY);
		setfont(40, 0, "����");
		outtextxy(300, 10, "��ҵ��ƹ���ϵͳ");
		setcolor (YELLOW);
	    setfont(25,0,"����");
	    outtextxy(300,100,"��ѡ�������(Сд���򣬴�д����):");
		setcolor(BLACK);
	    setfont(35,0,"΢���ź�");
		outtextxy(380,150,_T("a.��ѧ��"));
	    outtextxy(380,220,_T("b.���̹���"));
		outtextxy(380,290,_T("c.����ҵ��Ƴɼ�"));
	    outtextxy(380,360,_T("0.����"));
		char id = getch();//��ȡ�û����빦�����
		if(id == '0')
		{
			closegraph();//�ر�ͼ�ν���
			return ;
		}
		else if(id == 'a'||id == 'A'||id == 'b'|| id == 'B'||id == 'c'|| id == 'C')
			sortInfo(id);//����
		else agin();//��������
	}
}
//���˵�
void menu_main()
{	
	while(true)
	{	
		cleardevice(); //����
		initgraph(1000, 600);     //��ʼ�������С
		loadimage(0,"bkg.jpg"); //����ͼƬ������ͼ
		setbkmode(TRANSPARENT);//��������͸����
		//���������ı���ɫ�����塢���꣬��ɽ��沼��
		setcolor(DARKGRAY);
		setfont(40, 0, "����");
		outtextxy(300, 10, "��ҵ��ƹ���ϵͳ");
		setcolor (YELLOW);
	    setfont(25,0,"����");
	    outtextxy(300,100,"��ѡ�������:");
		setcolor(BLACK);
	             setfont(35,0,"΢���ź�");
	             outtextxy(200,130,_T("1.��ҵ�����Ϣ��ѯ"));
	             outtextxy(200,200,_T("2.��ҵ�����Ϣ����"));
				 outtextxy(200,270,_T("3.��ҵ�����Ϣͳ��"));
				 outtextxy(200,340,_T("4.ɾ����Ϣ"));
				 outtextxy(500,130,_T("5.�޸���Ϣ"));
				 outtextxy(500,200,_T("6.�����Ϣ"));
				 outtextxy(500,270,_T("7.�����Ϣ"));
	             outtextxy(500,340,_T("0.����"));
		end:
		int id = getch();//�����û�ѡ�������
		if(id == '0')
		{
			closegraph();//�ر�ͼƬ
			return menu_user();//�����û���¼����
		}
		else if(id == '1')
		{
			menu_main_search();//��ѯ����
		}
		else if(id == '2')
		{
			menu_main_sort();//�������
		}
		else if(id == '3')
		{			
			Stat();//ͳ����Ϣ
		}
		else if(id == '4')
		{
			 delete_Num(list);//ɾ����Ϣ
		}
		else if(id == '5')
		{
			ModifyInfo(list);//�޸���Ϣ
		}
		else if(id == '6')
		{
			student tempdata;//��ʱ�洢һ���ҵ�����Ϣ
			do
			{	InputBox(tempdata.stu_num, MAX_grade , "����ѧ�ţ�");
			}while(judge(tempdata.stu_num) == 0);//�жϸ�ʽ
			if (searchone(list,tempdata.stu_num) != NULL)//�ж�ѧ���Ƿ��Ѵ���
			{
				HWND wnd = GetHWnd();
				MessageBox(wnd, "��ѧ���Ѵ���,���������룡", "ϵͳ��Ϣ", MB_OK);
				goto end;
			}
			do
			{	InputBox(tempdata.grade, MAX_grade , "����༶��");
			}while(judge(tempdata.grade) == 0);
			do
			{	InputBox(tempdata.major, MAX_major, "����רҵ��");
			}while(judge(tempdata.major) == 0);
			do
			{	InputBox(tempdata.sub, MAX_sub , "�����ҵ�����Ŀ��");
			}while(judge(tempdata.sub) == 0);
			do
			{	InputBox(tempdata.result, MAX_res , "�����ҵ��Ƴɼ���");
			}while(judge(tempdata.result) == 0);
			do
			{	InputBox(tempdata.tea_num, MAX_num , "����ָ����ʦ�̹��ţ�");
			}while(judge(tempdata.tea_num) == 0);
			do
			{	InputBox(tempdata.post, MAX_post , "����ָ����ʦְ�ƣ�");
			}while(judge(tempdata.post) == 0);
			do
			{	InputBox(tempdata.type, MAX_type , "������Ŀ���ࣺ");
			}while(judge(tempdata.type) == 0);
			do
			{	InputBox(tempdata.state, MAX_state , "�Ƿ���ʵ�顢ʵϰ������ʵ�����������ʵ������ɣ�");
			}while(judge(tempdata.state) == 0);
			addInfo(list,tempdata); //�����Ϣ
			HWND wnd = GetHWnd();
			MessageBox(wnd, "��ӳɹ�", "ϵͳ��Ϣ", MB_OK);
		}
		else if(id == '7')
		{
			spotcheck();//�����Ϣ
		}
		else 
		{
			agin();//��Ҫ�������������
		}
	}
}
void menu_user()
{
				 initgraph(1000, 600);      //��ʼ��
				 loadimage(0,"bkg.jpg");	//���ر���ͼ
				 setbkmode(TRANSPARENT);	//���屳��͸����  ȥ����ɫ
				 setlinecolor(BLACK);		//����������ɫΪ��
				 setcolor(DARKGRAY);		//����������ɫΪ����ɫ
		         setfont(40, 0, "����");	//��������Ϊ����
		         outtextxy(300, 10, "��ҵ��ƹ���ϵͳ");//��������
		         setcolor (YELLOW);			//����������ɫΪ��
	             setfont(25,0,"����");		//��������Ϊ����
	             outtextxy(300,100,"��ѡ�������:");//��������
	             setcolor(BLACK);	//����������ɫΪ��
	             setfont(35,0,"΢���ź�");//����Ϊ΢���ź�
	             outtextxy(380,150,_T("1.�û���¼"));//��������
	             outtextxy(380,220,_T("2.ע��"));
	             outtextxy(380,290,_T("0.�˳�"));
}
int main()
{
	list = creatlist();//��������
	readfile(list); //��ʼ��ʱ����ļ�   ��Ϣ�Ķ�ʱд���ļ�
	char id;//��Ź������
	do
	{
		menu_user();//�û���¼ϵͳ
		id = getch();//ֱ�ӻ�ȡһ���ַ�
		if(id == '1')
		{
			logon();//�û���¼����
		}
		else if (id == '2')
		{
			Register();//ע�ắ��
		}
		else if(id == '0')
		{
			system("cls");//����
			savefile(list);//д���ļ���������Ϣ
			HWND wnd = GetHWnd();//�ú������ڻ�ȡͼ�δ��ڵľ����
			//MessageBox (���, ��ʾ����,����,MB_OK) ;
					MessageBox(wnd,"�ɹ��˳�ϵͳ\n","ϵͳ��Ϣ",MB_OK);
					closegraph();
					return 0;
		}
		else
		{
			agin();//�����������
		}
	}while(id);
	return 0;
}