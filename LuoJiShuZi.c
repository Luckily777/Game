#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void slashCard(int arr[]){
	srand((unsigned int)time(NULL));
	int s;
	int str[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i;
	for (i = 0; i < 4; i++){
		s = rand() % 10;
		while (str[s] == -1){
			s++;
			if (s == 10){
				s = 0;
			}
		}
		arr[i] = str[ s];
		str[s] = -1;
	}
}

void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	putchar('\n');
}

int judgeAns(int ans[], int arr[]){
	int i, j;
	int countA = 0;
	int countB = 0;
	for (i = 1; i <= 4; i++){
		for (j = 1; j <= 4; j++){
			if (ans[i] == arr[j]){
				countB++;
				break;
			}
		}
	}
	for (i = 0; i < 4; i++){
		if (ans[i] == arr[i]){
			countA++;
		}

	}
	countB = countB - countA;
	printf("%dA%dB\n", countA, countB);
	if (countA == 4)
	{
		return 1;
	}
	return 0;
}

int main(){
	int i, j;
	int arr[4];
	slashCard(arr);
	int ans[4];
	for (i = 1; i <= 8; i++){
		printf("第%d次输入：\n", i);
		for (j = 0; j < 4; j++)
		{
			scanf("%d", &ans[j]);
		}
		if (judgeAns(ans, arr))
		{
			break;
		}
	}
	if (i == 9){
		printf("您的机会已用尽！\n");
		printf("正确答案为：\n");
		printArray(arr, 4);
	}
	else{
		printf("恭喜 您的挑战成功！");
	}

	system("pause");
	return 0;
}
