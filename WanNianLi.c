#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Leap(int year){//�ж��Ƿ�������
	if (year % 400 == 0){
		return 1;
	}
	if (year % 4 == 0 && year % 100 != 0){
		return 1;
	}
	return 0;

}

int DayCount(int year){//����������Ҫ������֮ǰ��������
	int count = 0;
	count = 365 * (year - 1900);
	for (int i=1900; i < year; i++){
		if (Leap(i) == 1){
			count++;
		}
	}
	return count;
}

void LayOut(int year, int month){//��������Ҫ������·ݶ�Ӧ�����ڣ����ҽ���˳��Ĵ�ӡ
	int i;
	int n;
	int M[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysum = 0;
	daysum = DayCount(year);
	if (month <= 2){//����2�£�ֻ��Ҫ����1�µ�����
		daysum += 31;
	}
	if (month > 2){//������ڶ��µĻ����Ƚ��������꣬�����������1��
		daysum += Leap(year);
		for (i = 0; i < month - 1; i++){
			daysum += M[i];
		}
	}
	n = (daysum % 7) + 1;
	
	printf("�� һ �� �� �� �� �� \n");
	int count = 0;
	for (i = 0; i < n; i++){
		printf("   ");
		count+=1;
	}
	for (i = 1; i < M[month]; i++){
		printf("%-2d ", i);
		count += 1;
		if (count %7==0){
			printf("\n");
		}
	}
}



int main(){
	int year = 0;
	int month = 0;
	scanf("%d%d", &year, &month);
	LayOut(year, month);
	system("pause");
	return 0;
}