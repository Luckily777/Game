#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_ROW 8
#define MAX_COL 8

int Boxs;//统计其中所剩未完成箱子的个数
int x, y;//用此坐标来定位小人的位置


int map[MAX_ROW][MAX_COL] = {
	{ 0, 0, 1, 1, 1, 0, 0, 0 },
	{ 0, 0, 1, 4, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 1, 1, 1, 1 },
	{ 1, 1, 1, 3, 0, 3, 4, 1 },
	{ 1, 4, 0, 3, 2, 1, 1, 1 },
	{ 1, 1, 1, 1, 3, 1, 0, 0 },
	{ 0, 0, 0, 1, 4, 1, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0 }
};

/**
*	0	表示空
*	1	表示墙
*	2	表示人
*	3	表示箱子
*	4	表示目的地（球）
*	5	表示已完成的箱子
*/



//1.打印菜单
//2.选择游戏关卡
//3.玩家开始移动
//4.判断游戏是否成功

void MenuUi(){
	printf("\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("\t║                                                              ║\n");
	printf("\t║      欢迎使用推箱子游戏程序     祝您玩的愉快挑战无极限       ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                 ._______________________.                    ║\n");
	printf("\t║                 | _____________________ |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I     推 箱 子      I |                    ║\n");
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
	printf("\t║                谁 怕 ？ 一 蓑 烟 雨 任 平 生。              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║          1.开始游戏                 0.离开游戏               ║\n");
	printf("\t║                                                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int ChoiceStart(int i){
	printf("请输入您的选择：");
	while (1){
		scanf("%d", &i);
		if (i == 1){
			system("cls");/*清屏*/
			return 1;
		}
		if (i == 0){
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

void InitData(){
	int i, j;
	for (i = 0; i < MAX_ROW; i++){
		for (j = 0; j < MAX_COL; j++){
			//遍历到2（人）时，记录人的坐标。x， y是前面定义的全局变量
			if (map[i][j] == 2){
				x = j;
				y = i;
			}

			if (map[i][j] == 3){//计算地图之中箱子的数目
				Boxs++;
			}
		}
	}
}
void drawMap(){
	int i, j;
	for (i = 0; i < MAX_ROW; i++){
		for (j = 0; j < MAX_COL; j++){
			switch (map[i][j]){
			case 0:
				printf("  ");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				printf("♀");
				break;
			case 3:
				printf("◆");
				break;
			case 4:
				printf("●");
				break;
			case 5:
				printf("★");
				break;
			}
		}
		printf("\n");
	}
}

void MoveUp(){
	if (y == 0){//当上方直接是墙的时候，直接进行返回
		return;
	}
	int Ux = x;
	int Uy = y - 1;
	if (map[Uy][Ux] == 1||map[Uy][Ux]==5){//若上方是墙或者是已经完成的箱子，则不动
		return;
	}
	if (map[Uy][Ux] == 3){//在上方是箱子的情况下
		if (map[Uy - 1][Ux] == 1){//若再上方是墙的话，依然不动
			return;
		}
		if (map[Uy - 1][Ux] == 4){//若上方是终点的话
			map[Uy - 1][Ux] = 5;//将箱子向前移动，达到终点
			Boxs--;
		}
		else{
			map[Uy - 1][Ux] = 3;//若上方没有任何东西，则箱子肯定会向上一步
		}
	}
	map[y][x] = 0;//将人的位置置换为0
	map[Uy][Ux] = 2;//将原箱子的位置置换为人
	y = Uy;//将人的位置进行改变
}

void MoveDown(){
	int D = MAX_ROW - 1;
	if (y == D){//下方是墙，则不移动；
		return;
	}
	int Dx = x;
	int Dy = y + 1;
	if (map[Dy][Dx] == 1 || map[Dy][Dx] == 5){//若下方是墙或者是已经完成的箱子，则不动
		return;
	}
	if (map[Dy][Dx] == 3){//在下方是箱子的情况下
		if (map[Dy + 1][Dx] == 1){//若再下方是墙的话，依然不动
			return;
		}
		if (map[Dy + 1][Dx] == 4){//若下方是终点的话
			map[Dy + 1][Dx] = 5;//将箱子向下方移动，达到终点
			Boxs--;
		}
		else{
			map[Dy + 1][Dx] = 3;//若下方没有任何东西，则箱子肯定会向下一步
		}
	}
	map[y][x] = 0;//将人的位置置换为0
	map[Dy][Dx] = 2;//将原箱子的位置置换为人
	y = Dy;//将人的位置进行改变
}


void MoveLeft(){
	if (x == 0){
		return;
	}//左边是墙的话，则不动；
	int Lx = x - 1;
	int Ly = y;

	if (map[Ly][Lx] == 1 || map[Ly][Lx] == 5){//若左方是墙或者是已经完成的箱子，则不动
		return;
	}
	if (map[Ly][Lx] == 3){//在左方是箱子的情况下
		if (map[Ly][Lx - 1] == 1){//若再左方是墙的话，依然不动
			return;
		}
		if (map[Ly][Lx - 1] == 4){//若左方是终点的话
			map[Ly][Lx - 1] = 5;//将箱子向左方移动，达到终点
			Boxs--;
		}
		else{
			map[Ly][Lx - 1] = 3;//若左方没有任何东西，则箱子肯定会向左方一步
		}
	}
	map[y][x] = 0;//将人的位置置换为0
	map[Ly][Lx] = 2;//将原箱子的位置置换为人
	x = Lx;//将人的位置进行改变
}


void MoveRight(){
	int R = MAX_COL - 1;
	if (x == R){
		return;
	}
	int Rx = x + 1;
	int Ry = y;
	if (map[Ry][Rx] == 1 || map[Ry][Rx] == 5){//若右方是墙或者是已经完成的箱子，则不动
		return;
	}
	if (map[Ry][Rx] == 3){//在右方是箱子的情况下
		if (map[Ry][Rx + 1] == 1){//若再右方是墙的话，依然不动
			return;
		}
		if (map[Ry][Rx + 1] == 4){//若右方是终点的话
			map[Ry][Rx + 1] = 5;//将箱子向右方移动，达到终点
			Boxs--;
		}
		else{
			map[Ry][Rx + 1] = 3;//若右方没有任何东西，则箱子肯定会向右一步
		}
	}
	map[y][x] = 0;//将人的位置置换为0
	map[Ry][Rx] = 2;//将原箱子的位置置换为人
	x = Rx;//将人的位置进行改变
}



int Game(){
	char direction;
	InitData();
	while (1){
		system("cls");
		drawMap();
		printf("请输入你所需要移动的方向(小写字母)：（W为上，A为左，S为下，D为右）\n");
		if (!Boxs){
			break;
		}
		direction = getch();
		switch (direction){
		case 'w':
			MoveUp();
			break;
		case 'a':
			MoveLeft();
			break;
		case 's':
			MoveDown();
			break;
		case 'd':
			MoveRight();
			break;
		}
	}
	printf("您已通关游戏!\n");
	return 0;
}


int main(){
	int i = 0;
	int choice = 0;
	MenuUi(1); 
	{
		choice = ChoiceStart(i);
		if (choice == 1){
			Game();
		}
	}
	system("pause");
	return 0;
}
