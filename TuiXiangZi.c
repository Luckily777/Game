#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_ROW 8
#define MAX_COL 8

int Boxs;//ͳ��������ʣδ������ӵĸ���
int x, y;//�ô���������λС�˵�λ��


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
*	0	��ʾ��
*	1	��ʾǽ
*	2	��ʾ��
*	3	��ʾ����
*	4	��ʾĿ�ĵأ���
*	5	��ʾ����ɵ�����
*/



//1.��ӡ�˵�
//2.ѡ����Ϸ�ؿ�
//3.��ҿ�ʼ�ƶ�
//4.�ж���Ϸ�Ƿ�ɹ�

void MenuUi(){
	printf("\t�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U      ��ӭʹ����������Ϸ����     ף����������ս�޼���       �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                 ._______________________.                    �U\n");
	printf("\t�U                 | _____________________ |                    �U\n");
	printf("\t�U                 | I                   I |                    �U\n");
	printf("\t�U                 | I                   I |                    �U\n");
	printf("\t�U                 | I     �� �� ��      I |                    �U\n");
	printf("\t�U                 | I                   I |                    �U\n");
	printf("\t�U                 | I___________________I |                    �U\n");
	printf("\t�U                 !_______________________!                    �U\n");
	printf("\t�U                     ._[__________]_.                         �U\n");
	printf("\t�U                 .___|_______________|___.                    �U\n");
	printf("\t�U                  |::: ____             |                     �U\n");
	printf("\t�U                  |    ~~~~ [CD-ROM]    |                     �U\n");
	printf("\t�U                  !_____________________!                     �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                ˭ �� �� һ �� �� �� �� ƽ ����              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�U          1.��ʼ��Ϸ                 0.�뿪��Ϸ               �U\n");
	printf("\t�U                                                              �U\n");
	printf("\t�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a\n");
}

int ChoiceStart(int i){
	printf("����������ѡ��");
	while (1){
		scanf("%d", &i);
		if (i == 1){
			system("cls");/*����*/
			return 1;
		}
		if (i == 0){
			system("cls");/*����*/
			printf("��ӭ�����´���ս��\n");
			break;
		}
		else {
			printf("������������,�����������룺\n");
			continue;
		}
	}
	return 0;
}

void InitData(){
	int i, j;
	for (i = 0; i < MAX_ROW; i++){
		for (j = 0; j < MAX_COL; j++){
			//������2���ˣ�ʱ����¼�˵����ꡣx�� y��ǰ�涨���ȫ�ֱ���
			if (map[i][j] == 2){
				x = j;
				y = i;
			}

			if (map[i][j] == 3){//�����ͼ֮�����ӵ���Ŀ
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
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 4:
				printf("��");
				break;
			case 5:
				printf("��");
				break;
			}
		}
		printf("\n");
	}
}

void MoveUp(){
	if (y == 0){//���Ϸ�ֱ����ǽ��ʱ��ֱ�ӽ��з���
		return;
	}
	int Ux = x;
	int Uy = y - 1;
	if (map[Uy][Ux] == 1||map[Uy][Ux]==5){//���Ϸ���ǽ�������Ѿ���ɵ����ӣ��򲻶�
		return;
	}
	if (map[Uy][Ux] == 3){//���Ϸ������ӵ������
		if (map[Uy - 1][Ux] == 1){//�����Ϸ���ǽ�Ļ�����Ȼ����
			return;
		}
		if (map[Uy - 1][Ux] == 4){//���Ϸ����յ�Ļ�
			map[Uy - 1][Ux] = 5;//��������ǰ�ƶ����ﵽ�յ�
			Boxs--;
		}
		else{
			map[Uy - 1][Ux] = 3;//���Ϸ�û���κζ����������ӿ϶�������һ��
		}
	}
	map[y][x] = 0;//���˵�λ���û�Ϊ0
	map[Uy][Ux] = 2;//��ԭ���ӵ�λ���û�Ϊ��
	y = Uy;//���˵�λ�ý��иı�
}

void MoveDown(){
	int D = MAX_ROW - 1;
	if (y == D){//�·���ǽ�����ƶ���
		return;
	}
	int Dx = x;
	int Dy = y + 1;
	if (map[Dy][Dx] == 1 || map[Dy][Dx] == 5){//���·���ǽ�������Ѿ���ɵ����ӣ��򲻶�
		return;
	}
	if (map[Dy][Dx] == 3){//���·������ӵ������
		if (map[Dy + 1][Dx] == 1){//�����·���ǽ�Ļ�����Ȼ����
			return;
		}
		if (map[Dy + 1][Dx] == 4){//���·����յ�Ļ�
			map[Dy + 1][Dx] = 5;//���������·��ƶ����ﵽ�յ�
			Boxs--;
		}
		else{
			map[Dy + 1][Dx] = 3;//���·�û���κζ����������ӿ϶�������һ��
		}
	}
	map[y][x] = 0;//���˵�λ���û�Ϊ0
	map[Dy][Dx] = 2;//��ԭ���ӵ�λ���û�Ϊ��
	y = Dy;//���˵�λ�ý��иı�
}


void MoveLeft(){
	if (x == 0){
		return;
	}//�����ǽ�Ļ����򲻶���
	int Lx = x - 1;
	int Ly = y;

	if (map[Ly][Lx] == 1 || map[Ly][Lx] == 5){//������ǽ�������Ѿ���ɵ����ӣ��򲻶�
		return;
	}
	if (map[Ly][Lx] == 3){//���������ӵ������
		if (map[Ly][Lx - 1] == 1){//��������ǽ�Ļ�����Ȼ����
			return;
		}
		if (map[Ly][Lx - 1] == 4){//�������յ�Ļ�
			map[Ly][Lx - 1] = 5;//�����������ƶ����ﵽ�յ�
			Boxs--;
		}
		else{
			map[Ly][Lx - 1] = 3;//����û���κζ����������ӿ϶�������һ��
		}
	}
	map[y][x] = 0;//���˵�λ���û�Ϊ0
	map[Ly][Lx] = 2;//��ԭ���ӵ�λ���û�Ϊ��
	x = Lx;//���˵�λ�ý��иı�
}


void MoveRight(){
	int R = MAX_COL - 1;
	if (x == R){
		return;
	}
	int Rx = x + 1;
	int Ry = y;
	if (map[Ry][Rx] == 1 || map[Ry][Rx] == 5){//���ҷ���ǽ�������Ѿ���ɵ����ӣ��򲻶�
		return;
	}
	if (map[Ry][Rx] == 3){//���ҷ������ӵ������
		if (map[Ry][Rx + 1] == 1){//�����ҷ���ǽ�Ļ�����Ȼ����
			return;
		}
		if (map[Ry][Rx + 1] == 4){//���ҷ����յ�Ļ�
			map[Ry][Rx + 1] = 5;//���������ҷ��ƶ����ﵽ�յ�
			Boxs--;
		}
		else{
			map[Ry][Rx + 1] = 3;//���ҷ�û���κζ����������ӿ϶�������һ��
		}
	}
	map[y][x] = 0;//���˵�λ���û�Ϊ0
	map[Ry][Rx] = 2;//��ԭ���ӵ�λ���û�Ϊ��
	x = Rx;//���˵�λ�ý��иı�
}



int Game(){
	char direction;
	InitData();
	while (1){
		system("cls");
		drawMap();
		printf("������������Ҫ�ƶ��ķ���(Сд��ĸ)����WΪ�ϣ�AΪ��SΪ�£�DΪ�ң�\n");
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
	printf("����ͨ����Ϸ!\n");
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
