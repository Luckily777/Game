#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <assert.h>

//定义通讯录数组的最大值为200 [0-200) 前闭后开
#define MAX_SIZE 200
#define CAPACITY 20

//定义个人联系信息的结构体变量
typedef struct PersonInof {
	char name[1024];//存储姓名
	char phone[1024];//存储电话
}PersonInof;//定义结构体声明

//定义通讯录结构
typedef struct AddressBook {
	PersonInof *persons;//总共可存储的通讯录人数
	int size;//统计放入的个数
	//定义空间 [0- size) 为已使用的空间
	// (size-200) 为未使用的空间
	int capacity;
	//通讯录的容量
}AddressBook;


//文件的读取和存储操作函数
void SaveFile(AddressBook* address) {
	//文件存储
	//1. 先行打开我们需要写入数据的文件
	FILE* fp = fopen("h:/address.txt", "w");
	if (fp == NULL) {
		perror("文件打开操作失败！\n");
		return;
	}

	//2. 使用for循环遍历的方式，将通讯录之中的数据写入到文件之中
	for (int i = 0; i < address->size; i++) {
		fwrite(&address->persons[i], sizeof(PersonInof), 1, fp);
	}
	fclose(fp);
	printf("保存成功!\n");
}





//初始化函数，将通讯录中的信息进行初始化
void Init(AddressBook* address) {
	address->size = 0;//先行使size为0 ，则表示通讯录为空
	address->persons = (PersonInof*)malloc(sizeof(PersonInof) * CAPACITY);
	if (address->persons == NULL)
	{
		perror("use malloc");//报错
		exit(EXIT_FAILURE);//退出
	}
	memset(address->persons, 0, sizeof(PersonInof) * CAPACITY);
	address->capacity = CAPACITY;
}


void CheckCapacity(AddressBook* address) {
	//检查是否容量超标，进行扩容
	if (address->size == address->capacity) {
		PersonInof* ptr = (PersonInof*)realloc(address->persons,
			address->capacity * sizeof(PersonInof));
		//进行续接，每次扩大的容量都是一个标准容量capacity
		if (address->persons == NULL)
		{
			//判空
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		else {
			address->persons = ptr;
		}
		printf("扩容成功！\n");
	}
}



//打印通讯录的菜单选项
int Menu() {
	printf("============================\n");
	printf("==========通 讯 录==========\n");
	printf("======1.新 增 联 系 人======\n");
	printf("======2.删 除 联 系 人======\n");
	printf("======3.修 改 联 系 人======\n");
	printf("======4.查 找 联 系 人======\n");
	printf("======5.排 序 通 讯 录======\n");
	printf("======6.打 印 通 讯 录======\n");
	printf("======7.清 空 通 讯 录======\n");
	printf("======0.   退  出     ======\n");
	printf("============================\n");
	printf("请输入您的选择：");
	int choice;
	scanf("%d", &choice);//输入我们的选择
	return choice;///返回用户所输入的信息
}

//增加联系人函数
void AddpersonInof(AddressBook* address) {
	assert(address->persons != NULL);
	CheckCapacity(address);
	PersonInof* info = &address->persons[address->size];
	//这样做是为了方便使用，避免在下面的输入中不断地输入很长地一串
	printf("请输入姓名：");
	scanf("%s", info->name);
	printf("请输入电话：");
	scanf("%s", info->phone);
	printf("成功增加新的联系人！\n");
	address->size ++;
}

//删除联系人函数
void DelpersonInof(AddressBook* address) {
	//确定执行删除操作
	printf("执行删除\n");
	if (address->size <= 0) {
		//先行判定通讯录是否为空
		printf("通讯录为空，无需进行删除！\n");
		return;
	}

	printf("请输入您要删除的联系人序号：");
	int id = 0;
	//创建需要删除的联系人序号变量
	scanf("%d", &id);
	//麻烦之处就是需要先行进行查询全部的联系人

	if (id < 0 || id >= address->size) {
		//检查客户输入的程序是否合法
		printf("输入的id非法！无法进行删除\n");
		return;
	}

	PersonInof* last_info = &address->persons[address->size - 1];
	//找到最后一个成员的信息
	PersonInof* to_delete = &address->persons[id];
	//需要删除的成员信息

	*to_delete = *last_info;
	//二者进行互换则可
	address->size--;
	//最后更改size值，保证删除后数量减11
	printf("删除成功！\n");
}

void FindpersonInof(AddressBook* address) {
	printf("查找指定联系人\n");
	printf("请输入要查找的联系人姓名：");
	int N = 0;
	char name[1024] = { 0 };
	//设定输入名字的变量
	scanf("%s", name);
	for (int i = 0; i < address->size; i++) {
		//逐个进行比对，将相等的输出
		PersonInof* info = &address->persons[i];
		if (strcmp(name, info->name) == 0) {
			printf("[%d] %s:%s\n", i, info->name, info->phone);
			N++;
		}
	}
	if (N == 0) {
		printf("未找到您需要查找的联系人信息！\n");
	}
	else {
		printf("查找联系人完毕\n");
	}

}

void ModifypersonInof(AddressBook* address) {
	if (address->size <= 0) {
		//同样判断通讯录是否为空
		printf("通讯录为空，无法进行修改\n");
			return;
	}
	int id = 0;
	printf("请输入要修改的联系人序号：");
	//创建联系人序号中间变量
	scanf("%d", &id);
	if (id < 0 || id >= address->size) {
		//检查输入序号是否合法
		printf("输入序号无法查询，修改失败\n");
		return;
	}

	PersonInof* info = &address->persons[id];
	//定义结构体变量类型
	printf("请输入修改后的名字（* 表示不修改）：");
	char name[1024] = { 0 };
	scanf("%s", name);
	//若相等则代表不修改
	if (strcmp(name, "*") != 0) {
		strcpy(info->name, name);
	}
	printf("请输入修改后的电话（* 表示不修改）：");
	char phone[1024] = { 0 };
	scanf("%s", phone);
	//同理
	if (strcmp(phone, "*") != 0) {
		strcpy(info->phone, phone);
	}
	printf("修改完成！\n");
}

void PrintpersonInof(AddressBook* address) {
	printf("打印通讯录\n");
	printf("%5s\t%10s\t%15s\t\n","num","name", "phone");
	for (int i = 0; i < address->size; i++) {
		PersonInof* info = &address->persons[i];
		printf("[%d] %s:%s\n",i,info->name,info->phone);
	}
	//逐个打印所存在的通讯录数据
	printf("当前共打印%d条记录\n", address->size);
}

void SortpersonInof(AddressBook* address) {
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < address->size - 1; i++)
	{
		for (j = 0; j < address->size - i - 1; j++)
		{
			if (strcmp(address->persons[i].name, address->persons[i + 1].name) > 0)
			{
				struct PersonInof tmp;
				tmp = address->persons[j];
				address->persons[j] = address->persons[j + 1];
				address->persons[j + 1] = tmp;
			}
		}
	}
}


