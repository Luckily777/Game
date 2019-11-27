#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

void MenuUi(){
	printf("\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("\t║                                                              ║\n");
	printf("\t║      欢迎使用五子棋对战程序     祝您玩的愉快挑战无极限       ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                 ._______________________.                    ║\n");
	printf("\t║                 | _____________________ |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I     五 子 棋      I |                    ║\n");
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
	printf("\t║         寒 星 溪 月 疏 星 首，花 残 二 月 并 白 莲。         ║\n");
	printf("\t║         雨 月 金 星 追 黑 玉，松 丘 新 宵 瑞 山 腥。         ║\n");
	printf("\t║         星 月 长 峡 恒 水 流，白 莲 垂 俏 云 浦 岚。         ║\n");
	printf("\t║         黑 玉 银 月 倚 明 星，斜 月 明 月 堪 称 朋。         ║\n");
	printf("\t║         二 十 六 局 先 弃 二，直 指 游 星 斜 彗 星。         ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║          1.开始游戏                 0.离开游戏               ║\n");
	printf("\t║                                                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int ChoiceStart(int i){
	while (1){
		scanf("%d", &i);
		if (i == 1){
			system("cls");/*清屏*/
			return 1;
		}
		else if (i == 0){
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


void MenuMode(){
	printf("\t╔══════════════════════════════════════════════════════════════╗\n");
	printf("\t║                                                              ║\n");
	printf("\t║      欢迎使用五子棋对战程序     祝您玩的愉快挑战无极限       ║\n");
	printf("\t║                                                              ║\n");
	printf("\t║                 ._______________________.                    ║\n");
	printf("\t║                 | _____________________ |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I                   I |                    ║\n");
	printf("\t║                 | I     五 子 棋      I |                    ║\n");
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
	printf("\t║          1.人人模式                 2.人机模式              ║\n");
	printf("\t║                                                              ║\n");
	printf("\t╚══════════════════════════════════════════════════════════════╝\n");
}

int ChoiceMode(int i){
	while (1){
		scanf("%d", &i);
		if (i == 1){
			return 1;
		}
		if (i == 2){
			return 2;
		}
		else {
			printf("您的输入有误,请重新输入：\n");
			continue;
		}
	}
}

void Init(char chessBoard[MAX_ROW][MAX_COL]){
	srand((unsigned int)time(NULL));
	memset(chessBoard, ' ', MAX_ROW * MAX_COL * sizeof(char));
}

void Print(char chessBoard[MAX_ROW][MAX_COL]){
	printf("----------------\n");
	for (int row = 0; row < MAX_ROW; row++){
		for (int col = 0; col < MAX_COL; col++){
			printf("|%c ", chessBoard[row][col]);
		}
		printf("|\n");
		printf("----------------\n");
	}
}

void Playone(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
	int row = 0;
	int col = 0;
		printf("请输入您要落子的位置，棋盘规格为5x5，如(row col)：");
		scanf("%d %d", &row, &col);
				if (row<0 || row>=MAX_ROW || col<0 || col>=MAX_COL){
					printf("您的输入有误！\n");
					continue;
				}
				if (chessBoard[row][col] != ' ') {
					// 当前位置已经有子了, 不能再重复落子
					printf("该位置已经有子了!\n");
					continue;
				}
				 chessBoard[row][col] = 'X';
				break;
		}
	}

void Playtwo(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = 0;
		int col = 0;
			printf("请输入您要落子的位置，棋盘规格为5x5，如(2 2)：");
			scanf("%d %d", &row, &col);
			if (row<0 || row>MAX_ROW || col<0 || col>MAX_COL){
				printf("您的输入有误！\n");
				continue;
			}
			if (chessBoard[row][col] != ' ') {
				// 当前位置已经有子了, 不能再重复落子
				printf("该位置已经有子了!\n");
				continue;
			}
				chessBoard[row][col] = 'O';
				break;
	}
}

void Computer(char chessBoard[MAX_ROW][MAX_COL]){
	while (1){
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (chessBoard[row][col] != ' ') {
			continue;
		}
		chessBoard[row][col] = 'O';
		break;
	}
}

int IsFull(char chessBoard[MAX_ROW][MAX_COL]) {
	// 查找一下棋盘上是否有空位
	for (int row = 0; row < MAX_ROW; row++) {
		for (int col = 0; col < MAX_COL; col++) {
			if (chessBoard[row][col] == ' ') {
				// 找到空位了!!! 棋盘没满
				return 0;
			}
		}
	}
	// 所有位置都找完了, 也没找到空格, 最终才返回 1
	return 1;
}

char Check(char chessBoard[MAX_ROW][MAX_COL]){
	for (int row = 0; row < MAX_ROW; row++) {
		if (chessBoard[row][0] != ' '
			&& chessBoard[row][0] == chessBoard[row][1]
			&& chessBoard[row][0] == chessBoard[row][2]
			&& chessBoard[row][0] == chessBoard[row][3]
			&& chessBoard[row][0] == chessBoard[row][4]) {
			return chessBoard[row][0];
		}
	}
	// 2. 再检查所有的列
	for (int col = 0; col < MAX_COL; col++) {
		if (chessBoard[0][col] != ' '
			&& chessBoard[0][col] == chessBoard[1][col]
			&& chessBoard[0][col] == chessBoard[2][col]
			&& chessBoard[0][col] == chessBoard[3][col]
			&& chessBoard[0][col] == chessBoard[4][col]) {
			return chessBoard[0][col];
		}
	}
	// 3. 再检查对角线
	if (chessBoard[0][0] != ' '
		&& chessBoard[0][0] == chessBoard[1][1]
		&& chessBoard[0][0] == chessBoard[2][2]
		&& chessBoard[0][0] == chessBoard[3][3]
		&& chessBoard[0][0] == chessBoard[4][4]) {
		return chessBoard[0][0];
	}
	if (chessBoard[0][4] != ' '
		&& chessBoard[0][4] == chessBoard[1][3]
		&& chessBoard[0][4] == chessBoard[2][2]
		&& chessBoard[0][4] == chessBoard[3][1]
		&& chessBoard[0][4] == chessBoard[4][0]) {
		return chessBoard[0][4];
	}
	// 4. 判定是否和棋, 棋盘如果满了, 就算和棋
	if (IsFull(chessBoard)) {
		return 'Q';
	}
	return ' ';
}


void GamePlay(){
	char chessBoard[MAX_ROW][MAX_COL] = { 0 };
	Init(chessBoard);
	printf("一号玩家执棋！\n");
	char winner = ' ';
	while (1){
		Playone(chessBoard);
		Print(chessBoard);
		Check(chessBoard);
		winner = Check(chessBoard);
		if (winner != ' ') {
			break;
		}
		printf("二号玩家执棋！\n");
		Playtwo(chessBoard);
		Print(chessBoard);
		Check(chessBoard);
		winner = Check(chessBoard);
		if (winner != ' ') {
			break;
		}
	}
	system("cls");
	Print(chessBoard);

	if (winner == 'X') {
		printf("恭喜你, 你赢了!\n");
	}
	else if (winner == 'O') {
		printf("你真菜, 连ta都下不过!\n");
	}
	else {
		printf("你俩真菜,居然五五开!\n");
	}
}

void GameComputer(){
	char chessBoard[MAX_ROW][MAX_COL];
	Init(chessBoard);
	printf("一号玩家执棋！\n");
	char winner = ' ';
	while (1){
		Playone(chessBoard);
		Print(chessBoard);
		Check(chessBoard);
		winner = Check(chessBoard);
		if (winner != ' ') {
			break;
		}
		printf("电脑执棋！\n");
		Computer(chessBoard);
		Print(chessBoard);
		Check(chessBoard);
		winner = Check(chessBoard);
		if (winner != ' ') {
			break;
		}
	}
	system("cls");
	Print(chessBoard);

	if (winner == 'X') {
		printf("恭喜你, 你赢了!\n");
	}
	else if (winner == 'O') {
		printf("你真菜, 连电脑都下不过!\n");
	}
	else {
		printf("你真菜,和电脑五五开!\n");
	}
}

int main(){
	int i=0;
	int choice = 0;
	MenuUi(1); //打印游戏界面
	//是否进行游戏的选择；
	{
		printf("请输入您的选择：\n");
		choice= ChoiceStart(i);
		if (choice == 1){
			MenuMode(1);
		}
	}
//选择游戏的模式，人机或者人人；
	{
		printf("请选择游戏模式：\n");
		{
			choice = ChoiceMode(i);
			if (choice == 1){//人人模式
				system("cls");
				GamePlay(1);
			}
			if (choice == 2)
			{//人机模式
				system("cls");
				GameComputer(1);
			}
		}
	}
	system("pause");
	return 0;
}