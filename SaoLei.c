#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define MAX_ROW 12
#define MAX_COL 12
#define MAX_MINE 10

void MenuUi(){//打印初始化的开始界面
	printf("\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("\t║                                                              ║\n");
	printf("\t║        欢迎使用扫雷对战程序        祝您玩的愉快挑战无极限       ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                 ._______________________.                    ║\n");
	printf("\t║                 | _____________________ |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I     扫    雷      I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I___________________I |                    ║\n");
	printf("\t║                 !_______________________!                    ║\n");
	printf("\t║                     ._[__________]_.                         ║\n");
	printf("\t║                 .___|_______________|___.                    ║\n");
	printf("\t║                  |::: ____             |                     ║\n");
	printf("\t║                  |    ~~~~ [CD-ROM]    |                     ║\n");
	printf("\t║                  !_____________________!                     ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║          1.开始游戏                 0.离开游戏               ║\n");
	printf("\t║                                                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int ChoiceStart(int i){// 进行选择，是进入游戏还是离开游戏
	while (1){
		scanf("%d", &i);
		if (i == 1){//进入游戏
			system("cls");/*清屏*/
			return 1;
		}
		else if (i == 0){//退出游戏
			system("cls");/*清屏*/
			printf("欢迎您的下次挑战！\n");
			break;
		}
		else {
			printf("您的输入有误,请您重新输入：\n");
			continue;
		}
	}
	return 0;
}

void Init(char ShowMap[MAX_ROW][MAX_COL], char MineMap[MAX_ROW][MAX_COL]){
	int i, j;
	srand((unsigned int)time(NULL));//产生随机时间戳
	int count = MAX_MINE;//初始化雷数
	for (i = 1; i < (MAX_ROW - 1); i++){//定义地图左右两侧除过第一行和最后一行的所有墙壁
		ShowMap[i][0] = '*';
		ShowMap[i][MAX_COL - 1] = '*';
		MineMap[i][0] = '*';
		MineMap[i][MAX_COL - 1] = '*';
	}
	for (i = 0; i < MAX_ROW; i += (MAX_ROW-1)){//定义地图第一行和最后一行的所以墙壁
		for (j = 0; j < MAX_COL; j++){
			ShowMap[i][j] = '*';
			ShowMap[i][j] = '*';
			MineMap[i][j] = '*';
			MineMap[i][j] = '*';
		}
	}
	for (i = 1; i < (MAX_ROW - 1); i++){//定义除过墙壁以外正儿八经的地图板块
		for (j = 1; j < (MAX_COL - 1); j++){
			ShowMap[i][j] = 'x';
			MineMap[i][j] = 'x';
		}
	}
	while (count > 0){//利用随机数，来随机布置地雷的地图
		int row = (rand() % (MAX_ROW - 2)) + 1;
		int col = (rand() % (MAX_COL - 2)) + 1;
		if (MineMap[row][col] == '3'){//若已经布雷，则重新布置
			continue;
		}
		MineMap[row][col] = '3';
		count--;//总雷数减少，直到为零开始
	}

}

void PrintMap(char Map[MAX_ROW][MAX_COL]){//打印地图
	int i, j;
	for (i = 0; i < MAX_ROW; i++){
		for (j = 0; j < MAX_COL; j++){
			printf("%c ", Map[i][j]);
		}
		printf("\n");
	}
}

void InPut(char ShowMap[MAX_ROW][MAX_COL], int *row, int *col){
	while (1){
		printf("请您输出要翻开的坐标（10x10）：");
		scanf("%d %d", row, col);//输入要翻开的坐标；
		if (*row < 1 || *row >= MAX_ROW  || *col < 1 || *col >= MAX_COL){//输入的范围越界的话，则重新输入
			printf("您的输入有误！\n");
			continue;
		}
		if (ShowMap[*row][*col] != 'x'){//若是已经被翻开的地图，则也需要重新翻开
			printf("当前位置已经被翻开！\n");
			continue;
		}
		break;
	}
}

int CheckMine(char MineMap[MAX_ROW][MAX_COL],int row, int col){
	if (MineMap[row][col] == '3'){//检测输入的是否是雷，若是雷则判定游戏结束
		return 1;
	}
	return 0;
}

int CheckLast(int *count){//判定翻开的是否是最后一个非雷地图，若是则游戏胜利
	*count += 1;
	if (*count == 90){
		return 1;
	}
	return 0;
}

void UpData(char ShowMap[MAX_ROW][MAX_COL],char MineMap[MAX_ROW][MAX_COL],
	int row, int col){//统计周围9个方块之中的总雷数
	int count = 0;
	for (int r = row - 1; r <= row + 1; r++){
		for (int c = col - 1; c <= col + 1; c++){
			if (r < 1 || r > (MAX_ROW-2) || c < 1 || c > (MAX_COL-2)){
				continue;
			}
			if (MineMap[r][c] == '3'){
				count++;
			}
		}
	}
	ShowMap[row][col] = count+'0';//在此块上显示雷数
}

void Game(){
	char ShowMap[MAX_ROW][MAX_COL] = {0};//初始化玩家打开的地图
	char MineMap[MAX_ROW][MAX_COL] = {0};//初始化地雷分布的地图
	int count = 0;///检测最终所剩下的方块数
	Init(ShowMap,MineMap);//给展示地图和地雷地图进行赋值
	PrintMap(MineMap);//在测试的时候为了能够确保正确性，则将有雷的地图也打印出来；
	printf("------------------------\n");
	while (1){
		PrintMap(ShowMap);//打印地图
		int row = 0;
		int col = 0;
		InPut(ShowMap,&row, &col);//输入需要翻开的坐标
		if (CheckMine(MineMap, row, col)){//检查输入的坐标是否正确
			PrintMap(MineMap);//将最终的雷图打印出来，以让玩家输的心服口服
			printf("您踩雷了！");
			break;
		}
		if (CheckLast(&count)){
			printf("你赢了！");
			break;
		}
		system("cls");//没输入一次进行清屏，避免地图太多，造成视觉问题
		PrintMap(MineMap);
		printf("------------------------\n");
		UpData(ShowMap,MineMap,row, col);//计算周围九个格子中所包含的雷数
	}
}

int main(){
	int i=0;
	int choice = 0;
	MenuUi(1);
	printf("请输入您的选择:");
	choice = ChoiceStart(i);
	if (choice == 1){
		Game(1);
	}
	system("pause");
	return 0;
}