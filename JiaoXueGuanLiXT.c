#define  _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

#define N 3//������������Ϊ10
enum Sex//ö���Ա�����ֿ���
{
	male,female
};

struct Student{
	char name[20];
	int num;//100-109
	char sex[10];
	int Math;//100����
}stu[N] = { { "��һ", 100, "male", 100 }, {"���",101,"female",56}, {"����",102,"male",85} };

void PrintUi(){//��½���溯��
	printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                 ._______________________.                    �U\n");
	printf("\t�U                 | _____________________ |                    �U\n");
	printf("\t�U                 | I                   I |                    �U\n");
	printf("\t�U                 | I    ��ѧ����ϵͳ   I |                    �U\n");
	printf("\t�U                 | I                   I |                    �U\n");
	printf("\t�U                 | I___________________I |                    �U\n");
	printf("\t�U                 !_______________________!                    �U\n");
	printf("\t�U                     ._[__________]_.                         �U\n");
	printf("\t�U                 .___|_______________|___.                    �U\n");
	printf("\t�U                  |:::  ____            |                     �U\n");
	printf("\t�U                  |     ���룺          |                     �U\n");
	printf("\t�U                  !_____________________!                     �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}

int Land(){//��½����
	printf("���������ĵ�½���룺");
	int Psssword;//��ʼ����������
	int a = 7777777;
	for (int n = 1; n <= 3; n++){
	scanf("%d", &Psssword);

		if (Psssword==a){
			system("cls");
			printf("��������������ȷ��");
			printf("���ڵ�½�����Եȡ�������");
			Sleep(4000);//��½��ʱ���򣬲������ݵĵ�½״̬
			system("cls");
			return 1;
		}
		else{
			printf("��������������������������룡\n",n);
		}
		if (n == 3){//��½����Ϊ3ʱ �����þ� 
		printf("���Ļ������þ���");
		return -1;
	}

  }
	return 0;
}

void PrintMode(){//ϵͳ�˵�ҳ��
	printf("**************************************\n");
	printf("**************************************\n");
	printf("******                        ********\n");
	printf("******       �� ѧ ϵ ͳ      ********\n");
	printf("******                        ********\n");
	printf("******                        ********\n");
	printf("******     1. ¼ �� �� Ϣ     ********\n");
	printf("******     2. �� �� �� Ϣ     ********\n");
	printf("******     3. �� ѯ �� Ϣ     ********\n");
	printf("******     4. �� �� �� ��     ********\n");
	printf("******     0. �� �� ϵ ͳ     ********\n");
	printf("******                        ********\n");
	printf("******                        ********\n");
	printf("**************************************\n");
	printf("**************************************\n");
}


int Welcome()
{//��ӭ����
	PrintUi(1);//��ӡ�����溯��
	int i = Land(1);//��½����ĵ���
	if (i == 1){//����½�ɹ���򿪲˵�ҳ��
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
		if (i == stu[n].num){//����������ѧ�ź�ϵͳ�ڵ�ѧ����ȣ��򷵻ش�λ�����
			return  n;
		}
	}
	return -1;//���δ�ҵ����򷵻�-1
}

void InPut()
{//���뺯��
	int i;
	printf("��ʾ������ ѧ�ţ�100-109�� �Ա�male,female�� ��ѧ�ɼ���100���ƣ�\n");
	printf("������ȫ����ѧ����Ϣ��");
	for (i = 0; i < N; i++){
		scanf("%s%d%s%f", stu[i].name, &stu[i].num, stu[i].sex, &stu[i].Math);
	}
}

void SpecialPut(){
	int i,c;
	printf("��������Ҫ���ҵ�ѧ�ţ�100-109����");
	while (1){
		scanf("%d", &i);
		c = Search(i);
		if ( c== -1){
			printf("������������");
			continue;
		}
		printf("������%s\nѧ�ţ�%d\n�Ա�%s\n��ѧ��%d\n",stu[c].name, stu[c].num, stu[c].sex, stu[c].Math);
		break;
	}

}

void OutPut(){
	int i;
	printf("----------------------------------------------");
	printf("|������   |ѧ�ţ�    |�Ա�   |��ѧ��   |");
	for (i = 0; i < N; i++){
		printf("|%s     |%d     |%s    |%d    |\n", stu[i].name, stu[i].num, stu[i].sex,stu[i].Math);
	}
	printf("----------------------------------------------");
}


void Rand(){
	int i, j, num,math;//����ת�����н���
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
	printf("�ɼ�������Ϊ��");
	OutPut();
}
 

int main(){
	int c = Welcome(1);
	if (c == 0)
	{
		int choice;
		printf("��������Ҫ���еĲ�����ţ�");
		scanf("%d", &choice);
		switch (choice){
		case 1: InPut();//��Ϣ����
			break;
		case 2: OutPut();//��Ϣȫ������
			break;
		case 3: SpecialPut();//��ѧ�Ų��Ҳ������ѧ������Ϣ
			break;
		case 4: Rand();//��Ŀ�ɼ�����
			break;
		case 0://�˳�ϵͳ
			system("cls");
			printf("��ѡ���˳�ϵͳ");
			break;
		}
	}
	system("pause");
	return 0;
}