void ClearpersonInof(AddressBook* address) {
	printf("是否要删除全部通讯录？\n");
	printf("Y（y）/N（n）\n");
	//提供确认选项供客户选择
	char choice[1024] = { 0 };
	//回答是则进行最后的删除
	scanf("%c", choice);
	if ((strcmp(choice, "y") == 0) || (strcmp(choice, "Y") == 0)) {
		address->size = 0;
		printf("删除完毕！\n");
		return;
	}
	//否则进行取消操作
	else{
		printf("删除取消！\n");
		return;
	}
}


void LoadFile(AddressBook* address) {
	//文件读取
	//1. 打开文件
	FILE* fp = fopen("h:/address.txt", "r");
	if (fp == NULL) {
		perror("文件打开操作失败！\n");
		return;
	}

	//2. 循环读取文件之中的内容，并把数据加载到通讯录结构体之中
	PersonInof tmp = { 0 };
	while (1) {
		int n = fread(&tmp, sizeof(PersonInof), 1, fp);
		if (n < 1) {
			break;
		}
		CheckCapacity(address);
		//判断容量是否超标，进行扩容操作
		address->persons[address->size] = tmp;
		address->size++;
	}
	fclose(fp);

}

int main() {
	AddressBook address;//创建初始变量
	Init(&address);//初始化函数
	LoadFile(&address);
	typedef void(*Func)(AddressBook*);
	//定义函数指针

	//采用转移表地方式来进行菜单地选择
	Func func_table[] = {
		NULL,//为和菜单项地序号匹配，将0地位置置为空
		AddpersonInof,
		DelpersonInof,
		ModifypersonInof,
		FindpersonInof,
		SortpersonInof,
		PrintpersonInof,
		ClearpersonInof,
	};
	while (1) {
		int choice = Menu();
		if (choice < 0 || choice >= sizeof(func_table) / sizeof(func_table[0])) {
			printf("您的输入有误！\n");
			continue;
		}
		if (choice == 0) {
			SaveFile(&address);
			system("cls");
			printf("goodbye!\n");
			break;
		}
		func_table[choice](&address);
	}

	system("pause");
	return 0;
}