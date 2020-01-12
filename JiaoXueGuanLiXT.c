#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

#define N 3//定义数据总数为10
enum Sex//枚举性别的两种可能
{
	male,female
};

struct Student{
	char name[20];
	int num;//100-109
	char sex[10];
	int Math;//100分制
}stu[N] = { { "王一", 100, "male", 100 }, {"孙二",101,"female",56}, {"张三",102,"male",85} };

void PrintUi(){//登陆界面函数
	printf("\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                 ._______________________.                    ║\n");
	printf("\t║                 | _____________________ |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I    教学管理系统   I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I___________________I |                    ║\n");
	printf("\t║                 !_______________________!                    ║\n");
	printf("\t║                     ._[__________]_.                         ║\n");
	printf("\t║                 .___|_______________|___.                    ║\n");
	printf("\t║                  |:::  ____            |                     ║\n");
	printf("\t║                  |     密码：          |                     ║\n");
	printf("\t║                  !_____________________!                     ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int Land(){//登陆函数
	printf("请输入您的登陆密码：");
	int Psssword;//初始化密码数据
	int a = 7777777;
	for (int n = 1; n <= 3; n++){
	scanf("%d", &Psssword);

		if (Psssword==a){
			system("cls");
			printf("您的密码输入正确！");
			printf("正在登陆，请稍等…………");
			Sleep(4000);//登陆延时程序，产生短暂的登陆状态
			system("cls");
			return 1;
		}
		else{
			printf("您的密码输入错误，请您重新输入！\n",n);
		}
		if (n == 3){//登陆次数为3时 机会用尽 
		printf("您的机会已用尽！");
		return -1;
	}

  }
	return 0;
}

void PrintMode(){//系统菜单页面
	printf("**************************************\n");
	printf("**************************************\n");
	printf("******                        ********\n");
	printf("******       教 学 系 统      ********\n");
	printf("******                        ********\n");
	printf("******                        ********\n");
	printf("******     1. 录 入 信 息     ********\n");
	printf("******     2. 输 出 信 息     ********\n");
	printf("******     3. 查 询 信 息     ********\n");
	printf("******     4. 成 绩 排 名     ********\n");
	printf("******     0. 退 出 系 统     ********\n");
	printf("******                        ********\n");
	printf("******                        ********\n");
	printf("**************************************\n");
	printf("**************************************\n");
}


int Welcome()
{//欢迎函数
	PrintUi(1);//打印主界面函数
	int i = Land(1);//登陆界面的调用
	if (i == 1){//当登陆成功则打开菜单页面
		PrintMode(1);
		return 0;
	}
	else
	{
		return -1;
	}
}

int Search(int i)
{
	int n;
	for (n = 0; n < N; n++){
		if (i == stu[n].num){//如果所输入的学号和系统内的学号相等，则返回此位的序号
			return  n;
		}
	}
	return -1;//如果未找到，则返回-1
}

void InPut()
{//输入函数
	int i;
	printf("提示：姓名 学号（100-109） 性别（male,female） 数学成绩（100分制）\n");
	printf("请输入全部的学生信息：");
	for (i = 0; i < N; i++){
		scanf("%s%d%s%f", stu[i].name, &stu[i].num, stu[i].sex, &stu[i].Math);
	}
}

void SpecialPut(){
	int i,c;
	printf("请输入您要查找的学号（100-109）：");
	while (1){
		scanf("%d", &i);
		c = Search(i);
		if ( c== -1){
			printf("您的输入有误");
			continue;
		}
		printf("姓名：%s\n学号：%d\n性别：%s\n数学：%d\n",stu[c].name, stu[c].num, stu[c].sex, stu[c].Math);
		break;
	}

}

void OutPut(){
	int i;
	printf("----------------------------------------------");
	printf("|姓名：   |学号：    |性别：   |数学：   |");
	for (i = 0; i < N; i++){
		printf("|%s     |%d     |%s    |%d    |\n", stu[i].name, stu[i].num, stu[i].sex,stu[i].Math);
	}
	printf("----------------------------------------------");
}


void Rand(){
	int i, j, num,math;//设置转换的中介量
	char name[20],sex[10];
	for (i = 0; i < N - 1; i++){

		for (j = i+1; j < N; j++){

			if (stu[j].Math>stu[i].Math){

				math = stu[j].Math;
				stu[j].Math = stu[i].Math;
				stu[i].Math = math;

				strcpy(name, stu[j].name);
				strcpy(stu[j].name, stu[i].name);
				strcpy(stu[i].name, name);

				num = stu[j].num;
				stu[j].num = stu[i].num;
				stu[i].num = num;

				strcpy(sex , stu[j].sex);
				strcpy(stu[j].sex, stu[i].sex);
				strcpy(stu[i].sex, sex);


			}
		}
	}
	printf("成绩的排名为：");
	OutPut();
}
 

int main(){
	int c = Welcome(1);
	if (c == 0)
	{
		int choice;
		printf("请输入您要进行的操作序号：");
		scanf("%d", &choice);
		switch (choice){
		case 1: InPut();//信息输入
			break;
		case 2: OutPut();//信息全部输入
			break;
		case 3: SpecialPut();//按学号查找并输出此学生的信息
			break;
		case 4: Rand();//科目成绩排名
			break;
		case 0://退出系统
			system("cls");
			printf("您选择退出系统");
			break;
		}
	}
	system("pause");
	return 0;
}