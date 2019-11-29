#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int Leap(int year){//判断是否是闰年
	if (year % 400 == 0){
		return 1;
	}
	if (year % 4 == 0 && year % 100 != 0){
		return 1;
	}
	return 0;

}

int DayCount(int year){//计算在所需要输出年份之前的总天数
	int count = 0;
	count = 365 * (year - 1900);
	for (int i=1900; i < year; i++){
		if (Leap(i) == 1){
			count++;
		}
	}
	return count;
}

void LayOut(int year, int month){//计算所需要输出的月份对应的星期，并且进行顺序的打印
	int i;
	int n;
	int M[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int daysum = 0;
	daysum = DayCount(year);
	if (month <= 2){//若是2月，只需要增加1月的日子
		daysum += 31;
	}
	if (month > 2){//如果大于二月的话，先进行求闰年，若是闰年则加1；
		daysum += Leap(year);
		for (i = 0; i < month - 1; i++){
			daysum += M[i];
		}
	}
	n = (daysum % 7) + 1;
	
	printf("日 一 二 三 四 五 六 \n");
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